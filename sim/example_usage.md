# RattusBoard Simulation Example Usage

This file demonstrates typical usage scenarios for the RattusBoard simulation environment.

## Scenario 1: Basic Firmware Testing

```bash
# Build the development environment
docker build -t rattusboard-dev .

# Start container and build firmware
docker run -it --rm -v $(pwd):/workspace -w /workspace rattusboard-dev bash
cd /workspace
qmk compile -kb rattusboard -km default

# Start simulation (inside container)
renode sim/rattusboard.resc
```

In the Renode console:
```
# Load the compiled firmware
sysbus LoadELF @.build/rattusboard_default.elf

# Start the simulation
start

# Test left half matrix
test_matrix_left

# Test right half with trackball
configure_right
test_matrix_right
test_trackball
```

## Scenario 2: Split Communication Testing

```
# Configure as left half (master)
configure_left

# Simulate keypress
gpio.left_col0 Press
gpio.matrix_row0 Press
sleep 0.1
gpio.left_col0 Release
gpio.matrix_row0 Release

# Test split communication
test_split_comm

# Switch to right half simulation
configure_right
test_trackball
test_encoder
```

## Scenario 3: Encoder and Trackball Validation

```
# Set up right half
configure_right

# Test encoder clockwise
gpio.encoder_a Press
sleep 0.01
gpio.encoder_b Press
sleep 0.01
gpio.encoder_a Release
sleep 0.01
gpio.encoder_b Release

# Test trackball SPI communication
gpio.pmw3360_cs Press
sleep 0.01
gpio.pmw3360_cs Release

# Monitor SPI transactions
logLevel 0 spi0
```

## Scenario 4: Development Workflow

```bash
# 1. Make firmware changes
# Edit keyboards/rattusboard/keymap.c or other files

# 2. Rebuild
qmk compile -kb rattusboard -km default

# 3. Reload in simulation
machine Reset
sysbus LoadELF @.build/rattusboard_default.elf
start

# 4. Test specific feature
test_matrix_left
demo_keyboard_sequence

# 5. Debug if needed
logLevel 0 gpio
monitor gpio.matrix_row0
```

## Hardware Pin Reference

For development reference, here's the complete pin mapping:

**Matrix (Both Halves)**:
- Rows: GP2, GP3, GP4, GP5

**Left Half**:
- Columns: GP9, GP10, GP11, GP12, GP13, GP14
- Hand detect: GP21 → GND (low)

**Right Half**:
- Columns: GP15, GP16, GP17, GP18, GP19, GP20  
- Hand detect: GP21 → Float (high)
- PMW3360: CS=GP22, SCK=GP23, MOSI=GP24, MISO=GP25
- Encoder: A=GP26, B=GP27

**Communication**:
- Split serial: GP1 (both halves)
- Status LED: GP28