#!/bin/bash
# QMK Setup Script for RattusBoard
# Copyright 2024 RattusBoard Project
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

echo "🛠️  Setting up QMK environment for RattusBoard..."

# Ensure we have QMK CLI
if ! command -v qmk >/dev/null 2>&1; then
    echo "❌ QMK CLI not found. Installing QMK CLI..."
    python3 -m pip install --user qmk
    export PATH="$HOME/.local/bin:$PATH"
    echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc
fi

# Ensure we have ARM GCC
if ! command -v arm-none-eabi-gcc >/dev/null 2>&1; then
    echo "❌ ARM GCC not found. Installing ARM GCC toolchain..."
    sudo apt-get update && sudo apt-get install -y gcc-arm-none-eabi libnewlib-arm-none-eabi
fi

# Set up paths
REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
QMK_FIRMWARE_DIR="$REPO_ROOT/qmk_firmware"
RATTUSBOARD_KEYBOARD_DIR="$REPO_ROOT/keyboards/rattusboard"

echo "📂 Repository root: $REPO_ROOT"
echo "📂 QMK firmware will be: $QMK_FIRMWARE_DIR"

# Clone QMK firmware if it doesn't exist (minimal clone)
if [ ! -d "$QMK_FIRMWARE_DIR" ]; then
    echo "📥 Cloning QMK firmware (this may take a few minutes)..."
    git clone --depth 1 https://github.com/qmk/qmk_firmware.git "$QMK_FIRMWARE_DIR"
    
    # Initialize required submodules only
    cd "$QMK_FIRMWARE_DIR"
    git submodule update --init --recursive lib/chibios
    git submodule update --init --recursive platforms/chibios
    git submodule update --init --recursive quantum
else
    echo "✅ QMK firmware already exists"
fi

# Set up QMK home
export QMK_HOME="$QMK_FIRMWARE_DIR"
echo "export QMK_HOME=\"$QMK_FIRMWARE_DIR\"" >> ~/.bashrc

# Create symlink for RattusBoard keyboard
RATTUSBOARD_IN_QMK="$QMK_FIRMWARE_DIR/keyboards/rattusboard"
if [ -L "$RATTUSBOARD_IN_QMK" ]; then
    echo "✅ RattusBoard keyboard symlink already exists"
elif [ -d "$RATTUSBOARD_IN_QMK" ]; then
    echo "⚠️  RattusBoard keyboard directory exists in QMK, backing up..."
    mv "$RATTUSBOARD_IN_QMK" "$RATTUSBOARD_IN_QMK.backup.$(date +%s)"
fi

if [ ! -L "$RATTUSBOARD_IN_QMK" ]; then
    echo "🔗 Creating symlink for RattusBoard keyboard..."
    ln -sf "$RATTUSBOARD_KEYBOARD_DIR" "$RATTUSBOARD_IN_QMK"
fi

# Test compilation
echo "🔨 Testing firmware compilation..."
cd "$QMK_FIRMWARE_DIR"
if qmk compile -kb rattusboard -km default; then
    echo "✅ Firmware compilation successful!"
    echo "📁 Built files:"
    ls -la .build/rattusboard_default.* 2>/dev/null || echo "   No build files found"
    
    # Copy firmware to repo root for convenience
    if [ -f ".build/rattusboard_default.uf2" ]; then
        cp ".build/rattusboard_default.uf2" "$REPO_ROOT/"
        echo "   📄 Copied: rattusboard_default.uf2"
    fi
    if [ -f ".build/rattusboard_default.elf" ]; then
        cp ".build/rattusboard_default.elf" "$REPO_ROOT/"
        echo "   📄 Copied: rattusboard_default.elf"
    fi
else
    echo "⚠️  Firmware compilation failed. This might be expected if dependencies are missing."
    echo "   You can try running 'qmk setup' in the QMK firmware directory later."
fi

echo ""
echo "🎉 QMK setup complete!"
echo ""
echo "Quick start commands:"
echo "  cd $QMK_FIRMWARE_DIR"
echo "  qmk compile -kb rattusboard -km default"
echo ""
echo "Environment variables for your shell:"
echo "  export QMK_HOME=\"$QMK_FIRMWARE_DIR\""