/*
 * Copyright (c) 2026 catfact
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief STM32 LTDC driver extensions (L8 colour lookup table).
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_DISPLAY_STM32_LTDC_H_
#define ZEPHYR_INCLUDE_DRIVERS_DISPLAY_STM32_LTDC_H_

#include <stddef.h>
#include <stdint.h>
#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Number of entries in the LTDC layer colour lookup table. */
#define STM32_LTDC_CLUT_ENTRIES 256U

/**
 * @brief Update entries of the layer 1 colour lookup table (L8 mode).
 *
 * Entries are 0x00RRGGBB (the LTDC CLUT has no alpha; bits 31..24 are ignored).
 * The hardware CLUT may only be written during vertical blanking, so the new
 * entries are applied from the LTDC line interrupt at the next blanking period
 * and this call blocks until then (at most one frame).
 *
 * @param dev     LTDC display device.
 * @param entries Colours for CLUT indices [first, first + count).
 * @param first   First CLUT index to update.
 * @param count   Number of entries; first + count must not exceed 256.
 *
 * @retval 0 on success.
 * @retval -EINVAL on bad arguments.
 * @retval -ETIMEDOUT if no blanking period occurred (LTDC not running);
 *         the entries are retained and applied on the next update or re-init.
 */
int stm32_ltdc_set_clut(const struct device *dev, const uint32_t *entries,
			size_t first, size_t count);

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_DRIVERS_DISPLAY_STM32_LTDC_H_ */
