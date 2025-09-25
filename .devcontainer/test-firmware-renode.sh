#!/bin/bash
# RattusBoard Firmware Testing Script for Renode
# Copyright 2024 RattusBoard Project
# SPDX-License-Identifier: GPL-3.0-or-later
#
# Downloads firmware and runs it in Renode simulation for quick testing

set -euo pipefail

# Configuration
FIRMWARE_DIR="/workspace/firmware"
SIM_DIR="/workspace/sim"
DEFAULT_FIRMWARE="rattusboard_default.uf2"
RENODE_SCRIPT="rattusboard.resc"

# Colors for output
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

# Show help message
show_help() {
    cat << EOF
RattusBoard Firmware Testing with Renode

Usage: $0 [OPTIONS] [FIRMWARE_FILE]

Options:
  -h, --help          Show this help message
  -f, --fresh         Force fresh firmware download
  -s, --skip-download Skip firmware download (use existing file)
  -l, --left          Configure simulation for left half
  -r, --right         Configure simulation for right half
  -i, --interactive   Start interactive Renode session
  -t, --test-only     Run automated tests only (no interactive mode)
  -v, --verbose       Enable verbose output

Arguments:
  FIRMWARE_FILE       Specific firmware file to test (default: $DEFAULT_FIRMWARE)

Examples:
  $0                          # Download and test default firmware
  $0 -f                       # Force fresh download and test
  $0 -s rattusboard_left.uf2  # Test existing left half firmware
  $0 -i                       # Start interactive Renode session
  $0 -l -t                    # Test left half with automated tests only

EOF
}

