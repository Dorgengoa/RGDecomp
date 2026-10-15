#include "types.h"
/* insect 0x004F47A0 -- 652 bytes, 163 instructions, no calls.
 *
 * Builds the four corners of an axis-aligned box, optionally rotates them by
 * (sn, cs), scales and translates.  The four 16-byte clears are the written-out
 * byte loop of insect_FUN_004F52A0, with the `u32` counter that gives `bnez`
 * rather than `bgtz` at the bottom.  The rotation is written as ONE expression
 * per component so mwcc contracts it into `mula.s` + `msub.s` / `madd.s` --
 * naming the product would kill exactly that (normal-named-product-local). */

void insect_InsectBattleCalcQuadCorners_4f47a0(s32 z, f32 *a, f32 *b, f32 *c, f32 *d, f32 *ad,
                         f32 *sc, s32 rot, f32 x, f32 y, f32 sn, f32 cs,
                         f32 w, f32 h)
{
    f32 v3[4];
    f32 v2[4];
    f32 v1[4];
    f32 v0[4];
    u8 *p;
    u32 n;
    s32 i;

    p = (u8 *)v3;
    n = 0x10;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    v3[0] = -x + w;
    v3[2] = -y + h;
    p = (u8 *)v2;
    n = 0x10;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    v2[0] = x + w;
    v2[2] = -y + h;
    p = (u8 *)v1;
    n = 0x10;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    v1[0] = -x + w;
    v1[2] = y + h;
    p = (u8 *)v0;
    n = 0x10;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    v0[0] = x + w;
    v0[2] = y + h;
    for (i = 0; i < 3; i++) {
        a[i] = v3[i];
        b[i] = v2[i];
        c[i] = v1[i];
        d[i] = v0[i];
    }
    if (rot != 0) {
        a[0] = (v3[0] * cs) - (v3[2] * sn);
        b[0] = (v2[0] * cs) - (v2[2] * sn);
        c[0] = (v1[0] * cs) - (v1[2] * sn);
        d[0] = (v0[0] * cs) - (v0[2] * sn);
        a[2] = (v3[0] * sn) + (v3[2] * cs);
        b[2] = (v2[0] * sn) + (v2[2] * cs);
        c[2] = (v1[0] * sn) + (v1[2] * cs);
        d[2] = (v0[0] * sn) + (v0[2] * cs);
    }
    if (sc != 0) {
        for (i = 0; i < 3; i++) {
            a[i] = a[i] * sc[i];
            b[i] = b[i] * sc[i];
            c[i] = c[i] * sc[i];
            d[i] = d[i] * sc[i];
        }
    }
    for (i = 0; i < 3; i++) {
        a[i] = a[i] + ad[i];
        b[i] = b[i] + ad[i];
        c[i] = c[i] + ad[i];
        d[i] = d[i] + ad[i];
    }
}
