/* rgp:hwaccess */ #include "port/hwaccess.h"
#line 1
/* rgp:protos */
#define RGP_SELF_DrawListAddVramCopy_1414a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct Tex0 {
    u64 TBP0:14;
    u64 TBW:6;
    u64 PSM:6;
    u64 TW:4;
    u64 TH:4;
    u64 TCC:1;
    u64 TFX:2;
    u64 CBP:14;
    u64 CPSM:4;
    u64 CSM:1;
    u64 CSA:5;
    u64 CLD:3;
} Tex0;

typedef struct Rect {
    s32 y0;
    s32 x0;
    s32 y1;
    s32 x1;
} Rect;

typedef struct Pk {
    u8 pad0[0x28];
    u8 *base;       /* 0x28 */
    s32 n;          /* 0x2C */
} Pk;

typedef struct Ctx {
    s32 cur0;           /* 0x00 */
    u8 *cur;            /* 0x04 */
    u8 *arr[1];         /* 0x08 */
} Ctx;

/*rgp*/
extern u128 D_0047DE40 __attribute__((section(".sdata")));

#define SET_BITBLTBUF(sbp, sbw, spsm, dbp, dbw, dpsm) \
    ((u64)(sbp) | ((u64)(sbw) << 16) | ((u64)(spsm) << 24) | ((u64)(dbp) << 32) | ((u64)(dbw) << 48) | ((u64)(dpsm) << 56))
#define SET_TRXPOS(ssax, ssay, dsax, dsay, dir) \
    ((u64)(ssax) | ((u64)(ssay) << 16) | ((u64)(dsax) << 32) | ((u64)(dsay) << 48) | ((u64)(dir) << 59))
#define SET_TRXREG(rrw, rrh) ((u64)(rrw) | ((u64)(rrh) << 32))

void DrawListAddVramCopy_1414a0(Ctx *o, Tex0 *src, Rect *r, Tex0 *dst, s32 dx, s32 dy, s32 dir)
{
    u8 *t;
    Pk *pk;
    u32 *hdr;
    u64 *q;
    s32 dw;
    s32 sw;
    s32 h;
    s32 w;
    s32 x0;
    s32 y0;

    t = o->arr[o->cur0];
    if (t != 0) {
        pk = (Pk *)(t + 8);
    } else {
        pk = 0;
    }
    if (pk == 0) {
        return;
    }
    hdr = (u32 *)(pk->base + pk->n * 16);
    dw = dst->TBW << 6;
    sw = src->TBW << 6;
    if (dw < 0x40) {
        dw = 0x40;
    }
    if (sw < 0x40) {
        sw = 0x40;
    }
    x0 = r->x0;
    w = r->x1 - x0;
    if (w <= 0) {
        return;
    }
    y0 = r->y0;
    h = r->y1 - y0;
    if (h <= 0) {
        return;
    }
    *(u128 *)hdr = 0;
    hdr[0] = 0x60000007;
    hdr[3] = 0x50000007;
    hdr[4] = 0x8006;
    hdr[5] = 0x10000000;
    hdr[6] = 0xE;
    hdr[7] = 0;
    q = (u64 *)hdr;
    q[4] = 0;
    q[5] = 0x3F;
    q[6] = SET_BITBLTBUF(src->TBP0, sw / 64, src->PSM, dst->TBP0, dw / 64, dst->PSM);
    q[7] = 0x50;
    q[8] = SET_TRXPOS(x0, y0, dx, dy, dir);
    q[9] = 0x51;
    q[10] = SET_TRXREG(w, h);
    q[11] = 0x52;
    q[12] = 2;
    q[13] = 0x53;
    q[14] = 0;
    q[15] = 0x3F;
    MemStackAllocQw_14d950(pk, 8);
    *(u128 *)o->cur = D_0047DE40;
    ((u32 *)o->cur)[1] = ((u32)hdr);
    o->cur += 0x10;
}
