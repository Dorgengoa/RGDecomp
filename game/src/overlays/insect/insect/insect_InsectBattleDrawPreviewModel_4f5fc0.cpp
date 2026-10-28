/* rgp:protos */
#line 1
/* ix34s04 -- MATCH.  insect_InsectBattleDrawPreviewModel_4f5fc0, 1228 B, byte-identical (.text sha1
 * 9c0adc50, residue 0 bad, exact length 0x4cc).  Confirmed twice alone,
 * build/ix34/sweep_4f5fc0_{b,c}.log + sweep_4f5fc0_rawonce_confirm.log.
 *
 * From the ix32 park (2 bad) the whole edit is inside `case 0x1C:`:
 *   -  s = func_1290B8(D_0047D80C) * -D_0047D810 * 50.0f / 0.75f;
 *   -  t = func_1290B8(D_0047D80C) * -D_0047D7A4 * 50.0f;
 *   +  kf = 50.0f;
 *   +  s = func_1290B8(D_0047D80C) * (-D_0047D810 * kf) / 0.75f;
 *   +  t = func_1290B8(D_0047D80C) * (-D_0047D7A4 * kf);
 * plus `f32 kf;` in the local declaration run (position INERT: first, mid and
 * last all give 9c0adc50).
 *
 * THE LEVER: ix32 wrote that retail's tree `(-D * 50.0f) * call` and retail's
 * temp creation order were "not both reachable" -- every parenthesised arm went
 * +2 words because the literal 50.0f was materialised BEFORE the D load.
 * Naming the literal in a LOCAL assigned in its own statement makes 50.0f a
 * WEB whose creation site is the assignment, so the parenthesised product no
 * longer hoists the constant, and the literal operand stops being canonicalised
 * into rs.  Operand order still matters: `-D * kf` matches, `kf * -D` is 2 bad.
 * One `kf = 50.0f;` for both sites is enough (the second is CSE'd away), and it
 * still shares the `lui $v0,0x4248` with `y[2] = 50.0f;` at 0x4F63A8.
 */
#include "types.h"
/* insect 0x004F5FC0 -- 1228 bytes, br22, TWO `jalr $25` C++ virtual calls.
 * [[jalr-is-cpp-virtual]]
 *   vptr +0x1B0 slot 0x24 = virtual #7   (the insect_InsectBattleDrawMarkerModels_4f4a30 class)
 *   vptr +0xC0  slot 0x44 = virtual #15  on a STACK-LOCAL object whose vptr
 *                                        is written inline (&D_00470090).
 */

class VE {
public:
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;  
      
    
    void s07() { VCM0(void, 0x24); }                  /* slot 0x24 */
};

class VQ {
public:
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;  
      
     void s07() { VCM0(void, 0x24); } 
      
      
    void s15() { VCM0(void, 0x44); }                  /* slot 0x44 */
};

typedef struct V4 { f32 x; f32 y; f32 z; f32 w; } __attribute__((aligned(16))) V4;
typedef struct U4 { f32 x; f32 y; f32 z; f32 w; } U4;
typedef struct WV { V4 v; } WV;
typedef struct WU { U4 v; } WU;
typedef struct WU2 { WU v; } WU2;
typedef struct U2 { f32 x; f32 y; } U2;
typedef struct WH { U2 v; } WH;
typedef struct V2 { f32 x; f32 y; } V2;

struct Q {
    u8          pad000[0x50];
    V4          f050;
    V4          f060;
    u8          pad070[0xC0 - 0x70];
    const void *vptr;
    u8          pad0C4[0xD0 - 0xC4];
};

struct E {
    u8  pad000[0x450];
    s32 f450;
    u8  pad454[0x464 - 0x454];
    s32 f464;
    s8  f468;
    u8  pad469[0x4DC - 0x469];
    s32 f4DC;
    u8  pad4E0[0x790 - 0x4E0];
};

struct P {
    u8  pad000[0x54];
    s32 f054;
};

struct H {
    u8  pad000[0x4];
    f32 f004;
    f32 f008;
    f32 f00C;
};

struct O {
    u8    pad000[0xC0];
    void *f0C0;
    u8    pad0C4[0x890 - 0xC4];
    E     f0890;
    E     f1020;
    u8    pad17B0[0x5B30 - 0x17B0];
    P     f5B30;
};

extern "C" u8 D_00470090[];

