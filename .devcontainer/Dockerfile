# RattusBoard Development Environment for GitHub Codespaces
# Copyright 2024 RattusBoard Project  
# SPDX-License-Identifier: GPL-3.0-or-later
#
# Optimized Dockerfile for GitHub Codespaces with Renode simulation
# Includes QMK build tools, ARM toolchain, and Renode for RP2040 simulation

FROM ubuntu:22.04

# Avoid interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

# Install base packages and dependencies
RUN apt-get update && apt-get install -y \
    # Basic build tools
    build-essential \
    cmake \
    ninja-build \
    git \
    curl \
    wget \
    unzip \
    python3 \
    python3-pip \
    python3-venv \
    # ARM development tools
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    # QMK dependencies
    avr-libc \
    gcc-avr \
    # Additional utilities
    udev \
    dfu-util \
    dfu-programmer \
    avrdude \
    # .NET dependencies for Renode
    software-properties-common \
    gpg-agent \
    # Development utilities for Codespaces
    nano \
    vim \
    sudo \
    less \
    tree \
    htop \
    && rm -rf /var/lib/apt/lists/*

# Install .NET 6.0 (required for Renode)
RUN wget https://packages.microsoft.com/config/ubuntu/22.04/packages-microsoft-prod.deb -O packages-microsoft-prod.deb \
    && dpkg -i packages-microsoft-prod.deb \
    && rm packages-microsoft-prod.deb \
    && apt-get update \
    && apt-get install -y dotnet-sdk-6.0 \
    && rm -rf /var/lib/apt/lists/*

# Install Renode
ENV RENODE_VERSION=1.14.0
RUN wget https://github.com/renode/renode/releases/download/v${RENODE_VERSION}/renode-${RENODE_VERSION}.linux-portable.tar.gz \
    && tar -xzf renode-${RENODE_VERSION}.linux-portable.tar.gz \
    && mv renode_${RENODE_VERSION}_portable /opt/renode \
    && rm renode-${RENODE_VERSION}.linux-portable.tar.gz \
    && ln -s /opt/renode/renode /usr/local/bin/renode \
    && ln -s /opt/renode/renode-test /usr/local/bin/renode-test

# Create developer user for Codespaces compatibility
ARG USERNAME=developer
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && echo "$USERNAME:$USERNAME" | chpasswd \
    && usermod -aG sudo $USERNAME \
    && usermod -aG dialout $USERNAME \
    && echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Set up Python environment for QMK
USER $USERNAME
WORKDIR /home/$USERNAME

# Install QMK CLI and dependencies
RUN python3 -m pip install --user qmk \
    && echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc

# Install additional Python packages for development
RUN python3 -m pip install --user \
    platformio \
    pyserial \
    pillow \
    hjson

# Create development directories
RUN mkdir -p /home/$USERNAME/.local/share/qmk

# Set environment variables
ENV PATH="/home/$USERNAME/.local/bin:$PATH"

# Switch back to root for final setup
USER root

# Install RP2040 specific tools
RUN wget https://github.com/raspberrypi/pico-sdk/archive/refs/tags/1.5.1.tar.gz \
    && tar -xzf 1.5.1.tar.gz \
    && mv pico-sdk-1.5.1 /opt/pico-sdk \
    && rm 1.5.1.tar.gz

# Set up Pico SDK environment
ENV PICO_SDK_PATH="/opt/pico-sdk"

# Copy and install helper scripts
COPY .devcontainer/download-firmware.sh /usr/local/bin/rattusboard-download-firmware
COPY .devcontainer/test-firmware-renode.sh /usr/local/bin/rattusboard-test-firmware
RUN chmod +x /usr/local/bin/rattusboard-download-firmware /usr/local/bin/rattusboard-test-firmware

# Create startup script for easy usage
RUN printf '#!/bin/bash\n\
echo "RattusBoard Development Environment for GitHub Codespaces"\n\
echo "========================================================"\n\
echo ""\n\
echo "Available tools:"\n\
echo "  renode                         - Start Renode simulator"\n\
echo "  qmk                            - QMK command line interface"\n\
echo "  arm-none-eabi-gcc              - ARM cross-compiler"\n\
echo "  rattusboard-download-firmware  - Download latest firmware from GitHub"\n\
echo "  rattusboard-test-firmware      - Download and test firmware in Renode"\n\
echo ""\n\
echo "Quick start:"\n\
echo "  1. rattusboard-test-firmware   # Download and test firmware in one command"\n\
echo "  2. qmk compile -kb rattusboard -km default  # Compile locally"\n\
echo "  3. renode sim/rattusboard.resc  # Manual Renode simulation"\n\
echo ""\n\
echo "Firmware testing:"\n\
echo "  rattusboard-download-firmware -l          # List available firmware"\n\
echo "  rattusboard-download-firmware             # Download default firmware"\n\
echo "  rattusboard-test-firmware -i              # Interactive Renode session"\n\
echo "  rattusboard-test-firmware -t              # Automated tests only"\n\
echo ""\n\
echo "Simulation files:"\n\
echo "  sim/rattusboard.repl   - Platform description"\n\
echo "  sim/rattusboard.resc   - Simulation script"\n\
echo ""\n\
echo "Happy coding! 🐭⌨️"\n' > /usr/local/bin/rattusboard-dev \
    && chmod +x /usr/local/bin/rattusboard-dev

# Set up working directory permissions for workspace mount
RUN mkdir -p /workspace \
    && chown -R $USERNAME:$USERNAME /workspace

# Switch to developer user for runtime
USER $USERNAME
WORKDIR /workspace

# Health check to verify Renode installation
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD renode --version || exit 1

# Labels for container metadata
LABEL org.opencontainers.image.title="RattusBoard Codespaces Environment"
LABEL org.opencontainers.image.description="GitHub Codespaces environment for RattusBoard with Renode simulation"
LABEL org.opencontainers.image.source="https://github.com/Rattus-ukrizovany/RattusBoard"
LABEL org.opencontainers.image.licenses="GPL-3.0-or-later"
LABEL org.opencontainers.image.version="1.0.0"

# Default command shows help
CMD ["/bin/bash"]