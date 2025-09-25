# RattusBoard Simulation Environment

This document explains how to build firmware and run the RattusBoard in the Renode simulation environment for development and testing.

## Overview

The RattusBoard simulation environment provides:
- **Renode platform description** (`rattusboard.repl`) matching the RP2040 hardware
- **Simulation script** (`rattusboard.resc`) with interactive testing macros
- **Dockerized environment** with all required tools pre-installed
- **Hardware-accurate GPIO mapping** based on the actual board configuration

## Quick Start

### Option 1: GitHub Codespaces (Recommended)

The easiest way to get started is using GitHub Codespaces with our pre-configured development environment:

1. **Open in Codespaces**: Click the green "Code" button in the GitHub repository and select "Open with Codespaces"
2. **Wait for setup**: The environment will automatically install QMK, Renode, and all dependencies (~2-3 minutes)
3. **Compile firmware**: Run `qmk compile -kb rattusboard -km default`
4. **Start simulation**: Run `renode sim/rattusboard.resc`

```bash
# Quick commands for Codespaces:
qmk compile -kb rattusboard -km default
renode sim/rattusboard.resc

# Or use the helper script:
rattusboard-dev
```

**Features included in Codespaces:**
- ✅ Pre-installed Renode 1.14.0 with RP2040 support
- ✅ QMK CLI and ARM toolchain ready to use
- ✅ VS Code extensions for C/C++, Python, and QMK
- ✅ Configured workspace with proper paths and settings
- ✅ One-click setup - no local installation required

### Option 2: Using Docker

```bash
# Build the development environment
docker build -t rattusboard-dev .

# Run the container with workspace mounted
docker run -it --rm \
  -v $(pwd):/workspace \
  -w /workspace \
  rattusboard-dev

# Inside the container, start Renode simulation
renode sim/rattusboard.resc
```

### Option 3: Local Installation

```bash
# Install Renode (Linux)
wget https://github.com/renode/renode/releases/download/v1.14.0/renode-1.14.0.linux-portable.tar.gz
tar -xzf renode-1.14.0.linux-portable.tar.gz
sudo mv renode_1.14.0_portable /opt/renode
sudo ln -s /opt/renode/renode /usr/local/bin/renode

# Install QMK and ARM toolchain
pip3 install qmk
sudo apt install gcc-arm-none-eabi

# Start simulation
renode sim/rattusboard.resc
```

## Hardware Configuration

The simulation accurately models the RattusBoard hardware based on `config.h` and `HALVES_WIRING.md`:

### Left Half (Master)
- **MCU**: RP2040 (Raspberry Pi Pico)
- **Matrix Rows**: GP2, GP3, GP4, GP5 (4 rows)
- **Matrix Cols**: GP9, GP10, GP11, GP12, GP13, GP14 (6 columns)
- **Split Communication**: GP1 (SOFT_SERIAL_PIN)
- **Hand Detection**: GP21 → GND (identifies as left half)
- **USB Connection**: Native USB for host communication

### Right Half (Slave)  
- **MCU**: RP2040 (Raspberry Pi Pico)
- **Matrix Rows**: GP2, GP3, GP4, GP5 (4 rows)
- **Matrix Cols**: GP15, GP16, GP17, GP18, GP19, GP20 (6 columns)
- **PMW3360 Trackball**: SPI interface
  - CS: GP22, SCK: GP23, MOSI: GP24, MISO: GP25
- **Rotary Encoder**: GP26 (A phase), GP27 (B phase)
- **Hand Detection**: GP21 → Float (identifies as right half)

### Additional Hardware
- **Status LED**: GP28 (bootloader reset indicator)
- **Motion Interrupt**: GP29 (optional PMW3360 interrupt)
- **Diode Direction**: COL2ROW
- **Split Protocol**: Soft serial over TRRS cable

## Building Firmware

### QMK Firmware Build

```bash
# Set up QMK (first time only)
qmk setup

# Compile RattusBoard firmware
qmk compile -kb rattusboard -km default

# The output will be in .build/rattusboard_default.elf
```

### Custom Keymap Build

