/* SPDX-License-Identifier: CC0-1.0 */
/* libpkt GIF packet builder.  Each function writes exactly the words the
 * retail asm body writes (game/src/main/sdk/sceGifPk*.c,
 * gs/sceGifPkTerminate_10a420.c), with one deliberate difference: in host
 * memory mode a REF address is a host pointer and is not masked with
 * 0x9FFFFFFF (that would corrupt it); see docs/DMAC.md. */
#include <string.h>

#include "graphics_internal.h"
#include "libpkt.h"

void sceGifPkInit(sceGifPacket *pk, void *base)
{
    pk->pCurrent = (uint32_t *)base;
    pk->pDmaTag = NULL;
    pk->pBase = base;
}

void *sceGifPkReset(sceGifPacket *pk)
{
    pk->pDmaTag = NULL;
    pk->pCurrent = (uint32_t *)pk->pBase;
    return pk->pBase;
}

uint32_t *sceGifPkTerminate(sceGifPacket *pk)
{
    uint32_t *c = pk->pCurrent;
    while ((uintptr_t)c & 0xC) *c++ = 0;
    if (pk->pDmaTag) {
        int32_t qw = (int32_t)(((uint8_t *)c - (uint8_t *)pk->pDmaTag) >> 4) - 1;
        pk->pDmaTag[0] += (uint32_t)qw; /* QWC of the open CNT/END tag */
    }
    pk->pDmaTag = NULL;
    pk->pCurrent = c;
    return c;
}

static void open_tag(sceGifPacket *pk, uint32_t id, uint32_t opt1, uint32_t opt2, uint32_t flag)
{
    uint32_t *c = sceGifPkTerminate(pk);
    pk->pDmaTag = c;
    c[0] = flag | id;
    c[1] = 0;
    c[2] = opt1;
    c[3] = opt2;
    pk->pCurrent = c + 4;
}

void sceGifPkCnt(sceGifPacket *pk, uint32_t opt1, uint32_t opt2, uint32_t flag)
{
    open_tag(pk, 0x10000000u, opt1, opt2, flag);
}

void sceGifPkEnd(sceGifPacket *pk, uint32_t opt1, uint32_t opt2, uint32_t flag)
{
    open_tag(pk, 0x70000000u, opt1, opt2, flag);
}

void sceGifPkRef(sceGifPacket *pk, uint64_t addr, uint32_t size, uint32_t opt1, uint32_t opt2, uint32_t flag)
{
    uint32_t *c = sceGifPkTerminate(pk);
    uint32_t a = (uint32_t)addr;
#if RG_GRAPHICS_NATIVE
    /* the DMA address is the host pointer, whole (docs/NATIVE-RENDER.md "DMA addresses") */
#else
    if (g_rg_dmac && g_rg_dmac->mem_mode == DMAC_MEM_HOST) a = dmac_addr_of(g_rg_dmac, (const void *)(uintptr_t)a);
    else a &= 0x9FFFFFFFu;
#endif
    c[0] = flag | size | 0x30000000u;
    c[1] = a;
    c[2] = opt1;
    c[3] = opt2;
    pk->pCurrent = c + 4;
}

uint32_t *sceGifPkReserve(sceGifPacket *pk, uint32_t words)
{
    uint32_t *c = pk->pCurrent;
    pk->pCurrent = c + words;
    return c;
}

uint32_t *sceGifPkOpenGifTag(sceGifPacket *pk, rg_u128 giftag)
{
    uint32_t *c = pk->pCurrent;
    memcpy(c, &giftag, 16);
    pk->pCurrent = c + 4;
    pk->pGifTag = (uint64_t *)c;
    return c;
}

void sceGifPkCloseGifTag(sceGifPacket *pk)
{
    uint64_t *t = pk->pGifTag;
    uint32_t *c = pk->pCurrent;
    uint64_t lo;
    uint32_t flg, cnt;
    memcpy(&lo, t, 8);
    cnt = (uint32_t)((int32_t)(((uint8_t *)c - (uint8_t *)t) >> 3) - 2); /* 64-bit words after the tag */
    flg = (uint32_t)(lo >> 58) & 3u;
    if (flg != 1) cnt >>= 1;                                             /* qwords */
    if (flg != 2) {
        uint32_t nreg = (uint32_t)(lo >> 60);
        if (!nreg) nreg = 16;
        cnt = (cnt + nreg - 1) / nreg;
    }
    lo += cnt; /* NLOOP (retail adds to the whole word) */
    memcpy(t, &lo, 8);
    pk->pGifTag = NULL;
    while ((uintptr_t)c & 0xC) *c++ = 0;
    pk->pCurrent = c;
}

void sceGifPkAddGsAD(sceGifPacket *pk, uint32_t addr, uint64_t data)
{
    uint32_t *c = pk->pCurrent;
    uint64_t a = addr;
    memcpy(c, &data, 8);
    memcpy(c + 2, &a, 8);
    pk->pCurrent = c + 4;
}

void sceGifPkRefLoadImage(sceGifPacket *pk, uint16_t bp, uint8_t psm, uint16_t bw, const void *image,
                          uint32_t qwc, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    const rg_u128 tmpl = RG_U128(0xE, 1ull << 60); /* retail 0x456080: NREG 1, A+D */
    const uint8_t *src = (const uint8_t *)image;
    sceGifPkCnt(pk, 0, 0, 0);
    sceGifPkOpenGifTag(pk, tmpl);
    sceGifPkAddGsAD(pk, 0x50, ((uint64_t)bp << 32) | ((uint64_t)bw << 48) | ((uint64_t)psm << 56));
    sceGifPkAddGsAD(pk, 0x51, ((uint64_t)x << 32) | ((uint64_t)y << 48));
    sceGifPkAddGsAD(pk, 0x52, (uint64_t)w | ((uint64_t)h << 32));
    sceGifPkAddGsAD(pk, 0x53, 0);
    sceGifPkCloseGifTag(pk);
    while (qwc) {
        uint32_t n = qwc > 0x7FFF ? 0x7FFF : qwc;
        uint64_t *g;
        sceGifPkCnt(pk, 0, 0, 0);
        g = (uint64_t *)sceGifPkReserve(pk, 4);
        g[0] = (uint64_t)n | (2ull << 58) | (n == qwc ? 0x8000u : 0); /* IMAGE, EOP on the last */
        g[1] = 0;
        sceGifPkRef(pk, (uint64_t)(uintptr_t)src, n, 0, 0, 0);
        qwc -= n;
        src += n * 16;
    }
}
