/* ix24f2 PARKED DRAFT -- EXACT LENGTH, NOT BYTE-IDENTICAL. DO NOT MERGE. */
#include "types.h"
/* insect 0x004F6D30 -- 1,744 bytes, 436 instructions, 38 calls, 22 conditional
 * branches.  A quad emitter: it builds four corner vectors, projects them and
 * pushes two triangles.  Sibling: insect_InsectBattleDrawPieceIcons_4f5430.cpp (same func_13Exxx
 * drawing API, same inline 16-byte clear).
 *
 * The `% 3` carries NO `break 0,7` divide trap -- retail is bare, which
 * RE-CONFIRMS "divbyzerocheck is the OPERATOR not the ordinal": `/` sites carry
 * the check, `%` (mfhi) sites are bare.  So this unit must NOT get the pragma.
 *
 * `adda.s $f26,$f0` + `msub.s $f27,$f1,$f2` in case 7 is plain C
 * `var_f26 + D_0047D884 - D_0047D888 * t` ([[ps2-float-accumulator]]).
 *
 * Stack locals run 0x120,0x110,0x100,0xF0,0xE0,0xD0,0xC0,0xB0,0xA0,0x90,0x80,
 * 0x70 -- twelve 16-byte locals, first DECLARED gets the HIGHEST address.
 */

typedef struct Vec { f32 x, y, z, w; } Vec;
typedef struct SP  { s32 x, y, z, w; } SP;

typedef struct O {
    u8  pad000[0xC4];
    s32 f0C4[4];                /* +0xC4 */
    u8  pad0D4[0x5FC8 - 0xD4];
    f32 f5FC8;                  /* +0x5FC8 */
} O;

extern f32 D_0047D874;
extern f32 D_0047D878;
extern f32 D_0047D87C;
extern f32 D_0047D880;
extern f32 D_0047D884;
extern f32 D_0047D888;

extern f32  insect_InsectBattleFadeGetAlpha_50e0b0(O *o, s32 k);
extern void insect_InsectBattleFadeStart_50e1e0(O *o, s32 k, s32 a, s32 b, s32 c);

extern s32  func_15D340(SP *p, Vec *v);
extern s32  func_1C8F10(SP *p, Vec *u, Vec *v, f32 a, f32 b);
extern void func_13F730(void *h, s32 a);
extern void func_13EC00(void *h, s32 a);
extern void func_13ECC0(void *h, Vec *v);
extern void func_13ED60(void *h, s32 a, s32 b);
extern void func_13EE40(void *h, s32 a, s32 b, s32 c, s32 d);
extern void func_13EEB0(void *h, SP *p);
extern void func_13EF10(void *h, s32 x, s32 y, s32 z);
extern void func_13F5B0(void *h);

