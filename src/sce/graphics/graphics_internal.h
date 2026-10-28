/* SPDX-License-Identifier: CC0-1.0 */
/* Shared state of src/sce/graphics (not an SDK header). */
#ifndef RG_SCE_GRAPHICS_INTERNAL_H
#define RG_SCE_GRAPHICS_INTERNAL_H

#include "libdma.h"
#include "libgraph.h"

extern dmac_state *g_rg_dmac;
extern gs_state *g_rg_gs;

/* DmaWaitChannelIdle: never spins.  Runs held work; a channel that is still
 * held is reported and stopped, as retail does after its 16M-poll timeout.
 * Returns 0 if idle, -1 if it had to be stopped. */
int rg_dma_wait_idle(int ch);
/* libdma's DmaAddrFromSpr for a host pointer / address argument */
uint32_t rg_dma_addr(const void *p);
/* a polled status that reads "busy" lets virtual time pass (docs/SPIN.md) */
void rg_poll_charge(void);
#if RG_GRAPHICS_NATIVE
/* libdma_native.c: CHCR written with STR on channel ch (the transfer runs at the call) */
int rg_dma_start(int ch, uint32_t chcr);
#endif

#endif