```bash
# Create custom keymap
qmk new-keymap -kb rattusboard

# Edit your keymap in keyboards/rattusboard/keymaps/your_name/

# Compile custom keymap
qmk compile -kb rattusboard -km your_name
```

## Running Simulation

### 1. Start Renode with RattusBoard Configuration

```bash
# Start Renode with our simulation script
renode sim/rattusboard.resc
```

This will:
- Load the platform description matching RP2040 hardware
- Initialize GPIO pins according to the hardware configuration
- Set up interactive test macros
- Display the test menu

### 2. Load Firmware

In the Renode monitor console:

```
# Load compiled firmware
sysbus LoadELF @.build/rattusboard_default.elf

# Start the simulation
start
```

### 3. Interactive Testing

The simulation provides several test macros:

```
# Test left half matrix
test_matrix_left

# Test right half matrix  
test_matrix_right

# Test PMW3360 trackball sensor
test_trackball

# Test rotary encoder
test_encoder

# Test split communication
test_split_comm

# Configure as left/right half
configure_left
configure_right

# Run comprehensive demo
demo_keyboard_sequence
```

## Test Scenarios

### Matrix Testing

Test individual keys and key combinations:

```
# Press key at row 0, col 0 on left half
gpio.left_col0 Press
gpio.matrix_row0 Press
sleep 0.1
gpio.left_col0 Release
gpio.matrix_row0 Release

# Test right half key
gpio.right_col0 Press  
gpio.matrix_row0 Press
sleep 0.1
gpio.right_col0 Release
gpio.matrix_row0 Release
```

### Trackball Testing

Simulate PMW3360 sensor interactions:

```
# Simulate SPI communication
gpio.pmw3360_cs Press
sleep 0.01
gpio.pmw3360_cs Release

# Inject motion data
pmw3360 SetMotion 10 -5  # X=10, Y=-5 movement
```

### Encoder Testing

Test rotary encoder rotation:

```
# Clockwise rotation
gpio.encoder_a Press
sleep 0.01
gpio.encoder_b Press  
sleep 0.01
gpio.encoder_a Release
sleep 0.01
gpio.encoder_b Release

# Counter-clockwise rotation
gpio.encoder_b Press
sleep 0.01
gpio.encoder_a Press
sleep 0.01  
gpio.encoder_b Release
sleep 0.01
gpio.encoder_a Release
```

## Advanced Usage

### Debugging Firmware

```bash
# Enable detailed GPIO logging
logLevel 0 gpio

# Enable SPI transaction logging
logLevel 0 spi0

# Monitor specific pins
monitor gpio.matrix_row0
monitor gpio.pmw3360_cs
```

### Custom Test Scripts

Create custom test sequences:

```
macro my_custom_test
"""
    echo "Running custom test..."
    configure_left
    test_matrix_left
    configure_right  
    test_trackball
    test_encoder
    echo "Custom test completed"
"""
```

### Split Keyboard Testing

Test communication between halves:

```
# Simulate left half sending data
configure_left
gpio.split_serial Press
sleep 0.01
gpio.split_serial Release

# Switch to right half to receive
configure_right
# Firmware should process the communication
```

## Troubleshooting

### Common Issues

1. **Firmware not loading**
   ```
   Error: Could not load ELF file
   ```
   - Verify firmware path is correct
   - Ensure firmware was compiled successfully
   - Check file permissions

2. **GPIO not responding**
   ```
   Warning: GPIO pin not found
   ```
   - Verify pin numbers match hardware configuration
   - Check platform description file (rattusboard.repl)

3. **SPI communication failing**
   ```
   Error: SPI transaction timeout
   ```
   - Ensure PMW3360 sensor is properly initialized in platform
   - Check SPI pin configuration

### Debug Commands

```bash
# Check platform status
machine
sysbus

# Examine GPIO state
gpio

# Monitor memory regions
sysbus ReadDoubleWord 0x20000000  # Check SRAM
sysbus ReadDoubleWord 0x10000000  # Check Flash

# Reset simulation
machine Reset
```

## Firmware Validation

### Verification Checklist

