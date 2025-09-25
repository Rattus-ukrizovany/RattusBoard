#!/bin/bash
# Quick setup checker for RattusBoard development environment
# Copyright 2024 RattusBoard Project
# SPDX-License-Identifier: GPL-3.0-or-later

echo "🔍 RattusBoard Development Environment Checker"
echo "=============================================="

# Check if tools are installed
echo ""
echo "🔧 Checking required tools..."

# QMK CLI
if command -v qmk >/dev/null 2>&1; then
    echo "✅ QMK CLI: $(qmk --version 2>/dev/null || echo 'installed')"
else
    echo "❌ QMK CLI not found. Run: python3 -m pip install --user qmk"
fi

# ARM GCC
if command -v arm-none-eabi-gcc >/dev/null 2>&1; then
    echo "✅ ARM GCC: $(arm-none-eabi-gcc --version | head -1 | cut -d' ' -f1-3)"
else
    echo "❌ ARM GCC not found. Run: sudo apt-get install -y gcc-arm-none-eabi libnewlib-arm-none-eabi"
fi

# Renode
if command -v renode >/dev/null 2>&1; then
    echo "✅ Renode: $(renode --version 2>/dev/null | head -1 || echo 'installed')"
else
    echo "⚠️  Renode not found. Install from: https://github.com/renode/renode/releases"
fi

# Check QMK setup
echo ""
echo "⚙️  Checking QMK setup..."

if [ -d "qmk_firmware" ] && [ -d "qmk_firmware/quantum" ]; then
    echo "✅ QMK firmware repository found"
    
    if [ -d "qmk_firmware/keyboards/rattusboard" ]; then
        echo "✅ RattusBoard keyboard configuration found"
        
        # Test compilation
        echo ""
        echo "🔨 Testing firmware compilation..."
        cd qmk_firmware 2>/dev/null || { echo "❌ Failed to enter qmk_firmware directory"; exit 1; }
        
        if timeout 30 make rattusboard:default >/dev/null 2>&1; then
            echo "✅ Firmware compilation successful"
            if [ -f ".build/rattusboard_default.uf2" ]; then
                echo "✅ Firmware file created: .build/rattusboard_default.uf2"
            fi
        else
            echo "⚠️  Firmware compilation failed or timed out"
            echo "   Try: cd qmk_firmware && make rattusboard:default"
        fi
        cd - >/dev/null
    else
        echo "❌ RattusBoard keyboard not found in QMK firmware"
        echo "   Run: bash setup-qmk.sh"
    fi
else
    echo "❌ QMK firmware not set up"
    echo "   Run: bash setup-qmk.sh"
fi

# Check repository structure
echo ""
echo "📁 Checking repository structure..."

required_files=(
    "keyboards/rattusboard/info.json"
    "keyboards/rattusboard/rules.mk"
    "keyboards/rattusboard/keymaps/default/keymap.c"
    "sim/rattusboard.resc"
    "sim/rattusboard.repl"
)

all_found=true
for file in "${required_files[@]}"; do
    if [ -f "$file" ]; then
        echo "✅ $file"
    else
        echo "❌ $file missing"
        all_found=false
    fi
done

echo ""
if [ "$all_found" = true ]; then
    echo "🎉 All required files found! Environment looks good."
else
    echo "⚠️  Some files are missing. Repository may be incomplete."
fi

echo ""
echo "📚 Quick start commands:"
echo "  bash setup-qmk.sh              # Set up QMK environment"
echo "  bash .devcontainer/test-environment.sh  # Run full environment test"
echo "  cd qmk_firmware && make rattusboard:default  # Build firmware"
echo "  renode sim/rattusboard.resc     # Start simulation"
echo ""
echo "📖 For detailed setup instructions, see: SETUP.md"