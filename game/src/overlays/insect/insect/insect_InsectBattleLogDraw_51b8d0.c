/* rgp:protos */
#define RGP_SELF_TextStyleGetGradRgba_26f200 1
#define RGP_SELF_TextStyleGetRgba_26f2a0 1
#define RGP_SELF_TextStyleSetGradRgbaQuad_26f1b0 1
#define RGP_SELF_TextStyleSetRgbaQuad_26f250 1
#define RGP_SELF_insect_InsectBattleLogDraw_51b8d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051B8D0 -- 1,192 bytes, 300 instructions, 45 calls, 21 conditional
 * branches.
 *
 * func_15DE80's result lives in $4 across the whole counting loop and is
 * func_1418C0's first argument -- it is NOT the dead move it looks like.
 *
 * func_26F2A0 / func_26F200 return an 8-byte struct BY VALUE: retail builds it
 * in a compiler temp (0xB8 / 0xB0) and copies it with one ld/sd into the named
 * local (0xC8 / 0xC0), then passes it back in one 64-bit register.
 *
 * `dsll32/dsra32 ..,16` appears TWICE on each of the two func_1451x0 results
 * -- once at the assignment and once at the use -- which is a register-
 * resident s16 LOCAL, not an s32 local with a cast (ix22 round 1's narrowing
 * rule).  `bgez / addiu 1 / sra 1` is the signed `/ 2`.
 *
 * Both counting loops are TOP-tested (entered by a `b` to the test), so they
 * are written as plain `for`s with a `break`, not as rotated do/whiles.
 */

typedef struct Ent {
    u8  pad00[0x51];
    u8  f51;                        /* +0x51 */
    u8  pad52[0x54 - 0x52];
    s8  f54;                        /* +0x54 */
    u8  pad55[0x56 - 0x55];
    s16 f56;                        /* +0x56 */
    s16 f58;                        /* +0x58 */
} Ent;

typedef struct Obj {
    u8   pad00[0x4];
    Ent *f04;                       /* +0x04 */
    s16  f08;                       /* +0x08 */
    s16  f0A;                       /* +0x0A */
    s16  f0C;                       /* +0x0C */
    u8   pad0E[0x10 - 0xE];
    s16  f10;                       /* +0x10 */
    s16  f12;                       /* +0x12 */
    s16  f14;                       /* +0x14 */
    s16  f16;                       /* +0x16 */
    s16  f18;                       /* +0x18 */
    u8   pad1A[0x1E - 0x1A];
    s16  f1E;                       /* +0x1E */
    u8   pad20[0x28 - 0x20];
    u8   f28[4];                    /* +0x28 */
} Obj;

typedef struct V8 { s64 x; } V8;