- [ ] **Matrix scanning**: All 42 keys register correctly
- [ ] **Split communication**: Data transfers between halves  
- [ ] **Hand detection**: Left/right half identification works
- [ ] **Trackball tracking**: PMW3360 sensor responds to movement
- [ ] **Encoder rotation**: Both clockwise/counter-clockwise detected
- [ ] **USB communication**: Host receives keyboard data
- [ ] **Debouncing**: No ghost keys or matrix issues
- [ ] **Boot sequence**: Firmware initializes correctly

### Performance Testing

```bash
# Test rapid key presses
for i in {1..10}; do test_matrix_left; sleep 0.01; done

# Test continuous trackball movement  
for i in {1..50}; do pmw3360 SetMotion 1 1; sleep 0.02; done

# Test encoder speed
for i in {1..20}; do test_encoder; sleep 0.05; done
```

## Development Workflow

### Typical Development Cycle

1. **Modify firmware** in `keyboards/rattusboard/`
2. **Compile** with `qmk compile -kb rattusboard -km default`
3. **Load in simulation** with `sysbus LoadELF @.build/rattusboard_default.elf`
4. **Test features** using interactive macros
5. **Debug issues** with GPIO monitoring and logging
6. **Repeat** until functionality is verified

### Continuous Integration

The simulation environment can be used in CI/CD pipelines:

```yaml
# Example GitHub Actions workflow
- name: Build and Test Firmware
  run: |
    docker run --rm -v $PWD:/workspace rattusboard-dev bash -c "
      cd /workspace &&
      qmk compile -kb rattusboard -km default &&
      renode --disable-xwt --console rattusboard.resc --execute 'sysbus LoadELF @.build/rattusboard_default.elf; start; sleep 5; quit'
    "
```

## GitHub Codespaces Usage

### Getting Started with Codespaces

GitHub Codespaces provides a cloud-based development environment that's pre-configured for RattusBoard development:

1. **Create Codespace**:
   - Go to the RattusBoard repository on GitHub
   - Click the green "Code" button
   - Select "Codespaces" tab
   - Click "Create codespace on main"

2. **Wait for Setup**:
   - The environment automatically installs all dependencies
   - QMK, Renode, and ARM toolchain are ready to use
   - VS Code opens with recommended extensions

3. **Start Developing**:
   ```bash
   # Compile the default firmware
   qmk compile -kb rattusboard -km default
   
   # Start Renode simulation
   renode sim/rattusboard.resc
   
   # Load firmware in Renode console:
   sysbus LoadELF @.build/rattusboard_default.elf
   start
   ```

### Codespaces Features

- **Pre-configured VS Code**: Extensions for C/C++, Python, QMK, and YAML
- **Syntax highlighting**: Custom file associations for `.resc` and `.repl` files
- **Integrated terminal**: Bash with development tools in PATH
- **Workspace settings**: Properly configured include paths and compiler settings
- **Persistent storage**: Your changes are saved between sessions

### Troubleshooting Codespaces

**Environment not ready?**
```bash
# Check if QMK is available
qmk --version

# Check if Renode is available
renode --version

# Verify ARM compiler
arm-none-eabi-gcc --version
```

**Compilation issues?**
```bash
# Ensure QMK is set up
qmk setup -y

# Set the correct keyboard home
export QMK_HOME=/workspace
```

**Simulation not starting?**
```bash
# Check simulation files exist
ls -la sim/

# Start with verbose output
renode -v sim/rattusboard.resc
```

## Contributing

When modifying the simulation environment:

1. **Update platform description** (`rattusboard.repl`) for hardware changes
2. **Add test macros** (`rattusboard.resc`) for new features  
3. **Update documentation** to reflect changes
4. **Test thoroughly** with various firmware configurations
5. **Validate pin mappings** against hardware documentation

## References

- [Renode Documentation](https://renode.readthedocs.io/)
- [RP2040 Datasheet](https://datasheets.raspberrypi.org/rp2040/rp2040-datasheet.pdf)
- [QMK Documentation](https://docs.qmk.fm/)
- [PMW3360 Datasheet](https://www.pixart.com/products-detail/10/PMW3360DM-T2QU)
- [RattusBoard Hardware Configuration](/keyboards/rattusboard/config.h)
- [Hardware Wiring Guide](/HALVES_WIRING.md)