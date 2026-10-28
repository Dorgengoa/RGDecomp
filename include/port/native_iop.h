/* SPDX-License-Identifier: CC0-1.0 */
/* Game-side view of the native IOP lane (src/native/iop/rg_iop.h, docs/NATIVE-IOP.md),
 * for the overrides of the game's IOP boot functions.  Plain C only, so it can be
 * included next to the game's types.h. */
#ifndef RG_PORT_NATIVE_IOP_H
#define RG_PORT_NATIVE_IOP_H

#ifdef __cplusplus
extern "C" {
#endif

/* 1: RG_IOP=native (default): no IOP / SIF exists; 0: the IOP/SIF HLE (oracle). */
int rg_iop_native(void);

#ifdef __cplusplus
}
#endif
#endif