void insect_InsectBattleDrawCellQuad_4f6d30(O *o, void *h, s32 k, f32 fx, f32 fy, f32 fz, f32 fw)
{
    f32 zz;
    f32 u;
    f32 v;
    f32 sz;
    f32 al;
    f32 cx;
    f32 cy;
    f32 hw;
    f32 t;
    f32 y;
    s32 tex;
    s32 mode;
    s32 a8;
    s8  ix;
    s8  iy;
    s8  im;
    s8  im3;

    zz = fz;
    if (h != 0) {
        sz = 32.0f;
        tex = 0;
        mode = 0;
        cx = fx - 2.0f;
        cy = fy - 3.0f;
        cx = cx * 4.0f;
        cy = cy * 4.0f;
        hw = 2.75f;
        al = fw;
        iy = fy;
        im = iy % 3;
        ix = fx;
        im3 = (s8)(im * 3);
        t = (f32)(im3 + ix);
        switch (k) {
        case 0:
            zz = D_0047D874;
            u = 0.0f;
            v = u;
            al = insect_InsectBattleFadeGetAlpha_50e0b0(o, 0);
            if (al <= u) {
                insect_InsectBattleFadeStart_50e1e0(o, 0, 0x80, (s32)(16.0f * o->f5FC8), 1);
            } else if (al >= 1.0f) {
                insect_InsectBattleFadeStart_50e1e0(o, 0, 0, (s32)(16.0f * o->f5FC8), 1);
            }
            break;
        case 1:
            zz = D_0047D87C;
            v = 0.0f;
            u = sz;
            break;
        case 2:
            u = 64.0f;
            v = 0.0f;
            zz = D_0047D87C;
            break;
        case 3:
            u = 96.0f;
            v = 0.0f;
            zz = D_0047D87C;
            break;
        case 4:
            u = 1.0f;
            v = 33.0f;
            sz = 30.0f;
            zz = D_0047D880;
            break;
        case 5:
            u = 33.0f;
            sz = 30.0f;
            v = u;
            break;
        case 6:
            u = 222.0f;
            sz = 34.0f;
            zz = D_0047D874;
            v = 0.0f;
            mode = 1;
            break;
        case 7:
            mode = 3;
            sz = 128.0f;
            tex = 1;
            hw = hw * 2.5f;
            u = 0.0f;
            v = u;
            zz = D_0047D884 - D_0047D888 * t;
            break;
        }
        y = D_0047D878 + zz;
        {
            Vec v0 = {0};
            v0.x = 1.0f + (cx - hw);
            v0.y = y;
            v0.z = (cy + hw) - 1.0f;
            {
                Vec v1 = {0};
                v1.x = (cx + hw) - 1.0f;
                v1.y = y;
                v1.z = (cy + hw) - 1.0f;
                {
                    Vec v2 = {0};
                    v2.x = 1.0f + (cx - hw);
                    v2.y = y;
                    v2.z = 1.0f + (cy - hw);
                    {
                        Vec v3 = {0};
                        Vec t3;
                        Vec t2;
                        Vec t1;
                        Vec t0;
                        SP  q0;
                        SP  q1;
                        SP  q2;
                        SP  q3;
                        v3.x = (cx + hw) - 1.0f;
                        v3.y = y;
                        v3.z = 1.0f + (cy - hw);
                        switch (tex) {
                        case 0:
                            if (func_15D340(&q0, &v0) != 0 && func_15D340(&q1, &v1) != 0 &&
                                func_15D340(&q2, &v2) != 0 && func_15D340(&q3, &v3) != 0) {
                                func_13F730(h, 4);
                                func_13EC00(h, o->f0C4[mode]);
                                func_13EE40(h, 0x80, 0x80, 0x80, (s32)(128.0f * al));
                                func_13ED60(h, (s32)u, (s32)v);
                                func_13EF10(h, q0.x, q0.y, q0.z);
                                func_13ED60(h, (s32)(u + sz), (s32)v);
                                func_13EF10(h, q1.x, q1.y, q1.z);
                                func_13ED60(h, (s32)u, (s32)(v + sz));
                                func_13EF10(h, q2.x, q2.y, q2.z);
                                func_13ED60(h, (s32)(u + sz), (s32)(v + sz));
                                func_13EF10(h, q3.x, q3.y, q3.z);
                                func_13F5B0(h);
                            }
                            break;
                        case 1:
                            if (func_1C8F10(&q0, &t0, &v0, 0.0f, 0.0f) != 0 &&
                                func_1C8F10(&q1, &t1, &v1, 0.0f, 1.0f) != 0 &&
                                func_1C8F10(&q2, &t2, &v2, 1.0f, 0.0f) != 0 &&
                                func_1C8F10(&q3, &t3, &v3, 1.0f, 1.0f) != 0) {
                                func_13F730(h, 4);
                                func_13EC00(h, o->f0C4[mode]);
                                func_13ECC0(h, &t0);
                                a8 = (s32)(128.0f * al);
                                func_13EE40(h, 0x80, 0x80, 0x80, a8);
                                func_13EEB0(h, &q0);
                                func_13ECC0(h, &t1);
                                func_13EE40(h, 0x80, 0x80, 0x80, a8);
                                func_13EEB0(h, &q1);
                                func_13ECC0(h, &t2);
                                func_13EE40(h, 0x80, 0x80, 0x80, a8);
                                func_13EEB0(h, &q2);
                                func_13ECC0(h, &t3);
                                func_13EE40(h, 0x80, 0x80, 0x80, a8);
                                func_13EEB0(h, &q3);
                                func_13F5B0(h);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
}
