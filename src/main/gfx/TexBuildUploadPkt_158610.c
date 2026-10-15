#include "types.h"

typedef struct TEX0 {
    u64 TBP0 : 14;
    u64 TBW : 6;
    u64 PSM : 6;
    u64 TW : 4;
    u64 TH : 4;
    u64 TCC : 1;
    u64 TFX : 2;
    u64 CBP : 14;
    u64 CPSM : 4;
    u64 CSM : 1;
    u64 CSA : 5;
    u64 CLD : 3;
} TEX0;

typedef struct Tex {
    u8 pad0[2];
    s16 w;          /* 02 */
    s16 h;          /* 04 */
    s16 bpp;        /* 06 */
    u8 pad8[0x28];
    s16 stride;     /* 30 */
    u8 count;       /* 32 */
    u8 pad33;
    s16 base;       /* 34 */
    s16 flag;       /* 36 */
    TEX0 tex0;      /* 38 */
    u8 pad40[0x10];
    s32 mip[4];     /* 50 */
    u8 *clut;       /* 60 */
} Tex;

typedef void (*UploadFn)(s32, u8 *, s32, s32);

typedef struct Obj {
    u8 pad0[0x1F4];
    UploadFn fn;    /* 1F4 */
} Obj;

s32 TexBuildClutUploadPkt_157d70(Obj *, s32, s32 *, s32, s32, s32);
s32 GsBuildImageUploadPkt_1581b0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 GsBuildImageUploadRefPkt_158390(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

static inline s32 UploadPalette(s32 dst,s32 base,s32 cpsm,u8 * clut,s32 b,s32 mode){ s32 k;
                if (clut == 0) {
                    return 0;
                } else {
                    k = 0;
                    if (b == 8) {
                        if (mode) {
                            k = GsBuildImageUploadPkt_1581b0(dst, base, cpsm, 1, (s32)clut, 0x40, 0, 0, 0x10, 0x10);
                        } else {
                            k = GsBuildImageUploadRefPkt_158390(dst, base, cpsm, 1, (s32)clut, 0x40, 0, 0, 0x10, 0x10);
                        }
                    } else if (b == 4) {
                        if (mode) {
                            k = GsBuildImageUploadPkt_1581b0(dst, base, cpsm, 1, (s32)clut, 4, 0, 0, 8, 2);
                        } else {
                            k = GsBuildImageUploadRefPkt_158390(dst, base, cpsm, 1, (s32)clut, 4, 0, 0, 8, 2);
                        }
                    }
                }
return k; }
s32 TexBuildUploadPkt_158610(Obj *obj, s32 dst, Tex *tex, s32 mode) {
    s32 cpsm;
    TEX0 t;
    s32 base;
    UploadFn fn;
    Obj *o;
    s32 mip;
    s32 start;
    s32 k;
    s32 w;
    s32 h;
    s32 bpp;
    s32 n;
    s32 addr;
    s32 i;
    u8 *clut;
    s32 b;

    n = 0;
    bpp = tex->bpp;
    fn = obj->fn;
    w = tex->w;
    h = tex->h;
    o = obj;
    start = dst;
    t = tex->tex0;
    if (bpp == 8) {
        if (tex->flag != 0) {
            w >>= 1;
            h >>= 1;
            t.PSM = 0;
            bpp = 0x20;
            t.TBW = t.TBW >> 1;
        }
        n = 4;
    } else if (bpp == 4) {
        n = 1;
    }
    if (n > 0) {
        for (i = 0; i < tex->count; i++) {
            clut = tex->clut + i * tex->stride;
            if (dst == 0) continue;
            if (fn != 0 && mode == 0) {
                dst += TexBuildClutUploadPkt_157d70(o, dst, &addr, tex->bpp, tex->base + i * n, tex->tex0.CPSM) * 4;
                fn(addr, clut, tex->stride, tex->tex0.CPSM);
            } else {
                cpsm = tex->tex0.CPSM;
                base = tex->base + i * n;
                b = tex->bpp;
                k = UploadPalette(dst,base,cpsm,clut,b,mode);
                dst += k * 4;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        mip = tex->mip[i];
        if (mip == 0) break;
        if (t.TBW == 0) t.TBW = 1;
        if (dst != 0) {
            if (mode) {
                dst += GsBuildImageUploadPkt_1581b0(dst, t.TBP0, t.PSM, (s32)t.TBW, mip, bpp * (w * h) / 16 / 8, 0, 0, w, h) * 4;
            } else {
                dst += GsBuildImageUploadRefPkt_158390(dst, t.TBP0, t.PSM, (s32)t.TBW, mip, bpp * (w * h) / 16 / 8, 0, 0, w, h) * 4;
            }
        }
        k = bpp * (w * h) / 256 / 8;
        w >>= 1;
        h >>= 1;
        t.TBP0 += (u16)k;
        t.TBW = t.TBW >> 1;
    }
    return (dst - start) / 4;
}
