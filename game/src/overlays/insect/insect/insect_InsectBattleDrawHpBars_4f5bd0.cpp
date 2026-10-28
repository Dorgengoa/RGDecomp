/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x004F5BD0 -- C++ virtual dispatch, vptr at +0xC0, slot 0xA4 =
 * virtual #39 (8 + 4*39).  Same class as insect_InsectBattleCamInit_4f3390 /
 * insect_InsectBattleCamApplyTarget_4f32b0 / insect_InsectBattleCamApplyEye_4f3320.  [[jalr-is-cpp-virtual]]
 */

class VE {
public:
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;  
      
      
      
      
      
      
      
      
      
      void s32() { VCM0(void, 0x88); }
      
      
    void s39(void *p) { VCM(void, (void *, void *), 0xA4, p); }          /* slot 0xA4 */
};

struct E {
    u8 pad000[0x38];
    s8 f038;
    u8 pad039[0x71 - 0x39];
    s8 f071;
};

struct EL2 {
    u8 pad000[0x994];
};

struct O {
    u8   pad000[0xCC];
    s32  f0CC;
    u8   pad0D0[0x874 - 0xD0];
    VE  *f874;
    u8   pad878[0x35F8 - 0x878];
    EL2  arr[2];                        /* +0x35F8, stride 0x994 */
    u8   pad4920[0x4960 - 0x4920];
    s32  f4960;
};

struct Vec {
    s32 f00;
    f32 f04;
    s32 f08;
    s32 f0C;
};

struct SP {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
};

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
extern "C" void  GsPktSetAlphaBlend_13e500(void *h, s32 a);
extern "C" void  GsPktSetBlendMode_13e4f0(void *h, s32 a);
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
extern "C" f32   insect_InsectPieceGetHpRatio_512e70(E *e);
extern "C" s32   insect_InsectPieceTestStatus_513280(E *e, s32 k);
extern "C" void *insect_InsectBattleGetPieceModel_50df60(O *o, E *e);
extern "C" void  insect_InsectBoardFindPiece_4ee190(s32 *q, E *e, s32 *a, s32 *b);

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

extern "C" void insect_InsectBattleDrawHpBars_4f5bd0(O *o, void *h0)
{
    s32 sp13C;
    s32 sp138;
    Vec v __attribute__((aligned(16)));
    Vec b2 __attribute__((aligned(16)));
    Vec a __attribute__((aligned(16)));
    SP  p __attribute__((aligned(16)));
    s32 *q;
    s32 i;
    s32 j;
    EL2 *bp;
    E *e;
    void *x;
    void *h;
    f32 fv;
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;
    s32 z;
    s32 m;

    q = &o->f4960;
    DrawListAddTexLoad_1418c0(h0, 0x29E, 1.0f);
    for (i = 0; i < 2; i++) {
        bp = &o->arr[i];
        for (j = 0; j < 5; j++) {
            e = insect_InsectTeamGetPiece_5138d0(bp, j);
            if (e != 0) {
                fv = insect_InsectPieceGetHpRatio_512e70(e);
                if (insect_InsectPieceTestStatus_513280(e, 0x1B) != 0) {
                    clr(&v, 0x10);
                    x = insect_InsectBattleGetPieceModel_50df60(o, e);
                    if (x != 0) {
                        ObjGetAttachNodePos_1adec0(x, 0, &v);
                        if (e->f038 == 0x10) {
                            v.f04 = v.f04 + 0.5f;
                        }
                        v.f04 = v.f04 + D_0047D480;
                        o->f874->s39(&b2);
                        VecSub_1cbd00(&a, &b2, &v);
                        VecNormalize_1cbb80(&a, &a);
                        VecScale_1cbca0(&a, &a, 2.0f);
                        VecAdd_1cbdc0(&v, &v, &a);
                        if (ProjectToScreenOffset_15d160(&p, &v) != 0) {
                            insect_InsectBoardFindPiece_4ee190(q, e, &sp13C, &sp138);
                            h = DrawListBeginPrim_141b00(h0);
                            if (h == 0) {
                                return;
                            }
                            GsPktSetAlphaBlend_13e500(h, 1);
                            GsPktSetBlendMode_13e4f0(h, 1);
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
                            x1 = p.x + 0x100;
                            x0 = p.x - 0x100;
                            y0 = p.y - 0x30;
                            y1 = p.y + 0x30;
                            z = p.z;
                            fv = (f32)(512.0f * fv);
                            GsPktSetTexture_13ec00(h, o->f0CC);
                            GsPktSetRGBAQ_13ee40(h, 0x80, 0x80, 0x80, 0x80);
                            GsPktSetUV_13ed60(h, 0x15D, 0xBD);
                            GsPktSetXYZ_13ef10(h, x0 - 0x10, y0 - 0x10, z);
                            GsPktSetUV_13ed60(h, 0x17E, 0xC4);
                            GsPktSetXYZ_13ef10(h, x1 + 0x10, y1 + 0x10, z);
                            m = e->f071 * 12 + 0xEA;
                            GsPktSetRGBAQ_13ee40(h, 0x80, 0x80, 0x80, 0x80);
                            GsPktSetUV_13ed60(h, 0x156, m);
                            GsPktSetXYZ_13ef10(h, x0 + 0x20, y0 + 0x20, z);
                            GsPktSetUV_13ed60(h, 0x172, m + 2);
                            GsPktSetXYZ_13ef10(h, (s32)((f32)x0 + fv) - 0x10, y1 - 0x10, z);
                            GsPktClose_13f5b0(h);
                            DrawListEndPrim_141a20(h0);
                        }
                    }
                }
            }
        }
    }
}
