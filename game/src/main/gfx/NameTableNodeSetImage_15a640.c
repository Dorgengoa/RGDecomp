/* rgp:protos */
#define RGP_SELF_NameTableNodeSetImage_15a640 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

typedef struct TEX1 {
    u64 LCM : 1;
    u64 pad01 : 1;
    u64 MXL : 3;
    u64 MMAG : 1;
    u64 MMIN : 3;
    u64 MTBA : 1;
    u64 pad10 : 9;
    u64 L : 2;
    u64 pad21 : 11;
    u64 K : 12;
    u64 pad44 : 20;
} TEX1;

typedef struct Tex {
    s16 id;         /* 00 */
    s16 w;          /* 02 */
    s16 h;          /* 04 */
    s16 bpp;        /* 06 */
    char name[0x20];/* 08 */
    u16 size;       /* 28 */
    u8 pad2A[2];
    s32 total;      /* 2C */
    s16 stride;     /* 30 */
    u8 count;       /* 32 */
    u8 pad33[3];
    s16 s36;        /* 36 */
    u64 tex0;       /* 38 */
    u64 tex1;       /* 40 */
    u8 pad48[8];
    s32 mip[4];     /* 50 */
    s32 clut;       /* 60 */
} Tex;

#define SET_TEX0(tbp, tbw, psm, tw, th, tcc, tfx, cbp, cpsm, csm, csa, cld) \
    ((u64)(tbp) | ((u64)(tbw) << 14) | ((u64)(psm) << 20) | ((u64)(tw) << 26) | \
     ((u64)(th) << 30) | ((u64)(tcc) << 34) | ((u64)(tfx) << 35) | ((u64)(cbp) << 37) | \
     ((u64)(cpsm) << 51) | ((u64)(csm) << 55) | ((u64)(csa) << 56) | ((u64)(cld) << 61))
#define SET_TEX1(lcm, mxl, mmag, mmin, mtba, l, k) \
    ((u64)(lcm) | ((u64)(mxl) << 2) | ((u64)(mmag) << 5) | ((u64)(mmin) << 6) | \
     ((u64)(mtba) << 9) | ((u64)(l) << 19) | ((u64)(k) << 32))

/*rgp*/
char *strcpy(char *, const char *);

s32 NameTableNodeSetImage_15a640(Tex *tex, s16 id, char *name, s32 *mips, s32 w, s32 h, s32 bpp, s32 clut, u64 t1, s32 s36) {
    s32 local[4] __attribute__((aligned(16)));
    s32 i;
    s32 psm;
    s32 tw;
    s32 th;
    s32 v;
    s32 p;
    s32 tbw;
    s32 b;
    s32 ww;
    s32 size;
    s32 last;
    s32 rem;

    if (*name == 0) return 0;
    if (mips == 0) {
        mips = local;
        for (i = 0; i < 4; i++) mips[i] = 0;
    }
    NameTableNodeReset_15ada0(tex);
    switch (bpp) {
    case 4: psm = 0x14; break;
    case 8: psm = 0x13; break;
    case 16: psm = 2; break;
    case 24: psm = 1; break;
    case 32: psm = 0; break;
    default: return 0;
    }
    tw = 0;
    th = 0;
    v = w;
    while (v >= 2) { v /= 2; tw++; }
    i = 1;
    for (p = 0; p < tw; p++) i *= 2;
    if (w != i) tw++;
    v = h;
    while (v >= 2) { v /= 2; th++; }
    i = 1;
    for (p = 0; p < th; p++) i *= 2;
    if (h != i) th++;
    tbw = w / 64;
    if (w % 64 != 0) tbw++;
    if (tbw <= 0) tbw = 1;
    b = bpp;
    ww = w;
    if (bpp == 24) b = 32;
    if (b < 9 && w % 128 != 0) {
        ww = (w / 128 + 1) * 128;
        if (tbw % 2 != 0) tbw = (tbw / 2 + 1) * 2;
    }
    size = b * (ww * h) / 256 / 8;
    tex->total = 0;
    last = -1;
    switch (psm) {
    case 1:
    case 0:
    case 2:
    case 19:
    case 20:
        for (i = 0; i < 4; i++) {
            if (mips[i] == 0) {
                last = i - 1;
                break;
            }
        }
        for (i = 0; i < last + 1; i++) {
            tex->mip[i] = mips[i];
            if (mips[i] != 0) tex->total += size;
            size /= 4;
        }
        if (mips[0] == 0) tex->total = size;
        if (psm == 19) {
            tex->clut = clut;
            tex->stride = 0x400;
            tex->count = 1;
            tex->tex0 = SET_TEX0(0, tbw, psm, tw, th, 1, 0, 0, 0, 0, 0, 1);
        } else if (psm == 20) {
            tex->clut = clut;
            tex->stride = 0x40;
            tex->count = 1;
            tex->tex0 = SET_TEX0(0, tbw, psm, tw, th, 1, 0, 0, 0, 0, 0, 1);
        } else {
            tex->clut = 0;
            tex->tex0 = SET_TEX0(0, tbw, psm, tw, th, 1, 0, 0, 0, 0, 0, 0);
        }
        break;
    }
    tex->size = tex->total;
    rem = tex->size % 32;
    if (rem != 0) tex->size += (u16)(32 - rem);
    strcpy(tex->name, name);
    tex->w = w;
    tex->h = h;
    tex->bpp = bpp;
    tex->id = id;
    tex->s36 = s36;
    tex->tex1 = SET_TEX1(1, 0, 1, 1, 1, 0, 0);
    if (bpp > 0) {
        if (last > 0) {
            tex->tex1 = SET_TEX1(0, 2, 1, 5, 1, 0, -120);
            if (t1 != 0) {
                TEX1 *p = (TEX1 *)&t1;
                tex->tex1 = SET_TEX1(0, last, 1, 5, 1, p->L, p->K);
            }
        } else {
            tex->tex1 = SET_TEX1(0, 0, 1, 1, 1, 0, 0);
            if (t1 != 0) tex->tex1 = SET_TEX1(0, 0, 1, 1, 1, 0, 0);
        }
    }
    return 1;
}
