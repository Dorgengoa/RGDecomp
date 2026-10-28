/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x004F5430 -- C++ virtual dispatch, vptr at +0xC0, slot 0xA4 =
 * virtual #39 (8 + 4*39).  Same class as insect_InsectBattleCamInit_4f3390 /
 * insect_InsectBattleDrawHpBars_4f5bd0 / insect_InsectBattleCamApplyTarget_4f32b0.  [[jalr-is-cpp-virtual]]
 */

class VE {
public:
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;  
      
      
      
      
     void s16() { VCM0(void, 0x48); } 
      
      
      
      
      void s32() { VCM0(void, 0x88); }
      
      
    void s39(void *p) { VCM(void, (void *, void *), 0xA4, p); }          /* slot 0xA4 */
};

struct E {
    u8 pad000[0x38];
    s8 f038;
    u8 pad039[0x4F - 0x39];
    s8 f04F;
    u8 pad050[0x71 - 0x50];
    s8 f071;
};

struct EL2 {
    u8 pad000[0x994];
};

struct O {
    u8   pad000[0xC4];
    s32  f0C4;
    s32  f0C8;
    u8   pad0CC[0x874 - 0xCC];
    VE  *f874;
    u8   pad878[0x35F8 - 0x878];
    EL2  arr[2];                        /* +0x35F8, stride 0x994 */
    u8   pad4920[0x5D94 - 0x4920];
    s8   f5D94;
};

struct Vec {
    f32 f[4];
};

struct SP {
    s32 f[4];
};

extern "C" f32 D_0047D354;
extern "C" f32 D_0047D278;
extern "C" f32 D_0047D480;

extern "C" void  DrawListAddTexLoad_1418c0(void *h, s32 id, f32 t);
extern "C" void *DrawListBeginPrim_141b00(void *h);
extern "C" void  DrawListEndPrim_141a20(void *h);
extern "C" void  ObjGetAttachNodePos_1adec0(void *x, s32 k, Vec *v);
extern "C" void  VecSub_1cbd00(Vec *d, Vec *a, Vec *b);
extern "C" void  VecNormalize_1cbb80(Vec *d, Vec *a);
extern "C" void  VecScale_1cbca0(Vec *d, Vec *a, f32 t);
extern "C" void  VecAdd_1cbdc0(Vec *d, Vec *a, Vec *b);
extern "C" s32   ProjectToScreenOffset_15d160(SP *p, Vec *v);
extern "C" s32   ScreenPointInBounds_15d4a0(Vec *v);
extern "C" void  GsPktSetAlphaBlend_13e500(void *h, s32 a);
extern "C" void  GsPktSetBlendMode_13e4f0(void *h, s32 a);
extern "C" void  GsPktSetAlphaTestFunc_13e4c0(void *h, s32 a, s32 b);
extern "C" void  GsPktEnableAlphaTest_13e4d0(void *h, s32 a);
extern "C" void  GsPktEnableZTest_13e460(void *h, s32 a);
extern "C" void  GsPktSetGouraud_13e3b0(void *h, s32 a);
extern "C" void  GsPktSetOriginMode_13e2f0(void *h, s32 a);
extern "C" void  GsPktSetTexFilter_13e3d0(void *h, s32 a);
extern "C" void  GsPktSetAntialias_13e390(void *h, s32 a);
extern "C" void  GsPktSetZTest_13e450(void *h, s32 a);
extern "C" void  GsPktSetZWriteMask_13e430(void *h, s32 a);
extern "C" void  GsPktSetTextured_13e400(void *h, s32 a);
extern "C" void  GsPktSetUseUV_13e3e0(void *h, s32 a);
extern "C" void  GsPktOpenPrim_13f730(void *h, s32 a);
extern "C" void  GsPktSetTexture_13ec00(void *h, s32 a);
extern "C" void  GsPktSetRGBAQ_13ee40(void *h, s32 a, s32 b, s32 c, s32 d);
extern "C" void  GsPktSetUV_13ed60(void *h, s32 a, s32 b);
extern "C" void  GsPktSetXYZ_13ef10(void *h, s32 x, s32 y, s32 z);
extern "C" void  GsPktClose_13f5b0(void *h);
extern "C" E    *insect_InsectTeamGetPiece_5138d0(EL2 *b, s32 i);
extern "C" s32   insect_InsectPieceTestStatus_513280(E *e, s32 k);
extern "C" s32   insect_InsectPieceIsKing_514b00(E *e);
extern "C" s32   insect_InsectPieceIsInPlay_5149e0(E *e);
extern "C" s32   insect_InsectBattleTestFlag_50da40(O *o, s32 k);
extern "C" void *insect_InsectBattleGetPieceModel_50df60(O *o, E *e);

