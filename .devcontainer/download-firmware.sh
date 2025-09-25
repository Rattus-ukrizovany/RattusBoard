#!/bin/bash
# Firmware Download Script for RattusBoard
# Copyright 2024 RattusBoard Project
# SPDX-License-Identifier: GPL-3.0-or-later
#
# Downloads the latest firmware release from GitHub Releases
# Supports downloading specific firmware files or all files

set -euo pipefail

# Configuration
REPO_OWNER="Rattus-ukrizovany"
REPO_NAME="RattusBoard"
FIRMWARE_DIR="/workspace/firmware"
DEFAULT_FIRMWARE="rattusboard_default.uf2"

# Global variables
VERBOSE=false
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Logging functions
log_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

log_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

log_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Help message
show_help() {
    cat << EOF
RattusBoard Firmware Downloader

Usage: $0 [OPTIONS] [FIRMWARE_FILE]

Options:
  -h, --help          Show this help message
  -l, --list          List available firmware files from latest release
  -a, --all           Download all firmware files from latest release
  -f, --force         Force re-download even if file exists
  -d, --dir DIR       Set custom download directory (default: $FIRMWARE_DIR)
  -v, --verbose       Enable verbose output
  --tag TAG           Download from specific release tag instead of latest

Arguments:
  FIRMWARE_FILE       Specific firmware file to download (default: $DEFAULT_FIRMWARE)

Examples:
  $0                          # Download default firmware (rattusboard_default.uf2)
  $0 -l                       # List available firmware files
  $0 -a                       # Download all firmware files
  $0 rattusboard_left.uf2     # Download specific firmware file
  $0 --tag v1.0.0 -a          # Download all files from specific release
  $0 -f                       # Force re-download default firmware

EOF
}

