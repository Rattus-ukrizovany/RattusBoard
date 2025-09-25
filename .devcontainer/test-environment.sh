#!/bin/bash
# Test script to validate RattusBoard Codespaces environment
# Copyright 2024 RattusBoard Project
# SPDX-License-Identifier: GPL-3.0-or-later

echo "🧪 Testing RattusBoard Development Environment"
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

if command -v arm-none-eabi-gcc >/dev/null 2>&1; then
    echo "✅ ARM GCC: $(arm-none-eabi-gcc --version | head -1)"
else
    echo "❌ ARM GCC not found"
    failed=1
fi

# Test 2: Check repository structure
echo ""
echo "📁 Checking repository structure..."

if [ -d "keyboards/rattusboard" ]; then
    echo "✅ RattusBoard keyboard definition found"
else
    echo "❌ RattusBoard keyboard definition missing"
    failed=1
fi

if [ -f "keyboards/rattusboard/config.h" ]; then
    echo "✅ Keyboard configuration found"
else
    echo "❌ Keyboard configuration missing"
    failed=1
fi

if [ -f "keyboards/rattusboard/info.json" ]; then
    echo "✅ Keyboard info.json found"
else
    echo "❌ Keyboard info.json missing"
    failed=1
fi

# Test 3: Try QMK setup (if not already done)
echo ""
echo "⚙️  Testing QMK setup..."
if [ -d "qmk_firmware" ]; then
    echo "✅ QMK firmware directory exists"
else
    echo "⚠️  QMK setup may be needed - run: qmk setup -y"
fi

# Test 4: Test compilation (basic validation)
echo ""
echo "🔨 Testing configuration validation..."
if python3 -c "
import json
try:
    with open('keyboards/rattusboard/info.json', 'r') as f:
        data = json.load(f)
    print('✅ Keyboard info.json is valid JSON')
    print(f'✅ Keyboard name: {data.get(\"keyboard_name\", \"Unknown\")}')
    print(f'✅ Processor: {data.get(\"processor\", \"Unknown\")}')
except Exception as e:
    print(f'❌ Keyboard info.json validation failed: {e}')
    exit(1)
" 2>/dev/null; then
    echo "✅ Configuration validation successful"
else
    echo "⚠️  Configuration validation failed"
    failed=1
fi

# Summary
echo ""
echo "📊 Test Summary"
echo "==============="
if [ $failed -eq 0 ]; then
    echo "🎉 All tests passed! Environment is ready for development."
    echo ""
    echo "Quick start commands:"
    echo "  qmk setup -y                           # Set up QMK firmware"
    echo "  qmk compile -kb rattusboard -km default # Compile firmware"
    echo ""
    echo "Configuration files:"
    echo "  keyboards/rattusboard/config.h         # Hardware configuration"
    echo "  keyboards/rattusboard/info.json        # Keyboard definition"
    echo "  HALVES_WIRING.md                       # Wiring guide"
else
    echo "⚠️  Some tests failed. Please check the setup."
    echo ""
    echo "Troubleshooting:"
    echo "  - Try running: qmk setup -y"
    echo "  - Check if you're in the correct directory: /workspace"
    echo "  - Restart the Codespace if issues persist"
fi

echo ""
echo "For help, see: https://github.com/Rattus-ukrizovany/RattusBoard"