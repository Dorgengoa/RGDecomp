#include "types.h"

/* The four 1<<40..1<<44 flag tests all branch the SAME way (to the shared
 * continue point) -> one `&&` chain.  The `c.le.s/bc1tl` and `c.lt.s/bc1fl`
 * pairs with the mov.s in the delay slot are plain `if (t <= u) t = u;` /
 * `if (t >= u) t = u;` clamps.
 */

extern f32 D_0045B080[];
extern f32 D_0047DAC0;
extern f32 D_0047DAB4;
extern f32 D_0047DB14;

extern void VecCopy_1cbe30(void *, void *);
extern void VecAdd_1cbdc0(void *, void *, void *);
extern void VecWrapAngle_1cbe90(void *, void *);
extern void MatFromSRT_1caf40(void *, void *, void *, void *);
extern void MtxMulDir_1cb910(void *, void *, void *);
extern void *GetCurrentScene_1f5be0(void);
extern f32 GameSceneGetTimeStep_1ceba0(void *);
extern void VecAddMaxZero_1cbd40(void *, void *, void *);
extern void VecAddMinZero_1cbd20(void *, void *, void *);
extern void VecScale_1cbca0(void *, void *, f32);

s32 CharaCalcBoundsRangeMaybe_237f20(u8 *p, u8 *lo, u8 *hi, f32 pad)
{
    f32 s;
    f32 t;
    f32 u;
    f32 lim;
    u64 fl;
    u8 *obj;
    /* stack locals are allocated in REVERSE declaration order:
       c=0x80, d=0x70, b=0x60, a=0x50 */
    u8 c[0x40];
    u8 d[16];
    u8 b[16];
    u8 a[16];

    fl = *(u64 *)(p + 0x3D0);
    if ((fl & 0x100000000000ULL) != 0 && (fl & 0x40000000000ULL) != 0 &&
        (fl & 0x20000000000ULL) != 0 && (fl & 0x10000000000ULL) != 0) {
        return 0;
    }

    VecCopy_1cbe30(lo, p + 0x70);
    VecCopy_1cbe30(hi, p + 0x70);

    u = *(f32 *)(p + 0x24);
    t = *(f32 *)(lo + 4);
    *(f32 *)(lo + 4) = (t > u) ? t : u;

    u = *(f32 *)(p + 0x24);
    t = *(f32 *)(hi + 4);
    *(f32 *)(hi + 4) = (t < u) ? t : u;

    VecAdd_1cbdc0(d, p + 0x60, p + 0x90);
    VecWrapAngle_1cbe90(d, d);
    MatFromSRT_1caf40(c, p + 0x50, d, p + 0x70);
    MtxMulDir_1cb910(b, c, p + 0xB0);

    s = GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0());

    VecAddMaxZero_1cbd40(lo, lo, b);
    VecAddMinZero_1cbd20(hi, hi, b);

    VecScale_1cbca0(a, p + 0x80, s * *(f32 *)(p + 0x414));
    VecAddMaxZero_1cbd40(lo, lo, a);
    VecAddMinZero_1cbd20(hi, hi, a);

    VecScale_1cbca0(a, p + 0xD0, s);
    VecAddMaxZero_1cbd40(lo, lo, a);
    VecAddMinZero_1cbd20(hi, hi, a);

    VecScale_1cbca0(a, p + 0xE0, s);
    VecAddMaxZero_1cbd40(lo, lo, a);
    VecAddMinZero_1cbd20(hi, hi, a);

    VecScale_1cbca0(a, p + 0xF0, s);
    VecAddMaxZero_1cbd40(lo, lo, a);
    VecAddMinZero_1cbd20(hi, hi, a);

    fl = *(u64 *)(p + 0x3D0);
    if ((fl & 0x10000000000ULL) == 0) {
        lim = D_0047DAC0 * D_0045B080[0];
        obj = *(u8 **)(p + 0x3F4);
        if (obj != 0) {
            t = *(f32 *)(obj + 0x4C8) * (D_0047DB14 * D_0045B080[0]);
        } else {
            t = 0.0f;
        }
        pad = pad + ((t > lim) ? t : lim);
    }
    if ((fl & 0x20000000000ULL) == 0) {
        lim = D_0047DAB4 * D_0045B080[0];
        obj = *(u8 **)(p + 0x3F4);
        if (obj != 0) {
            u = *(f32 *)(obj + 0x4CC) * (D_0047DB14 * D_0045B080[0]);
        } else {
            u = 0.0f;
        }
        *(f32 *)(lo + 4) = *(f32 *)(lo + 4) + ((u > lim) ? u : lim);
    }

    *(f32 *)(lo + 0) = *(f32 *)(lo + 0) + pad;
    *(f32 *)(lo + 8) = *(f32 *)(lo + 8) + pad;
    *(f32 *)(hi + 0) = *(f32 *)(hi + 0) - pad;
    *(f32 *)(hi + 8) = *(f32 *)(hi + 8) - pad;
    return 1;
}
