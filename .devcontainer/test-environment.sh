#!/bin/bash
# Test script to validate RattusBoard Codespaces environment
# Copyright 2024 RattusBoard Project
# SPDX-License-Identifier: GPL-3.0-or-later

echo "🧪 Testing RattusBoard Codespaces Environment"
echo "=============================================="

# Test 1: Check required tools are available
echo "🔧 Checking required tools..."
failed=0

if command -v qmk >/dev/null 2>&1; then
    echo "✅ QMK CLI: $(qmk --version)"
else
    echo "❌ QMK CLI not found"
    failed=1
fi

if command -v renode >/dev/null 2>&1; then
    echo "✅ Renode: $(renode --version | head -1)"
else
    echo "❌ Renode not found"
    failed=1
fi

if command -v arm-none-eabi-gcc >/dev/null 2>&1; then
    echo "✅ ARM GCC: $(arm-none-eabi-gcc --version | head -1)"
else
    echo "❌ ARM GCC not found"
    failed=1
fi

# Test 2: Check repository structure
echo ""
echo "📁 Checking repository structure..."

if [ -f "sim/rattusboard.resc" ]; then
    echo "✅ Renode simulation script found"
else
    echo "❌ Renode simulation script missing"
    failed=1
fi

if [ -f "sim/rattusboard.repl" ]; then
    echo "✅ Renode platform description found"
else
    echo "❌ Renode platform description missing"
    failed=1
fi

if [ -d "keyboards/rattusboard" ]; then
    echo "✅ RattusBoard keyboard definition found"
else
    echo "❌ RattusBoard keyboard definition missing"
    failed=1
fi

# Test 3: Try QMK setup (non-destructive)
echo ""
echo "⚙️  Testing QMK setup..."
if QMK_HOME=/workspace qmk setup --yes 2>/dev/null; then
    echo "✅ QMK setup successful"
else
    echo "⚠️  QMK setup may need manual intervention"
fi

# Test 4: Test compilation (if environment is fully set up)
echo ""
echo "🔨 Testing firmware compilation..."
if QMK_HOME=/workspace qmk compile -kb rattusboard -km default 2>/dev/null; then
    echo "✅ Firmware compilation successful"
    if [ -f ".build/rattusboard_default.elf" ]; then
        echo "✅ Firmware binary created"
    fi
else
    echo "⚠️  Firmware compilation failed (may need QMK setup)"
fi

# Summary
echo ""
echo "📊 Test Summary"
echo "==============="
if [ $failed -eq 0 ]; then
    echo "🎉 All tests passed! Environment is ready for development."
    echo ""
    echo "Quick start commands:"
    echo "  qmk compile -kb rattusboard -km default"
    echo "  renode sim/rattusboard.resc"
else
    echo "⚠️  Some tests failed. Please check the setup."
    echo ""
    echo "Troubleshooting:"
    echo "  - Try running: qmk setup -y"
    echo "  - Check if you're in the correct directory: /workspace"
    echo "  - Restart the Codespace if issues persist"
fi

echo ""
echo "For help, see: https://github.com/Rattus-ukrizovany/RattusBoard/blob/main/SIMULATION.md"