// Copyright 2024 RattusBoard Project  
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#define HAL_USE_SPI TRUE
#define HAL_USE_PAL TRUE
#define PAL_USE_CALLBACKS TRUE
#define PAL_USE_WAIT TRUE

#include_next <halconf.h>