extern volatile s32 D_00485148;     /* _gp - 0x28 */
extern u8 insect_D_005253F0[];

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void  TextStyleSetGradRgbaQuad_26f1b0(void *q, V8 v);
/*rgp*/
void TextStyleGetGradRgba_26f200(void *, void *);
extern void  TextStyleSetRgbaQuad_26f250(void *q, V8 v);
/*rgp*/
void TextStyleGetRgba_26f2a0(void *, void *);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleLogDraw_51b8d0(Obj *o)
{
    V8    v1 __attribute__((aligned(16)));
    V8    v2 __attribute__((aligned(16)));
    V8    t1 __attribute__((aligned(16)));
    V8    t2 __attribute__((aligned(16)));
    s32   ra[4] __attribute__((aligned(16)));
    s32   rb[4] __attribute__((aligned(16)));
    void *h;
    void *h2;
    void *w;
    void *sp;
    void *q;
    Ent  *p;
    s32   c21;
    s32   c22;
    s32   c23;
    s16   x;
    s16   y;
    u8   *cp;
    u32   cn;
    s32   n;
    s32   i;

    if (o->f04 == 0) {
        return;
    }
    h = GetDrawCtx_15de80();
    q = o->f28;
    if (q == 0) {
        return;
    }
    n = 0;
    p = o->f04;
    i = 0;
    while (i < 0x50) {
        if (p->f54 == 0) {
            break;
        }
        n++;
        i++;
        p++;
    }
    if (n == 0) {
        return;
    }
    if (o->f18 < n) {
        n = o->f18;
    }
    DrawListAddTexLoad_1418c0(h, 0x338, 1.0f);
    t1 = ({ V8 rgp_sret; TextStyleGetRgba_26f2a0((void *)&rgp_sret, (void *)(q)); rgp_sret; });
    v1 = t1;
    t2 = ({ V8 rgp_sret; TextStyleGetGradRgba_26f200((void *)&rgp_sret, (void *)(q)); rgp_sret; });
    v2 = t2;
    c21 = ((signed char)TextStyleGetFontType_26ede0(q));
    c22 = TextStyleGetZ_26e430(q);
    TextStyleSetZ_26e440(q, -1);
    c23 = ((short)TextStyleGetAlpha_26dd30(q));
    TextStyleSetFontType_26edf0(q, 2);
    TextStyleSetClipRect_26f620(q, o->f08 + o->f10, o->f0A + o->f14, o->f08 + o->f12,
                o->f0A + o->f16);
    p = o->f04;
    i = 0;
    while (i < n) {
        if (p->f56 > 0) {
            break;
        }
        if (p->f58 >= 0) {
            insect_InsectPlaySe_510870(p->f58);
            p->f58 = -1;
        }
        TextStyleSetAlpha_26dd40(q, p->f51);
        TextStyleSetRgba_26f280(q, 0x80, 0x80, 0x80, 0x80);
        TextStyleSetGradRgba_26f1e0(q, 0x80, 0x80, 0x80, 0x80);
        FontDrawText_26cdc0(q, p, o->f08, o->f0A - o->f0C + i * 0x18);
        i++;
        p++;
    }
    TextStyleSetAlpha_26dd40(q, c23);
    TextStyleSetZ_26e440(q, c22);
    TextStyleSetRgbaQuad_26f250(q, v1);
    TextStyleSetGradRgbaQuad_26f1b0(q, v2);
    TextStyleSetFontType_26edf0(q, c21);
    TextStyleClearClipRect_26f600(q);
    if (o->f1E != 0) {
    if (GetPauseStep_2f6660() == 0) {
        D_00485148 = D_00485148 + 1;
    }
    if (D_00485148 > 0x1E) {
        D_00485148 = 0;
    }
    if (D_00485148 >= 0xF) {
        return;
    }
    h2 = GetDrawCtx_15de80();
    x = DrawEnvGetWidth_1451e0(h2);
    y = DrawEnvGetHeight_1451d0(h2);
    sp = NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), insect_D_005253F0, -1);
    w = DrawListBeginPrim_141b00(h2);
    GsPktSetAlphaBlend_13e500(w, 1);
    GsPktSetBlendMode_13e4f0(w, 1);
    GsPktSetAlphaTestFunc_13e4c0(w, 6, 0);
    GsPktEnableAlphaTest_13e4d0(w, 1);
    GsPktEnableZTest_13e460(w, 0);
    GsPktSetOriginMode_13e2f0(w, 0);
    GsPktSetGouraud_13e3b0(w, 1);
    GsPktSetTextured_13e400(w, 1);
    GsPktOpenPrim_13f730(w, 6);
    GsPktSetTexture_13ec00(w, sp);
    cp = (u8 *)ra;
    cn = 0x10;
    if (cp != 0) {
        do {
            *cp = 0;
            cn--;
            cp++;
        } while (cn != 0);
    }
    ra[0] = (x - 0x16) / 2;
    ra[1] = (y + 0x114) / 2 - 6;
    cp = (u8 *)rb;
    cn = 0x10;
    if (cp != 0) {
        do {
            *cp = 0;
            cn--;
            cp++;
        } while (cn != 0);
    }
    rb[0] = (x + 0x16) / 2;
    rb[1] = (y + 0x134) / 2 - 6;
    GsPktSetRGBAQ_13ee40(w, 0x80, 0x80, 0x80, 0x80);
    GsPktSetUV_13ed60(w, 0xE4, 0);
    GsPktSetXYZPixel_13f110(w, ra[0], ra[1], 0);
    GsPktSetUV_13ed60(w, 0xF6, 0x10);
    GsPktSetXYZPixel_13f110(w, rb[0], rb[1], 0);
    GsPktClose_13f5b0(w);
    DrawListEndPrim_141a20(h2);
    } else {
        D_00485148 = 0;
    }
}