/* ix18e LEVER (from insect_InsectBattleDrawMarkerModels_4f4a30): the count must be COPIED into a
 * local declared AFTER the pointer and assigned BEFORE it. */
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

extern "C" void insect_InsectBattleDrawPieceIcons_4f5430(O *o, void *h0)
{
    Vec v1 __attribute__((aligned(16)));
    Vec v2 __attribute__((aligned(16)));
    SP  p1 __attribute__((aligned(16)));
    Vec b1 __attribute__((aligned(16)));
    Vec b2 __attribute__((aligned(16)));
    SP  p2 __attribute__((aligned(16)));
    Vec vb __attribute__((aligned(16)));
    Vec va __attribute__((aligned(16)));
    Vec c1 __attribute__((aligned(16)));
    Vec c2 __attribute__((aligned(16)));
    void *h;
    s8  c;
    s32 i;
    s32 j;
    E *e;
    s32 k;
    s32 k2;
    EL2 *bp;
    void *x;
    s32 flag;
    s16 w;
    s32 xA;
    s32 xB;
    s32 yA;
    s32 yB;
    s32 z1;
    s32 n;
    s32 X0;
    s32 X1;
    s32 Y0;
    s32 Y1;
    s32 z2;
    s16 r;
    s16 s;
    s16 t;
    s16 u;

    c = o->f5D94;
    DrawListAddTexLoad_1418c0(h0, 0x29E, 1.0f);
    h = DrawListBeginPrim_141b00(h0);
    GsPktSetAlphaBlend_13e500(h, 1);
    GsPktSetBlendMode_13e4f0(h, 1);
    GsPktSetAlphaTestFunc_13e4c0(h, 6, 0);
    GsPktEnableAlphaTest_13e4d0(h, 1);
    GsPktEnableZTest_13e460(h, 0);
    GsPktSetGouraud_13e3b0(h, 1);
    GsPktSetOriginMode_13e2f0(h, 0);
    GsPktSetTexFilter_13e3d0(h, 1);
    GsPktSetAntialias_13e390(h, 0);
    GsPktEnableZTest_13e460(h, 1);
    GsPktSetZTest_13e450(h, 2);
    GsPktSetZWriteMask_13e430(h, 0);
    GsPktSetTextured_13e400(h, 1);
    GsPktSetUseUV_13e3e0(h, 1);
    GsPktOpenPrim_13f730(h, 6);
    for (i = 0; i < 2; i++) {
        bp = &o->arr[i];
        for (j = 0; j < 5; j++) {
            if (bp != 0) {
                e = insect_InsectTeamGetPiece_5138d0(bp, j);
                if (e != 0) {
                    if (insect_InsectPieceTestStatus_513280(e, 0x1B) != 0) {
                        clr(&v1, 0x10);
                        clr(&v2, 0x10);
                        x = insect_InsectBattleGetPieceModel_50df60(o, e);
                        if (x != 0) {
                            ObjGetAttachNodePos_1adec0(x, 0, &v1);
                            for (k2 = 0; k2 < 3; k2++) {
                                v2.f[k2] = v1.f[k2];
                            }
                            v1.f[1] = v1.f[1] + D_0047D354;
                            if (insect_InsectPieceIsKing_514b00(e) != 0) {
                                v1.f[1] = v1.f[1] + D_0047D278;
                            }
                            if (e->f038 == 0x10) {
                                v1.f[1] = v1.f[1] + 0.5f;
                                v2.f[1] = v2.f[1] + 0.5f;
                            }
                            v2.f[1] = v2.f[1] + D_0047D480;
                        }
                        if (insect_InsectBattleTestFlag_50da40(o, 0x2F) != 0) {
                            flag = 0;
                            if (insect_InsectPieceIsInPlay_5149e0(e) != 0) {
                                if (ProjectToScreenOffset_15d160(&p1, &v1) != 0) {
                                    w = 0x40;
                                    xA = p1.f[0] - 0xA0;
                                    yA = p1.f[1] - 0x1E0;
                                    xB = p1.f[0] + 0xA0;
                                    yB = p1.f[1] - 0xA0;
                                    z1 = p1.f[2];
                                    if (c > 0) {
                                        if (insect_InsectPieceTestStatus_513280(e, 3) != 0) {
                                            flag = 1;
                                            w = 0x54;
                                        }
                                    }
                                    if (insect_InsectPieceTestStatus_513280(e, 0x1C) != 0) {
                                        flag = 1;
                                    }
                                    if (flag != 0) {
                                        clr(&b1, 0x10);
                                        b1.f[0] = (f32)xA;
                                        b1.f[1] = (f32)yA;
                                        b1.f[2] = (f32)p1.f[2];
                                        clr(&b2, 0x10);
                                        b2.f[0] = (f32)xB;
                                        b2.f[1] = (f32)yB;
                                        b2.f[2] = (f32)p1.f[2];
                                        if (ScreenPointInBounds_15d4a0(&b1) == 0) {
                                            continue;
                                        }
                                        if (ScreenPointInBounds_15d4a0(&b2) == 0) {
                                            continue;
                                        }
                                        GsPktSetTexture_13ec00(h, o->f0C4);
                                        GsPktSetRGBAQ_13ee40(h, 0x80, 0x80, 0x80, 0x80);
                                        GsPktSetUV_13ed60(h, w, 0x20);
                                        GsPktSetXYZ_13ef10(h, xA, yA, z1);
                                        GsPktSetUV_13ed60(h, w + 0x14, 0x34);
                                        GsPktSetXYZ_13ef10(h, xB, yB, z1);
                                    }
                                }
                            }
                        }
                        if (insect_InsectBattleTestFlag_50da40(o, 0x30) != 0) {
                            n = e->f04F;
                            if (n > 0) {
                                o->f874->s39(&vb);
                                VecSub_1cbd00(&va, &vb, &v2);
                                VecNormalize_1cbb80(&va, &va);
                                VecScale_1cbca0(&va, &va, 2.0f);
                                VecAdd_1cbdc0(&v2, &v2, &va);
                                if (ProjectToScreenOffset_15d160(&p2, &v2) != 0) {
                                    for (k = 0; k < n; k++) {
                                        X0 = p2.f[0] - 0x110 + k * 192;
                                        X1 = p2.f[0] - 0x70 + k * 192;
                                        Y0 = p2.f[1] - 0xD0;
                                        Y1 = p2.f[1] - 0x30;
                                        z2 = p2.f[2];
                                        clr(&c1, 0x10);
                                        c1.f[0] = (f32)X0;
                                        c1.f[1] = (f32)Y0;
                                        c1.f[2] = (f32)p2.f[2];
                                        clr(&c2, 0x10);
                                        c2.f[0] = (f32)X1;
                                        c2.f[1] = (f32)Y1;
                                        c2.f[2] = (f32)p2.f[2];
                                        u = 0xA;
                                        r = 0x5E;
                                        s = 0xF6;
                                        t = 0xA;
                                        if (e->f071 == 1) {
                                            r += 0xA;
                                        }
                                        if (insect_InsectPieceTestStatus_513280(e, 0x20) != 0) {
                                            X0 = p2.f[0] - 0xF0;
                                            X1 = p2.f[0] + 0xF0;
                                            Y0 = p2.f[1] - 0x130;
                                            Y1 = p2.f[1] - 0x50;
                                            t = 0xE;
                                            r = 0;
                                            u = 0x1E;
                                            s = 0;
                                            if (e->f071 == 1) {
                                                s = 0x1E;
                                            }
                                            n = 0;
                                        }
                                        if (ScreenPointInBounds_15d4a0(&c1) == 0) {
                                            continue;
                                        }
                                        if (ScreenPointInBounds_15d4a0(&c2) == 0) {
                                            continue;
                                        }
                                        GsPktSetTexture_13ec00(h, o->f0C8);
                                        GsPktSetRGBAQ_13ee40(h, 0x80, 0x80, 0x80, 0x80);
                                        GsPktSetUV_13ed60(h, s, r);
                                        GsPktSetXYZ_13ef10(h, X0, Y0, z2);
                                        GsPktSetUV_13ed60(h, s + u, r + t);
                                        GsPktSetXYZ_13ef10(h, X1, Y1, z2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    GsPktClose_13f5b0(h);
    DrawListEndPrim_141a20(h0);
}
