/* SPDX-License-Identifier: CC0-1.0 */
/* Shared between the src/sce/sif translation units. Not a public header. */
#ifndef SCE_SIF_INTERNAL_H
#define SCE_SIF_INTERNAL_H

#include <stdint.h>

#include "rg_iop.h" /* RG_IOP switch + census (docs/NATIVE-IOP.md) */

#define DMAC_CH_SIF0 5

/* RG_IOP=native: every SDK entry answers without src/ps2/sif or src/ps2/iop (the
 * "no IOP" contract: boot/sync succeed, modules get ids, registers read as booted;
 * RPC / DMA / heap / sdremote have no native meaning and are counted as
 * unconverted).  Defined in sif_ee.c. */
uint32_t sif_native_reg_get(uint32_t reg);
uint32_t sif_native_reg_set(uint32_t reg, uint32_t v);

void sif_ee_ensure_boot(void);      /* rg_sif_boot(NULL) once + DMAC SIF0 handler */
int sif_ee_can_block(void);         /* on a guest thread, kernel in use, not in a handler */
void sif_ee_wait_idle(void);        /* make progress on queued SIF events */
void sif_ee_reset_clients(void);
/* Synchronous RPC used by the SDK wrappers (fileio, iopheap, loadfile, sdremote).
 * 0 ok, -1 unknown server (reported by the core). */
int sif_ee_rpc_sync(uint32_t sid, uint32_t fno, const void *send, uint32_t ssize, void *recv, uint32_t rsize);

void fio_reset_client(void); /* fileio.c */
void sdr_reset(void);        /* libsdr.c */

#endif
