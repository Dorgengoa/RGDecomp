/* SPDX-License-Identifier: CC0-1.0 */
/* Force-included (-include) into the reused tests/gs golden-scene sources:
 * every GS entry point those tests call is renamed to a tee that drives the
 * software reference AND a shadow gs_state rendered by the GPU renderer, and
 * every read the test makes becomes a comparison checkpoint (gpu_tee.c). */
#ifndef RG_GPU_TEE_H
#define RG_GPU_TEE_H

#define gs_create tee_gs_create
#define gs_destroy tee_gs_destroy
#define gs_reset tee_gs_reset
#define gs_gif_write tee_gs_gif_write
#define gs_vu1_gif_sink tee_gs_vu1_gif_sink
#define gs_vif1_gif_sink tee_gs_vif1_gif_sink
#define gs_write_reg tee_gs_write_reg
#define gs_write_priv tee_gs_write_priv
#define gs_vsync tee_gs_vsync
#define gs_write_pixel tee_gs_write_pixel
#define gs_read_pixel tee_gs_read_pixel
#define gs_read_rect_rgba tee_gs_read_rect_rgba
#define gs_read_display tee_gs_read_display
#define gs_read_fifo tee_gs_read_fifo

#endif
