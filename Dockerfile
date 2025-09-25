# RattusBoard Development Environment with Renode
# Copyright 2024 RattusBoard Project  
# SPDX-License-Identifier: GPL-3.0-or-later
#
# Dockerfile for reproducible RattusBoard development with Renode simulation
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

# Create non-root user for development
RUN useradd -m -u 1000 -s /bin/bash developer \
    && usermod -aG dialout developer

# Set up Python environment for QMK
USER developer
WORKDIR /home/developer

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
RUN mkdir -p /home/developer/rattusboard \
    && mkdir -p /home/developer/.local/share/qmk

# Set environment variables
ENV PATH="/home/developer/.local/bin:$PATH"
ENV QMK_HOME="/home/developer/rattusboard"

# Switch back to root for final setup
USER root

# Install RP2040 specific tools
RUN wget https://github.com/raspberrypi/pico-sdk/archive/refs/tags/1.5.1.tar.gz \
    && tar -xzf 1.5.1.tar.gz \
    && mv pico-sdk-1.5.1 /opt/pico-sdk \
    && rm 1.5.1.tar.gz

# Set up Pico SDK environment
ENV PICO_SDK_PATH="/opt/pico-sdk"

# Create startup script
RUN printf '#!/bin/bash\n\
echo "RattusBoard Development Environment"\n\
echo "=================================="\n\
echo ""\n\
echo "Available tools:"\n\
echo "  renode                 - Start Renode simulator"\n\
echo "  qmk                    - QMK command line interface"\n\
echo "  arm-none-eabi-gcc      - ARM cross-compiler"\n\
echo ""\n\
echo "Simulation files:"\n\
echo "  rattusboard.repl       - Platform description"\n\
echo "  rattusboard.resc       - Simulation script"\n\
echo ""\n\
echo "Quick start:"\n\
echo "  1. cd /workspace"\n\
echo "  2. qmk compile -kb rattusboard -km default"\n\
echo "  3. renode rattusboard.resc"\n\
echo ""\n' > /usr/local/bin/rattusboard-dev \
    && chmod +x /usr/local/bin/rattusboard-dev

# Install VS Code extensions helper
RUN printf '#!/bin/bash\n\
echo "Installing recommended VS Code extensions..."\n\
code --install-extension ms-vscode.cpptools\n\
code --install-extension ms-python.python\n\
code --install-extension ms-dotnettools.csharp\n\
code --install-extension QMK.qmk\n\
echo "Extensions installed!"\n' > /usr/local/bin/install-vscode-extensions \
    && chmod +x /usr/local/bin/install-vscode-extensions

# Set up working directory permissions
RUN chown -R developer:developer /home/developer

# Switch to developer user for runtime
USER developer
WORKDIR /home/developer

# Default command shows help
CMD ["rattusboard-dev"]

# Health check to verify Renode installation
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD renode --version || exit 1

# Labels for container metadata
LABEL org.opencontainers.image.title="RattusBoard Development Environment"
LABEL org.opencontainers.image.description="Complete development environment for RattusBoard with Renode simulation"
LABEL org.opencontainers.image.source="https://github.com/Rattus-ukrizovany/RattusBoard"
LABEL org.opencontainers.image.licenses="GPL-3.0-or-later"
LABEL org.opencontainers.image.version="1.0.0"