extern "C" f32 D_0047D1FC;
extern "C" f32 D_0047D410;
extern "C" f32 D_0047D414;
extern "C" f32 D_0047D7A4;
extern "C" f32 D_0047D7F8;
extern "C" f32 D_0047D80C;
extern "C" f32 D_0047D810;
extern "C" f32 D_00480E80;
extern "C" f32 D_00480E84;
extern "C" f32 D_00480E88;
extern "C" f32 D_00480E8C;
extern "C" f32 D_00480F30;
extern "C" f32 D_00480F34;
extern "C" f32 D_00480F38;
extern "C" f32 D_00480F3C;

extern "C" f32   Tanf_1290b8(f32 a);
extern "C" void  GsPktSetTextured_13e400(void *g, s32 a);
extern "C" void  GsPktSetFrameMask_13e420(void *g, s32 a);
extern "C" void  GsPktSetZWriteMask_13e430(void *g, s32 a);
extern "C" void  GsPktSetZTest_13e450(void *g, s32 a);
extern "C" void  GsPktEnableZTest_13e460(void *g, s32 a);
extern "C" void  GsPktSetAlphaBlend_13e500(void *g, s32 a);
extern "C" void  GsPktSetRGBAQ_13ee40(void *g, s32 a, s32 b, s32 c, s32 d);
extern "C" void  GsPktSetXYZPixel_13f110(void *g, s32 a, s32 b, s32 c);
extern "C" void  GsPktClose_13f5b0(void *g);
extern "C" void  GsPktOpenPrim_13f730(void *g, s32 a);
extern "C" void  DrawListAddTexLoad_1418c0(void *h, s32 id, f32 t);
extern "C" void  DrawListEndPrim_141a20(void *h);
extern "C" void *DrawListBeginPrim_141b00(void *h);
extern "C" void CameraSetViewFromCameraBase_142dd0(void *, Q *, int, int);
extern "C" void  ViewSetFov_142f10(void *h, f32 t);
extern "C" void  ViewStackPop_1443e0(void *h);
extern "C" void  ViewStackPush_144430(void *h);
extern "C" void  DrawEnvGetFrameRect_145040(void *h, s32 *r);
extern "C" void  DrawListAddCameraMatrixPacket_1481b0(void *h);
extern "C" void  DrawListAddViewPacket_1482e0(void *h);
extern "C" void  ModelSetScale_150ff0(E *e, f32 *v);
extern "C" void  ModelSetRot_151080(E *e, f32 *v);
extern "C" void  ModelSetPos_151110(E *e, f32 *v);
extern "C" void  CameraBaseApplyLookAt_15fa80(Q *q);
extern "C" void  DrawModelPreview_28be80(E *e, f32 a, f32 b);
extern "C" H    *InsectCageAdjFindById_3916e0(s32 k);
extern "C" s32   insect_InsectBattleGetState_50d6f0(O *o, s32 k);
extern "C" s32   insect_InsectBattleTestFlag_50da40(O *o, s32 k);
extern "C" void  insect_InsectBattleClearFlag_50da90(O *o, s32 k);

/* ix18e LEVER: the count must be COPIED into a local declared AFTER the
 * pointer and assigned BEFORE it.  Verbatim from insect_InsectBattleDrawMarkerModels_4f4a30.cpp. */
static inline void clr(void *p, u32 n)
{
    u8 *q;
    u32 c;

    c = n;
    q = (u8 *)p;
    if (q != 0) {
        do {
            *q = 0;
            c--;
            q++;
        } while (c != 0);
    }
}

