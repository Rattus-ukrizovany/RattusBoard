// Copyright 2024 RattusBoard Project
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include_next <mcuconf.h>

// Enable SPI for PMW3360 trackball sensor
#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 TRUE

// SPI configuration for optimal PMW3360 performance
#undef RP_SPI_SPI0_RX_DMA_STREAM
#define RP_SPI_SPI0_RX_DMA_STREAM 0

#undef RP_SPI_SPI0_TX_DMA_STREAM  
#define RP_SPI_SPI0_TX_DMA_STREAM 1