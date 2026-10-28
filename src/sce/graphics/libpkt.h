/* SPDX-License-Identifier: CC0-1.0 */
/* libpkt GIF packet builder (the census's 11 sceGifPk* functions).
 * Signatures follow the game's own declarations (e.g. GsUploadImage16Blocks,
 * FixedTexUploadImpl), which pass the REF address as a 64-bit value and the
 * GIFtag by value as a 128-bit integer. */
#ifndef RG_SCE_LIBPKT_H
#define RG_SCE_LIBPKT_H

#include <stdint.h>

#include "port/u128.h"

#ifdef __cplusplus
extern "C" {
#endif
/* x64 (docs/X64-PLAN.md): SDK structs live in game memory with 4-byte pointers */
#ifndef SCE_P32
#if defined(_WIN64)
#define SCE_P32 __ptr32 __uptr
#else
#define SCE_P32
#endif
#endif

typedef struct sceGifPacket {
    uint32_t * SCE_P32 pCurrent; /* 0x0 next free word */
    void * SCE_P32 pBase;        /* 0x4 */
    uint32_t * SCE_P32 pDmaTag;  /* 0x8 open CNT/END tag whose QWC Terminate fills in */
    uint64_t * SCE_P32 pGifTag;  /* 0xC open GIFtag whose NLOOP CloseGifTag fills in */
} sceGifPacket;

void sceGifPkInit(sceGifPacket *pk, void *base);
void *sceGifPkReset(sceGifPacket *pk);
uint32_t *sceGifPkTerminate(sceGifPacket *pk);
void sceGifPkCnt(sceGifPacket *pk, uint32_t opt1, uint32_t opt2, uint32_t flag);
void sceGifPkRef(sceGifPacket *pk, uint64_t addr, uint32_t size, uint32_t opt1, uint32_t opt2, uint32_t flag);
void sceGifPkEnd(sceGifPacket *pk, uint32_t opt1, uint32_t opt2, uint32_t flag);
uint32_t *sceGifPkReserve(sceGifPacket *pk, uint32_t words);
uint32_t *sceGifPkOpenGifTag(sceGifPacket *pk, rg_u128 giftag);
void sceGifPkCloseGifTag(sceGifPacket *pk);
void sceGifPkAddGsAD(sceGifPacket *pk, uint32_t addr, uint64_t data);
void sceGifPkRefLoadImage(sceGifPacket *pk, uint16_t bp, uint8_t psm, uint16_t bw, const void *image,
                          uint32_t qwc, uint32_t x, uint32_t y, uint32_t w, uint32_t h);

#ifdef __cplusplus
}
#endif
#endif
