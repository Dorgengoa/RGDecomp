/* rgp:protos */
#define RGP_SELF_insect_InsectBattleDrawCellQuad_4f6d30 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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
            Vec v0 __attribute__((aligned(16))) = {0};
            v0.x = 1.0f + (cx - hw);
            v0.y = y;
            v0.z = (cy + hw) - 1.0f;
            {
                Vec v1 __attribute__((aligned(16))) = {0};
                v1.x = (cx + hw) - 1.0f;
                v1.y = y;
                v1.z = (cy + hw) - 1.0f;
                {
                    Vec v2 __attribute__((aligned(16))) = {0};
                    v2.x = 1.0f + (cx - hw);
                    v2.y = y;
                    v2.z = 1.0f + (cy - hw);
                    {
                        Vec v3 __attribute__((aligned(16))) = {0};
                        Vec t3 __attribute__((aligned(16)));
                        Vec t2 __attribute__((aligned(16)));
                        Vec t1 __attribute__((aligned(16)));
                        Vec t0 __attribute__((aligned(16)));
                        SP  q0 __attribute__((aligned(16)));
                        SP  q1 __attribute__((aligned(16)));
                        SP  q2 __attribute__((aligned(16)));
                        SP  q3 __attribute__((aligned(16)));
                        v3.x = (cx + hw) - 1.0f;
                        v3.y = y;
                        v3.z = 1.0f + (cy - hw);
                        switch (tex) {
                        case 0:
                            if (ProjectToScreen_15d340(&q0, &v0) != 0 && ProjectToScreen_15d340(&q1, &v1) != 0 &&
                                ProjectToScreen_15d340(&q2, &v2) != 0 && ProjectToScreen_15d340(&q3, &v3) != 0) {
                                GsPktOpenPrim_13f730(h, 4);
                                GsPktSetTexture_13ec00(h, o->f0C4[mode]);
                                GsPktSetRGBAQ_13ee40(h, 0x80, 0x80, 0x80, (s32)(128.0f * al));
                                GsPktSetUV_13ed60(h, (s32)u, (s32)v);
                                GsPktSetXYZ_13ef10(h, q0.x, q0.y, q0.z);
                                GsPktSetUV_13ed60(h, (s32)(u + sz), (s32)v);
                                GsPktSetXYZ_13ef10(h, q1.x, q1.y, q1.z);
                                GsPktSetUV_13ed60(h, (s32)u, (s32)(v + sz));
                                GsPktSetXYZ_13ef10(h, q2.x, q2.y, q2.z);
                                GsPktSetUV_13ed60(h, (s32)(u + sz), (s32)(v + sz));
                                GsPktSetXYZ_13ef10(h, q3.x, q3.y, q3.z);
                                GsPktClose_13f5b0(h);
                            }
                            break;
                        case 1:
                            if (CameraProjectToScreenStq_1c8f10(&q0, &t0, &v0, 0.0f, 0.0f) != 0 &&
                                CameraProjectToScreenStq_1c8f10(&q1, &t1, &v1, 0.0f, 1.0f) != 0 &&
                                CameraProjectToScreenStq_1c8f10(&q2, &t2, &v2, 1.0f, 0.0f) != 0 &&
                                CameraProjectToScreenStq_1c8f10(&q3, &t3, &v3, 1.0f, 1.0f) != 0) {
                                GsPktOpenPrim_13f730(h, 4);
                                GsPktSetTexture_13ec00(h, o->f0C4[mode]);
                                GsPktSetSTVec_13ecc0(h, &t0);
                                a8 = (s32)(128.0f * al);
                                GsPktSetRGBAQ_13ee40(h, 0x80, 0x80, 0x80, a8);
                                GsPktSetXYZVecI_13eeb0(h, &q0);
                                GsPktSetSTVec_13ecc0(h, &t1);
                                GsPktSetRGBAQ_13ee40(h, 0x80, 0x80, 0x80, a8);
                                GsPktSetXYZVecI_13eeb0(h, &q1);
                                GsPktSetSTVec_13ecc0(h, &t2);
                                GsPktSetRGBAQ_13ee40(h, 0x80, 0x80, 0x80, a8);
                                GsPktSetXYZVecI_13eeb0(h, &q2);
                                GsPktSetSTVec_13ecc0(h, &t3);
                                GsPktSetRGBAQ_13ee40(h, 0x80, 0x80, 0x80, a8);
                                GsPktSetXYZVecI_13eeb0(h, &q3);
                                GsPktClose_13f5b0(h);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
}