# Check if required tools are available
check_dependencies() {
    local missing_deps=()
    
    if ! command -v curl >/dev/null 2>&1; then
        missing_deps+=("curl")
    fi
    
    if ! command -v jq >/dev/null 2>&1; then
        missing_deps+=("jq")
    fi
    
    if [ ${#missing_deps[@]} -ne 0 ]; then
        log_error "Missing required dependencies: ${missing_deps[*]}"
        log_error "Please install the missing tools and try again."
        exit 1
    fi
}

# Get latest release information
get_release_info() {
    local tag="$1"
    local api_url
    
    if [ "$tag" = "latest" ]; then
        api_url="https://api.github.com/repos/${REPO_OWNER}/${REPO_NAME}/releases/latest"
    else
        api_url="https://api.github.com/repos/${REPO_OWNER}/${REPO_NAME}/releases/tags/${tag}"
    fi
    
    if [ "$VERBOSE" = true ]; then
        log_info "Fetching release info from: $api_url"
    fi
    
    local response
    response=$(curl -s "$api_url") || {
        log_error "Failed to fetch release information from GitHub API"
        log_error "Please check your internet connection and try again"
        return 1
    }
    
    # Check if API returned an error
    local error_msg
    error_msg=$(printf "%s" "$response" | jq -r '.message // empty' 2>/dev/null || echo "")
    if [ -n "$error_msg" ]; then
        log_error "GitHub API error: $error_msg"
        return 1
    fi
    
    echo "$response"
}

# List available firmware files
list_firmware_files() {
    local tag="$1"
    
    log_info "Fetching available firmware files from $tag release..."
    
    local release_info
    release_info=$(get_release_info "$tag") || return 1
    
    local release_name
    release_name=$(printf "%s" "$release_info" | jq -r '.name // "Unknown Release"' 2>/dev/null || echo "Unknown Release")
    
    local assets
    assets=$(printf "%s" "$release_info" | jq -r '.assets[]? | select(.name | endswith(".uf2"))? | "\(.name) (\(.size) bytes)" // empty' 2>/dev/null || echo "")
    
    echo
    log_success "Release: $release_name"
    echo
    echo "Available firmware files:"
    if [ -n "$assets" ]; then
        echo "$assets" | while IFS= read -r asset; do
            echo "  • $asset"
        done
    else
        log_warning "No .uf2 firmware files found in this release"
    fi
    echo
}

# Download a specific firmware file
download_firmware_file() {
    local tag="$1"
    local filename="$2"
    local download_dir="$3"
    local force="$4"
    
    # Create firmware directory if it doesn't exist
    mkdir -p "$download_dir"
    
    local filepath="$download_dir/$filename"
    
    # Check if file already exists
    if [ -f "$filepath" ] && [ "$force" = false ]; then
        log_warning "File $filename already exists in $download_dir"
        log_info "Use -f/--force to re-download or delete the file manually"
        return 0
    fi
    
    log_info "Fetching release information..."
    local release_info
    release_info=$(get_release_info "$tag") || return 1
    
    # Find the download URL for the specified file
    # Use the same approach as the list function which works
    local download_url=""
    
    # Get all assets and then filter in bash instead of jq
    local all_assets
    all_assets=$(printf "%s" "$release_info" | jq -r '.assets[]? | "\(.name) \(.browser_download_url)"' 2>/dev/null || echo "")
    
    if [ -n "$all_assets" ]; then
        # Find the line with our filename and extract the URL
        download_url=$(echo "$all_assets" | grep "^${filename} " | cut -d' ' -f2- || echo "")
    fi
    
    if [ "$VERBOSE" = true ]; then
        log_info "Looking for filename: $filename"
        log_info "Download URL found: $download_url"
    fi
    
    if [ -z "$download_url" ] || [ "$download_url" = "null" ]; then
        log_error "Firmware file '$filename' not found in the latest release"
        log_info "Use -l/--list to see available files"
        return 1
    fi
    
    log_info "Downloading $filename..."
    if [ "$VERBOSE" = true ]; then
        log_info "URL: $download_url"
        log_info "Destination: $filepath"
    fi
    
    # Download the file
    if curl -L -o "$filepath" "$download_url"; then
        local file_size
        file_size=$(stat -c%s "$filepath" 2>/dev/null || echo "unknown")
        log_success "Downloaded $filename ($file_size bytes) to $download_dir"
        
        # Verify it's actually a UF2 file (basic check)
        if [ "$file_size" != "unknown" ] && [ "$file_size" -lt 100 ]; then
            log_warning "Downloaded file seems unusually small - please verify it's correct"
        fi
        
        return 0
    else
        log_error "Failed to download $filename"
        # Clean up partial download
        rm -f "$filepath"
        return 1
    fi
}

# Download all firmware files
download_all_firmware() {
    local tag="$1"
    local download_dir="$2"
    local force="$3"
    
    log_info "Fetching release information..."
    local release_info
    release_info=$(get_release_info "$tag") || return 1
    
    # Get all .uf2 files
    local firmware_files
    firmware_files=$(printf "%s" "$release_info" | jq -r '.assets[]? | select(.name | endswith(".uf2"))? | .name // empty' 2>/dev/null || echo "")
    
    if [ -z "$firmware_files" ]; then
        log_error "No .uf2 firmware files found in the release"
        return 1
    fi
    
    local success_count=0
    local total_count=0
    
    echo "$firmware_files" | while IFS= read -r filename; do
        total_count=$((total_count + 1))
        if download_firmware_file "$tag" "$filename" "$download_dir" "$force"; then
            success_count=$((success_count + 1))
        fi
    done
    
    log_info "Download summary: $success_count/$total_count files downloaded successfully"
}

# Main function
main() {
    local DOWNLOAD_ALL=false
    local FORCE=false
    local DOWNLOAD_DIR="$FIRMWARE_DIR"
    local RELEASE_TAG="latest"
    local FIRMWARE_FILE="$DEFAULT_FIRMWARE"
    local LIST_FILES=false
    
    # Parse command line arguments
    while [[ $# -gt 0 ]]; do
        case $1 in
            -h|--help)
                show_help
                exit 0
                ;;
            -l|--list)
                LIST_FILES=true
                shift
                ;;
            -a|--all)
                DOWNLOAD_ALL=true
                shift
                ;;
            -f|--force)
                FORCE=true
                shift
                ;;
            -v|--verbose)
                VERBOSE=true
                shift
                ;;
            -d|--dir)
                DOWNLOAD_DIR="$2"
                shift 2
                ;;
            --tag)
                RELEASE_TAG="$2"
                shift 2
                ;;
            -*)
                log_error "Unknown option: $1"
                show_help
                exit 1
                ;;
            *)
                FIRMWARE_FILE="$1"
                shift
                ;;
        esac
    done
    
    # Check dependencies
    check_dependencies
    
    # Handle list command
    if [ "$LIST_FILES" = true ]; then
        list_firmware_files "$RELEASE_TAG"
        exit 0
    fi
    
    echo "🐭 RattusBoard Firmware Downloader"
    echo "=================================="
    echo
    
    # Handle download all command
    if [ "$DOWNLOAD_ALL" = true ]; then
        download_all_firmware "$RELEASE_TAG" "$DOWNLOAD_DIR" "$FORCE"
        exit_code=$?
    else
        download_firmware_file "$RELEASE_TAG" "$FIRMWARE_FILE" "$DOWNLOAD_DIR" "$FORCE"
        exit_code=$?
    fi
    
    if [ $exit_code -eq 0 ]; then
        echo
        log_success "Firmware download completed!"
        log_info "Files saved to: $DOWNLOAD_DIR"
        echo
        log_info "Next steps:"
        echo "  1. Flash firmware to your RattusBoard using the .uf2 files"
        echo "  2. Or test in Renode simulation: rattusboard-test-firmware"
        echo
    else
        echo
        log_error "Firmware download failed!"
        log_info "Troubleshooting tips:"
        echo "  • Check your internet connection"
        echo "  • Verify the firmware file name with -l/--list"
        echo "  • Try again with -v/--verbose for more details"
        echo
        exit $exit_code
    fi
}

# Run main function with all arguments
main "$@"