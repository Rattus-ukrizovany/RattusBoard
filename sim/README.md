# RattusBoard Simulation Files

This directory contains the Renode simulation environment for the RattusBoard split keyboard.

## Files

- **`rattusboard.repl`** - Platform description file defining the RP2040 hardware layout
- **`rattusboard.resc`** - Main simulation script with interactive test macros
- **`test_simulation.resc`** - Quick validation test for the simulation environment

## Quick Start

From the repository root directory:

```bash
# Start interactive simulation
renode sim/rattusboard.resc

# Run validation test
renode sim/test_simulation.resc
```

## Loading Firmware

After starting the simulation:

```
# In Renode monitor console
sysbus LoadELF @.build/rattusboard_default.elf
start
```

## Available Test Commands

- `test_matrix_left` - Test left half key matrix
- `test_matrix_right` - Test right half key matrix  
- `test_trackball` - Test PMW3360 trackball sensor
- `test_encoder` - Test rotary encoder
- `configure_left` - Set hand detection for left half
- `configure_right` - Set hand detection for right half
- `demo_keyboard_sequence` - Run comprehensive demo

See [SIMULATION.md](../SIMULATION.md) for complete documentation.