// Copyright 2023 Danny Nguyen (danny@keeb.io)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SPLIT_HAND_PIN GP4
#define USB_VBUS_PIN GP8
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP12
#define SERIAL_USART_RX_PIN GP13
#define SERIAL_USART_PIN_SWAP
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U
#define I2C_DRIVER I2CD2
#define I2C1_SDA_PIN GP10
#define I2C1_SCL_PIN GP11

// RGB Matrix
#define RGB_MATRIX_LED_COUNT 68
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

#define SPLIT_LAYER_STATE_ENABLE

// Copied over from getreur. Might not be needed.
// Unfortunately, some applications drop or misorder fast key events. This is a
// partial fix to slow down the rate at which macros are sent.
// #define TAP_CODE_DELAY 12

// Tap-hold configuration for home row mods.
#define TAPPING_TERM 175
#define TAPPING_TERM_PER_KEY
#define QUICK_TAP_TERM_PER_KEY
#define ACHORDION_STREAK

// This is useful if you have a very high tapping term; otherwise, misfires are common.
// #define PERMISSIVE_HOLD

// These are highly discouraged for home row mods; putting these here to make 
// note of them for future reference.
// #define HOLD_ON_OTHER_KEY_PRESS
// #define RETRO_TAPPING