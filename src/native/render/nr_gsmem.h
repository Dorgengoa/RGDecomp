/* SPDX-License-Identifier: CC0-1.0 */
/* GS local-memory address arithmetic for the native renderer (docs/NATIVE-RENDER.md
 * "Checkpoint 10"): where a pixel of a buffer (bp, bw, psm) lies in the 4 MB the GPU holds
 * (the mirror).  The swizzle as a decode step of the game's data, not a memory model: no
 * memory is read or written here.  Same bit formulas as src/ps2/gs/gs_mem.c and
 * src/gpu/shaders/gs_common.hlsli (checked against the manual's figures by tests/gs). */
#ifndef RG_NR_GSMEM_H
#define RG_NR_GSMEM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* byte address of pixel (x, y); for 4-bit formats the byte holding the nibble and
 * *nib (may be NULL) = 0 low / 1 high.  T8H / T4HL / T4HH: the address of the 32-bit word
 * (their bits are 24-31 / 24-27 / 28-31 of it). */
uint32_t nr_px_addr(int psm, uint32_t bp, uint32_t bw, uint32_t x, uint32_t y, int *nib);
/* bits per pixel in transfers (4 / 8 / 16 / 24 / 32), 0 if invalid */
int nr_psm_bpp(int psm);
/* the 32-bit word index (addr >> 2) and the bit mask of that word a pixel occupies */
void nr_px_word(int psm, uint32_t bp, uint32_t bw, uint32_t x, uint32_t y, uint32_t *word, uint32_t *mask,
                uint32_t *shift);

#ifdef __cplusplus
}
#endif
#endif