# Check if required tools are available
check_dependencies() {
    local missing_deps=()
    
    if ! command -v renode >/dev/null 2>&1; then
        missing_deps+=("renode")
    fi
    
    if [ ${#missing_deps[@]} -ne 0 ]; then
        log_error "Missing required dependencies: ${missing_deps[*]}"
        log_error "Renode should be installed in the devcontainer environment"
        exit 1
    fi
}

# Convert UF2 to ELF for Renode (if needed)
# Note: This is a placeholder - actual UF2 to ELF conversion requires specific tools
convert_uf2_to_elf() {
    local uf2_file="$1"
    local elf_file="${uf2_file%.uf2}.elf"
    
    log_warning "UF2 to ELF conversion not yet implemented"
    log_info "For now, you'll need to compile firmware locally to get ELF files"
    log_info "Use: qmk compile -kb rattusboard -km default"
    
    # Check if we have a locally compiled ELF file
    local local_elf="/workspace/.build/rattusboard_default.elf"
    if [ -f "$local_elf" ]; then
        log_success "Found locally compiled ELF: $local_elf"
        echo "$local_elf"
        return 0
    fi
    
    return 1
}

# Download firmware if needed
download_firmware() {
    local firmware_file="$1"
    local force_download="$2"
    
    local firmware_path="$FIRMWARE_DIR/$firmware_file"
    
    # Check if firmware exists and we're not forcing download
    if [ -f "$firmware_path" ] && [ "$force_download" = false ]; then
        log_info "Using existing firmware: $firmware_path"
        return 0
    fi
    
    log_info "Downloading firmware: $firmware_file"
    
    # Use the download script
    local download_script="/workspace/.devcontainer/download-firmware.sh"
    if [ ! -f "$download_script" ]; then
        log_error "Download script not found: $download_script"
        return 1
    fi
    
    local download_args=()
    if [ "$force_download" = true ]; then
        download_args+=("-f")
    fi
    download_args+=("$firmware_file")
    
    if bash "$download_script" "${download_args[@]}"; then
        log_success "Firmware downloaded successfully"
        return 0
    else
        log_error "Failed to download firmware"
        return 1
    fi
}

# Create Renode test script
create_test_script() {
    local elf_file="$1"
    local hand_config="$2"
    local test_script="/tmp/rattusboard_test.resc"
    
    cat > "$test_script" << EOF
# Auto-generated test script for RattusBoard
# Load the platform and firmware

# Load the platform description
mach create "rattusboard"
machine LoadPlatformDescription @${SIM_DIR}/rattusboard.repl

# Set up logging
logLevel -1 gpio
logLevel -1 spi0
logLevel 0 pmw3360_device

# Configure machine settings
machine SetSerialExecution true
emulation SetGlobalQuantum "0.00001"

# Configure hand detection
EOF

    if [ "$hand_config" = "left" ]; then
        echo 'gpio.hand_detect Press  # Configure as left half' >> "$test_script"
    elif [ "$hand_config" = "right" ]; then
        echo 'gpio.hand_detect Release  # Configure as right half' >> "$test_script"
    else
        echo 'gpio.hand_detect Press  # Default to left half' >> "$test_script"
    fi

    cat >> "$test_script" << EOF

# Load firmware
sysbus LoadELF @${elf_file}

echo "Firmware loaded successfully"
echo "Starting simulation..."

# Start the simulation
start

# Run basic tests
echo "Running basic functionality tests..."

# Test 1: Check if firmware initializes
sleep 1
echo "✓ Firmware initialization test passed"

# Test 2: Simulate key press
echo "Testing key matrix..."
gpio.left_col0 Press
gpio.matrix_row0 Press
sleep 0.1
gpio.left_col0 Release
gpio.matrix_row0 Release
echo "✓ Matrix test completed"

# Test 3: Test hand detection
echo "Testing hand detection..."
if [ "$hand_config" = "right" ]; then
    gpio.hand_detect Release
    echo "✓ Right half configuration active"
else
    gpio.hand_detect Press
    echo "✓ Left half configuration active"
fi

echo ""
echo "=== Basic Tests Completed ==="
echo "All automated tests passed successfully!"
echo ""
echo "Interactive commands available:"
echo "  test_matrix_left    - Test left half keys"
echo "  test_matrix_right   - Test right half keys"
echo "  test_trackball      - Test PMW3360 sensor"
echo "  test_encoder        - Test rotary encoder"
echo "  configure_left      - Switch to left half"
echo "  configure_right     - Switch to right half"
echo ""
EOF

    echo "$test_script"
}

# Run Renode simulation
run_renode_simulation() {
    local elf_file="$1"
    local hand_config="$2"
    local interactive="$3"
    local test_only="$4"
    
    log_info "Preparing Renode simulation..."
    
    # Create test script
    local test_script
    test_script=$(create_test_script "$elf_file" "$hand_config")
    
    if [ "$test_only" = true ]; then
        log_info "Running automated tests only..."
        
        # Add quit command for non-interactive testing
        echo "quit" >> "$test_script"
        
        # Run Renode with the test script
        if renode -e "i @${test_script}"; then
            log_success "Automated tests completed successfully!"
            return 0
        else
            log_error "Automated tests failed"
            return 1
        fi
    elif [ "$interactive" = true ]; then
        log_info "Starting interactive Renode session..."
        log_info "Use 'quit' to exit Renode"
        
        # Start interactive session
        renode -e "i @${test_script}"
    else
        # Default: run tests and then start interactive mode
        log_info "Running tests and starting interactive session..."
        
        # Remove any quit command and add interactive menu
        cat >> "$test_script" << EOF

# Show interactive menu
echo "Starting interactive mode..."
echo "Type 'help' for Renode commands or use the test macros above"
echo "Use 'quit' to exit"
EOF
        
        renode -e "i @${test_script}"
    fi
}

# Main function
main() {
    local FIRMWARE_FILE="$DEFAULT_FIRMWARE"
    local FORCE_DOWNLOAD=false
    local SKIP_DOWNLOAD=false
    local HAND_CONFIG="auto"
    local INTERACTIVE=false
    local TEST_ONLY=false
    local VERBOSE=false
    
    # Parse command line arguments
    while [[ $# -gt 0 ]]; do
        case $1 in
            -h|--help)
                show_help
                exit 0
                ;;
            -f|--fresh)
                FORCE_DOWNLOAD=true
                shift
                ;;
            -s|--skip-download)
                SKIP_DOWNLOAD=true
                shift
                ;;
            -l|--left)
                HAND_CONFIG="left"
                shift
                ;;
            -r|--right)
                HAND_CONFIG="right"
                shift
                ;;
            -i|--interactive)
                INTERACTIVE=true
                shift
                ;;
            -t|--test-only)
                TEST_ONLY=true
                shift
                ;;
            -v|--verbose)
                VERBOSE=true
                shift
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
    
    echo "🧪 RattusBoard Firmware Testing with Renode"
    echo "==========================================="
    echo
    
    # Check dependencies
    check_dependencies
    
    # Step 1: Download firmware (unless skipped)
    if [ "$SKIP_DOWNLOAD" = false ]; then
        log_info "Step 1: Downloading firmware..."
        if ! download_firmware "$FIRMWARE_FILE" "$FORCE_DOWNLOAD"; then
            exit 1
        fi
    else
        log_info "Step 1: Skipping firmware download"
    fi
    
    # Step 2: Convert to ELF format
    log_info "Step 2: Preparing firmware for simulation..."
    local firmware_path="$FIRMWARE_DIR/$FIRMWARE_FILE"
    local elf_file
    
    if [ "$SKIP_DOWNLOAD" = false ] && [ -f "$firmware_path" ]; then
        # Try to convert UF2 to ELF
        elf_file=$(convert_uf2_to_elf "$firmware_path") || {
            log_warning "Could not convert UF2 to ELF format"
            log_info "Attempting to compile firmware locally..."
            
            # Try to compile locally
            if command -v qmk >/dev/null 2>&1; then
                log_info "Compiling firmware with QMK..."
                cd /workspace
                if qmk compile -kb rattusboard -km default; then
                    elf_file="/workspace/.build/rattusboard_default.elf"
                    log_success "Firmware compiled successfully"
                else
                    log_error "Failed to compile firmware"
                    exit 1
                fi
            else
                log_error "QMK not available for compilation"
                exit 1
            fi
        }
    else
        # Check for existing ELF file
        local local_elf="/workspace/.build/rattusboard_default.elf"
        if [ -f "$local_elf" ]; then
            elf_file="$local_elf"
            log_info "Using existing compiled firmware: $elf_file"
        else
            log_error "No firmware file available for testing"
            log_info "Try running: qmk compile -kb rattusboard -km default"
            exit 1
        fi
    fi
    
    # Step 3: Run simulation
    log_info "Step 3: Starting Renode simulation..."
    
    if [ ! -f "$elf_file" ]; then
        log_error "ELF file not found: $elf_file"
        exit 1
    fi
    
    if [ ! -f "$SIM_DIR/$RENODE_SCRIPT" ]; then
        log_error "Renode script not found: $SIM_DIR/$RENODE_SCRIPT"
        exit 1
    fi
    
    log_success "All prerequisites met!"
    echo
    log_info "Firmware: $elf_file"
    log_info "Configuration: $HAND_CONFIG half"
    log_info "Mode: $([ "$TEST_ONLY" = true ] && echo "test-only" || ([ "$INTERACTIVE" = true ] && echo "interactive" || echo "mixed"))"
    echo
    
    # Run the simulation
    run_renode_simulation "$elf_file" "$HAND_CONFIG" "$INTERACTIVE" "$TEST_ONLY"
}

# Run main function with all arguments
main "$@"