extern "C" void insect_InsectBattleDrawPreviewModel_4f5fc0(O *o, s32 mode)
{
    s32   r[4] __attribute__((aligned(16)));
    Q     q __attribute__((aligned(16)));
    V4    d __attribute__((aligned(16)));
    V4    c __attribute__((aligned(16)));
    f32   v[4] __attribute__((aligned(16)));
    f32   w[4] __attribute__((aligned(16)));
    f32   u[4] __attribute__((aligned(16)));
    f32   y[4] __attribute__((aligned(16)));
    f32   z[4] __attribute__((aligned(16)));
    P    *p;
    E    *e;
    H    *h;
    void *g;
    s32   ok;
    s32   i;
    s32   n;
    f32   kf;
    f32   t;
    f32   s;

    p = &o->f5B30;
    e = 0;
    if (p != 0) {
        ok = 0;
        if (mode == 0 && insect_InsectBattleGetState_50d6f0(o, 0) == 0x1B) {
            ok = 1;
            e = &o->f0890;
        }
        if (mode == 1 && insect_InsectBattleGetState_50d6f0(o, 0) == 0x1C) {
            ok = 1;
            e = &o->f1020;
        }
        if (e == 0 || ok == 0) {
            return;
        }
        {
            {
                if (insect_InsectBattleGetState_50d6f0(o, 0) == 0x1B) {
                h = 0;
                if (p != 0) {
                    h = InsectCageAdjFindById_3916e0(p->f054);
                }
                if (h == 0) {
                    return;
                }
                e->f450 = 0;
                *(WH *)&v[0] = *(WH *)&D_00480E80;
                *(WH *)&v[2] = *(WH *)&D_00480E88;
                v[2] = 70.0f;
                v[0] = 0.0f;
                v[1] = 0.0f;
                ModelSetPos_151110(e, v);
                clr(w, 0x10);
                w[2] = 0.0f;
                w[0] = D_0047D410;
                w[1] = D_0047D414;
                ModelSetRot_151080(e, w);
                t = h->f004;
                clr(u, 0x10);
                u[0] = t;
                u[1] = t;
                u[2] = t;
                ModelSetScale_150ff0(e, u);
                DrawModelPreview_28be80(e, h->f008, h->f00C);
            } else {
                g = DrawListBeginPrim_141b00(o->f0C0);
                DrawEnvGetFrameRect_145040(o->f0C0, r);
                GsPktEnableZTest_13e460(g, 0);
                GsPktSetZTest_13e450(g, 0);
                GsPktSetTextured_13e400(g, 0);
                GsPktSetAlphaBlend_13e500(g, 0);
                GsPktSetZWriteMask_13e430(g, 0);
                GsPktSetFrameMask_13e420(g, 2);
                GsPktOpenPrim_13f730(g, 6);
                GsPktSetRGBAQ_13ee40(g, 0x80, 0x80, 0x80, 0x80);
                i = r[1];
                while (i < r[3]) {
                    GsPktSetXYZPixel_13f110(g, i, r[0], 0);
                    GsPktSetXYZPixel_13f110(g, i + 0x20, r[2], 0);
                    i += 0x20;
                }
                GsPktClose_13f5b0(g);
                DrawListEndPrim_141a20(o->f0C0);
                ViewStackPush_144430(o->f0C0);
                ViewSetFov_142f10(o->f0C0, D_0047D7F8);
                q.vptr = D_00470090;
                ((VQ *)&q)->s15();
                clr(&d, 0x10);
                *(V2 *)&c.x = *(V2 *)&D_00480F30;
                *(V2 *)&c.z = *(V2 *)&D_00480F38;
                *(rg_s128 *)&q.f060 = *(rg_s128 *)&d;
                *(rg_s128 *)&q.f050 = *(rg_s128 *)&c;
                CameraBaseApplyLookAt_15fa80(&q);
                CameraSetViewFromCameraBase_142dd0(o->f0C0, &q, 0, 0);
                DrawListAddViewPacket_1482e0(o->f0C0);
                DrawListAddCameraMatrixPacket_1481b0(o->f0C0);
                switch (insect_InsectBattleGetState_50d6f0(o, 0)) {
                case 0x1C: {
                    kf = 50.0f;
                    s = Tanf_1290b8(D_0047D80C) * (-D_0047D810 * kf) / 0.75f;
                    t = Tanf_1290b8(D_0047D80C) * (-D_0047D7A4 * kf);
                    *(WH *)&y[0] = *(WH *)&D_00480E80;
                    *(WH *)&y[2] = *(WH *)&D_00480E88;
                    y[1] = t;
                    y[2] = 50.0f;
                    y[0] = s;
                    ModelSetPos_151110(e, y);
                    clr(z, 0x10);
                    z[0] = 0.0f;
                    z[2] = 0.0f;
                    z[1] = D_0047D1FC;
                    ModelSetRot_151080(e, z);
                    if (insect_InsectBattleTestFlag_50da40(o, 0x1B) != 0) {
                        e->f464 = 0x1F;
                        e->f468 = 1;
                        insect_InsectBattleClearFlag_50da90(o, 0x1B);
                    }
                } break;
                }
                n = e->f4DC;
                if (n > 0) {
                    DrawListAddTexLoad_1418c0(o->f0C0, n, 1.0f);
                    ((VE *)e)->s07();
                }
                ViewStackPop_1443e0(o->f0C0);
                DrawListAddViewPacket_1482e0(o->f0C0);
                }
            }
        }
    }
}
