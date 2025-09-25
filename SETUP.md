# RattusBoard Development Setup Guide

This guide provides step-by-step instructions for setting up a complete development environment for RattusBoard.

## Quick Start (Recommended)

For the fastest setup, run our automated setup script:

```bash
bash setup-qmk.sh
```

This script will:
- Install QMK CLI and dependencies
- Clone QMK firmware repository
- Set up RattusBoard keyboard configuration
- Test compilation
- Install development tools (ARM GCC, build tools)

## Manual Setup (Alternative)

If you prefer to set up manually or need to troubleshoot:

### 1. Install Development Tools

```bash
# Install Python and QMK CLI
python3 -m pip install --user qmk
echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc
export PATH="$HOME/.local/bin:$PATH"

# Install ARM GCC toolchain
sudo apt-get update
sudo apt-get install -y gcc-arm-none-eabi libnewlib-arm-none-eabi

# Install QMK dependencies
sudo apt-get install -y avr-libc gcc-avr avrdude dfu-util dfu-programmer

# Install Renode for simulation (optional)
wget https://github.com/renode/renode/releases/download/v1.16.0/renode-1.16.0.linux-portable.tar.gz
tar -xzf renode-1.16.0.linux-portable.tar.gz
sudo mv renode_1.16.0_portable /opt/renode
sudo ln -sf /opt/renode/renode /usr/local/bin/renode
```

### 2. Set Up QMK Firmware

```bash
# Clone QMK firmware (shallow clone for faster setup)
git clone --depth 1 https://github.com/qmk/qmk_firmware.git
cd qmk_firmware

# Initialize required submodules
git submodule update --init --recursive lib/chibios lib/pico-sdk platforms/chibios

# Set QMK home
export QMK_HOME="$(pwd)"
echo "export QMK_HOME=\"$(pwd)\"" >> ~/.bashrc

# Copy RattusBoard keyboard configuration
cp -r ../keyboards/rattusboard keyboards/
```

### 3. Configure QMK

```bash
# Set default keyboard and keymap
qmk config user.keyboard=rattusboard
qmk config user.keymap=default
```

## Building Firmware

### Using QMK CLI (Recommended)

```bash
cd qmk_firmware
qmk compile -kb rattusboard -km default
```

### Using Make (Alternative)

```bash
cd qmk_firmware
make rattusboard:default
```

Built firmware files will be in the `.build/` directory:
- `rattusboard_default.uf2` - Flash this to your keyboard
- `rattusboard_default.elf` - Use this for Renode simulation

## Testing Your Setup

Run the environment test to verify everything is working:

```bash
bash .devcontainer/test-environment.sh
```

This will check:
- ✅ Required tools (QMK CLI, ARM GCC, Renode)
- ✅ Repository structure
- ✅ QMK setup status
- ✅ Firmware compilation

## Simulation with Renode

Start an interactive simulation session:

```bash
renode sim/rattusboard.resc
```

Or run automated tests:

```bash
bash .devcontainer/test-firmware-renode.sh -t
```

## Troubleshooting

### QMK CLI Not Found
```bash
python3 -m pip install --user qmk
export PATH="$HOME/.local/bin:$PATH"
```

### Keyboard Not Recognized
If `qmk compile -kb rattusboard -km default` fails:

1. Ensure the keyboard is copied (not symlinked) to `qmk_firmware/keyboards/rattusboard`
2. Try using make instead: `make rattusboard:default`
3. Check that all required files exist:
   - `keyboards/rattusboard/info.json`
   - `keyboards/rattusboard/rules.mk`
   - `keyboards/rattusboard/keymaps/default/keymap.c`

### Compilation Errors
- Ensure all submodules are initialized: `git submodule update --init --recursive`
- Install missing dependencies: `sudo apt-get install -y avr-libc gcc-avr`
- Check `qmk doctor` output for missing tools

### Simulation Issues
- Ensure Renode is installed and in PATH: `which renode`
- Check that simulation files exist: `ls sim/rattusboard.resc sim/rattusboard.repl`
- Try compiling firmware first to generate ELF file

## Development Workflow

1. **Edit Code**: Modify keyboard configuration in `keyboards/rattusboard/`
2. **Build**: Run `qmk compile -kb rattusboard -km default`
3. **Test**: Flash firmware to hardware or run in Renode simulation
4. **Debug**: Use Renode for interactive debugging and testing

## IDE Setup

For VS Code users, install these extensions:
- C/C++ Extension Pack
- Python
- CMake Tools
- HexEditor (for firmware files)

The repository includes VS Code configuration in `.devcontainer/devcontainer.json`.

## Getting Help

- 📖 [QMK Documentation](https://docs.qmk.fm/)
- 🔧 [Renode Documentation](https://renode.readthedocs.io/)
- 🐛 [RattusBoard Issues](https://github.com/Rattus-ukrizovany/RattusBoard/issues)
- 💬 [QMK Discord](https://discord.gg/Uq7gcHh)

For RattusBoard-specific issues, please [open an issue](https://github.com/Rattus-ukrizovany/RattusBoard/issues/new/choose) on GitHub.