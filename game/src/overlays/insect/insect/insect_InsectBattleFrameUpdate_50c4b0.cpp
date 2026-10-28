/* rgp:protos */
#line 1
/* Exact 4,228-byte INSECT function. Message 506 is "%s : %s ACE : %s"
 * and takes three variadic values; message 505 additionally takes the level.
 * The then arm deliberately has one fewer argument. See FINDINGS.md.
 */
#include "types.h"

/* vptr +0xC0; slots 0xA4 / 0xA8 are virtuals #39 / #40 (8 + 4*N) */
class VE {
public:
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;  
      
      
      
      
     void s16() { VCM0(void, 0x48); } 
      
      
      
      
      void s32() { VCM0(void, 0x88); }
      
      
    void s39(f32 *v) { VCM(void, (void *, f32 *), 0xA4, v); }           /* slot 0xA4 */
    void s40(f32 *v) { VCM(void, (void *, f32 *), 0xA8, v); }           /* slot 0xA8 */
};

/* vptr +0x1B0; slots 0x18 / 0x44 are virtuals #4 / #15 */
class MD {
public:
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;  
    
    void t04(f32 a) { VCM(void, (void *, f32), 0x18, a); }            /* slot 0x18 */
      
      
      
    
    void t15(f32 a) { VCM(void, (void *, f32), 0x44, a); }            /* slot 0x44 */
    u8 pad1B4[0x448 - 0x1B4];
    f32 f448;
};

/* the wrapped two-float struct whose copy survives DSE -- verbatim from
 * insect_InsectBattleDrawPreviewModel_4f5fc0.cpp (merged, byte-identical) */
typedef struct U2 { f32 x; f32 y; } U2;
typedef struct WH { U2 v; } WH;

struct P {
    u8  pad0000[0x4344];
    s32 f4344;
};

struct EL {
    u8  pad000[0x790];
};

struct GRID {
    u8  pad000[0x994];
};

struct Cell {
    u8  pad00[0x18];
    s8  f18;
    u8  pad19[0x1A - 0x19];
    s16 f1A;
    u8  pad1C[0x1E - 0x1C];
    s16 f1E;
    u8  pad20[0x38 - 0x20];
    s8  f38;
    s8  f39;
    u8  pad3A[0x5C - 0x3A];
    s32 f5C;
    s32 f60;
    u8  pad64[0x71 - 0x64];
    s8  f71;
};

struct Cur {
    u8  pad00[0x8];
    s8  f08;
    s8  f09;
    s8  f0A;
    s8  f0B;
};

struct Part {
    s16   f00;
    s16   f02;
    void *f04;
};

struct Node {
    u8  pad00[0x8];
    s16 f08;
    u8  pad0A[0x20 - 0xA];   /* ix54: stride 32.  retail's trio is sh 8/40/72($a1) */
};

struct Anim {
    u8    pad00[0x20];
    Node *f20;
    u8    pad24[0x28 - 0x24];
    Part *f28;
};

struct O {
    u8    pad0000[0x558];
    u8    f0558[0x870 - 0x558];
    P    *f0870;
    u8    pad0874[0x878 - 0x874];
    s32   f0878;
    s32   f087C;
    s32   f0880;
    EL   *f0884;
    u8    pad0888[0x890 - 0x888];
    u8    f0890[0x1020 - 0x890];
    u8    f1020[0x17B0 - 0x1020];
    EL    arr[4];                       /* 0x17B0, stride 0x790 */
    u8    pad35F0[0x35F4 - 0x35F0];
    s32   f35F4;
    GRID  grid[2];                      /* 0x35F8, stride 0x994 */
    u8    pad4920[0x4960 - 0x4920];
    u8    f4960[0x4F90 - 0x4960];
    u8    f4F90[0x4FBC - 0x4F90];
    u8    f4FBC;
    u8    pad4FBD[0x4FD0 - 0x4FBD];
    f32   f4FD0[3];
    u8    pad4FDC[0x4FE0 - 0x4FDC];
    f32   f4FE0[3];
    u8    pad4FEC[0x5054 - 0x4FEC];
    u8    f5054[0x506C - 0x5054];
    u8    f506C[0x5080 - 0x506C];
    u8    f5080[0x50E8 - 0x5080];
    u8    f50E8[0x5178 - 0x50E8];
    u8    f5178[0x5B28 - 0x5178];
    Cell *f5B28;
    Cell *f5B2C;
    u8    pad5B30[0x5D8C - 0x5B30];
    f32   f5D8C;
    f32   f5D90;
    s8    f5D94;
    u8    pad5D95[0x5D98 - 0x5D95];
    f32   f5D98;
    u8    pad5D9C[0x5DA0 - 0x5D9C];
    s32   f5DA0;
    s32   f5DA4;
    s32   f5DA8;
    u8    pad5DAC[0x5DB0 - 0x5DAC];
    s32   f5DB0;
    u8    pad5DB4[0x5EF1 - 0x5DB4];
    u8    f5EF1;
    u8    pad5EF2[0x5F82 - 0x5EF2];
    u8    f5F82[0x5FC8 - 0x5F82];
    f32   f5FC8;
};

/* .sdata / .sbss through _gp = 0x00485170 */
extern "C" f32 D_0047D1FC;              /* _gp-0x7F74, 3.141592741f */
extern "C" f32 D_0047D278;              /* _gp-0x7EF8 */
extern "C" f32 D_0047D5D0;              /* _gp-0x7BA0 */
extern "C" f32 D_0047D7F8;              /* _gp-0x7978 */
extern "C" f32 D_0047DADC;              /* _gp-0x7694 */
extern "C" f32 D_0047DC30;              /* _gp-0x7540 */
extern "C" f32 D_0047DC80;              /* _gp-0x74F0 */
extern "C" f32 D_00480E80;              /* _gp-0x42F0 */
extern "C" f32 D_00480E88;              /* _gp-0x42E8 */
extern "C" f32 D_00480EC0;              /* _gp-0x42B0 */
extern "C" f32 D_00480EC8;              /* _gp-0x42A8 */
extern "C" f32 D_00480ED0;              /* _gp-0x42A0 */
extern "C" f32 D_00480ED8;              /* _gp-0x4298 */
extern "C" s32 D_00480EE0[2];           /* _gp-0x4290 */
extern "C" s32 D_00484F90;              /* _gp-0x1E0 */
extern "C" s8 D_00484F94;              /* _gp-0x1DC */

extern "C" u8 insect_D_00524CA0[];

extern "C" {
void  Sprintf_1343b8(void *b, s32 a, ...);
void  ModelSetRot_151080(void *e, f32 *v);
void  ModelSetPos_151110(void *e, f32 *v);
void  ModelObjPlayMotionByName_1867a0(void *e, const u8 *p, s32 n);
void  ObjGetAttachNodePos_1adec0(s32 h, s32 n, f32 *v);
VE   *ObjRecGetLiveObject_1c3bc0(P *p, s32 n);
void  ObjRecSetFlags_1c3e00(P *p, s32 a, s32 b, s32 c);
void  ObjRecSetFlag2_1c3e80(P *p, s32 a, s32 b);
void *ObjRecGetLiveObject_1c4a90(P *p, s32 n);
void  ParamTableSetAlpha_1cfb10(P *p, s32 id, f32 t);
void  UiSetTextString_28f510(s32 h, u16 id, s32 v, s32 n);
void  UiSetTextX_28f590(s32 h, u16 id, s32 v, s32 n);
Part *UiGetWidgetText_28f620(s32 h, u16 id, s32 n);
void  UiSetWidgetVisible_290010(s32 h, s32 id, s32 a, s32 b);
Anim *UiFindWidget_290460(s32 h, u16 id);   /* ix54: u16, not s32 -- an s32 param
                                     * widens every u16 id AT THE CALL */
f32   UiGetWidgetAlphaTarget_290660(s32 h, s32 id);
void  UiFadeWidgetAlpha_290690(s32 h, s32 id, f32 t, f32 s, f32 u);
f32   UiGetWidgetAlpha_290770(s32 h, s32 id);
void  UiSetTextColor_290a40(s32 h, u16 id, s32 c, s32 n);
void  UiSetWidgetPos_290f60(s32 h, s32 id, s32 x, s32 y);
void UiSetWidgetSubItemValue_291250(s32, u16, s32, long long);   /* ix54: u16 -- s32 puts
                                                   * the andi AT THE CALL */
void  UiUpdateWidgets_2913a0(s32 h);
void  DamagePopupUpdateAll_2d30e0(s32 h);
void InsectHudBarSetRatioMaybe_392370(void *, Anim *, s32, f32);
void  InsectInfoIconSetUvByIdMaybe_3929b0(void *a, s32 h, s16 id, s32 n, s32 m, s32 k);
void  UiQuadSetByModeRelated_3934d0(void *a, Anim *b, s32 x, s32 y, s32 n, s32 m);
void  InsectBattleMenuFrameNineSliceMaybe_393ac0(void *a, Anim *b, s32 x, s32 y, s32 n);
void  TextEntryUpdate_436640(s32 h);
void  insect_InsectSeqStep_4ea0a0(s32 h, void *p);
Cell *insect_InsectBoardGetPiece_4ee9a0(void *g, s16 x, s16 y);
void  insect_InsectBoardFxUpdate_4ef8d0(void *g);
void  insect_InsectBattleFadeStep_50a1e0(O *o);
s32   insect_InsectBattleGetStep_50d6a0(O *o, s32 n);
s32   insect_InsectBattleGetState_50d6f0(O *o, s32 n);
s32   insect_InsectBattleTestFlag_50da40(O *o, s32 k);
s32   insect_InsectBattleGetPieceModel_50df60(O *o, Cell *c);
s32   insect_InsectGetDamagePopupList_5108c0(void);
s32   insect_InsectSeqGet_5108d0(void);
void  insect_InsectCursorSetInput_511090(void *p);
Cur  *insect_InsectCursorSetFindPage_511e60(void *p, s32 n);
s32   insect_InsectMsgTextWidth_512ab0(void *p, void *s, s32 n);
s32   insect_InsectMsgGet_512b70(void *p, s32 n);
f32   insect_InsectPieceGetHpRatio_512e70(void *p);
void  insect_InsectTeamUpdatePieces_513750(void *p);
Cell *insect_InsectTeamGetPiece_5138d0(void *p, s32 n);
s32   insect_InsectPieceIsAce_514ac0(Cell *c);
s32   insect_InsectPieceIsKing_514b00(Cell *c);
void  insect_InsectBattleLogUpdate_51bd80(void *p);
void  insect_InsectAbilityTableGetMatchCount_51cee0(void *p);
s32  *insect_InsectAbilityTableCollect_51cef0(void *p, s8 a, s8 b, s8 c, s32 d);
void  insect_InsectBattleEffectsUpdate_51d4b0(void *p);
}

/* ix18e LEVER: the count must be COPIED into a local declared AFTER the
 * pointer and assigned BEFORE it.  Verbatim from insect_InsectBattleDrawMarkerModels_4f4a30.cpp and
 * insect_InsectBattleDrawPreviewModel_4f5fc0.cpp, both merged and byte-identical. */
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

extern "C" void insect_InsectBattleFrameUpdate_50c4b0(O *o)
{
    f32   b[4] __attribute__((aligned(16)));
    f32   e2[4] __attribute__((aligned(16)));
    f32   h2[4] __attribute__((aligned(16)));
    f32   a[4] __attribute__((aligned(16)));
    s32   id;
    f32   c2[4] __attribute__((aligned(16)));
    f32   d2[4] __attribute__((aligned(16)));
    f32   g2[4] __attribute__((aligned(16)));
    f32   k2[4] __attribute__((aligned(16)));
    f32   n3[3];
    f32   n4[3];
    P    *p;
    VE   *ve;
    MD   *md;
    EL   *el;
    void *hd;
    void *hdcut;
    Cell *cl;
    Cur  *cu;
    Part *pt;
    Node *nd;
    s32  *px;
    s32   i;
    s32   ipx;
    s32   ig2;
    Cell *clg2;
    u16   other;
    Cell *clb28;
    Cell *cl2;
    void *p5;   /* ix54: retail keeps &o->f5F82 in $s1 across FOUR sites */
    void *p5b;
    Anim *an;
    u16   idA;
    u16   idB;
    u16   idC;
    u16   idD;
    u16   idE;
    u16   idF;
    u16   idG;
    s32   side;
    s32   sub;
    s32   j;
    s32   k;
    s32   n;
    s32   v;
    s32   w;
    s32   t;
    s32   c5;
    s32   c6;
    s32   loopid;
    f32   f1;
    f32   f2;
    f32   f3;
    f32   f4;
    f32   tt;

    p = o->f0870;
    if (p != 0) {
        ve = ObjRecGetLiveObject_1c3bc0(p, p->f4344);
        if (ve != 0) {
            ve->s39(n3);
            ve->s40(n4);
            o->f4FD0[0] = n3[0];
            o->f4FD0[1] = n3[1];
            o->f4FD0[2] = n3[2];
            o->f4FE0[0] = n4[0];
            o->f4FE0[1] = n4[1];
            o->f4FE0[2] = n4[2];
        }
    }
    n = o->f5DB0;
    if (n > 0) {
        n = n - 1;
        o->f5DB0 = n;
        if (n <= 0) {
            o->f5DB0 = 0;
        }
    }
    insect_InsectBoardFxUpdate_4ef8d0(o->f4960);
    insect_InsectCursorSetInput_511090(o->f4F90);
    n = ((o->f4FBC & 0x10) != 0);
    if (n) {
        o->f4FBC = (u8)(o->f4FBC | 0x20);
        insect_InsectCursorSetInput_511090(o->f4F90);
        o->f4FBC = (u8)(o->f4FBC & 0xDF);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 9) != 0) {
        insect_InsectTeamUpdatePieces_513750(&o->grid[0]);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0xA) != 0) {
        insect_InsectTeamUpdatePieces_513750(&o->grid[1]);
    }
    insect_InsectBattleFadeStep_50a1e0(o);

    id = 0;
    if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
        id = 0x8A;
        ObjRecSetFlags_1c3e00(o->f0870, 1, 0, 0x10);
    }
    hdcut = ObjRecGetLiveObject_1c4a90(o->f0870, id);
    if (hdcut != 0) {
        f1 = 1.0f;
        ObjRecSetFlag2_1c3e80(o->f0870, 1, id);
        *(WH *)&b[0] = *(WH *)&D_00480EC0;
        *(WH *)&b[2] = *(WH *)&D_00480EC8;
        *(WH *)&a[0] = *(WH *)&D_00480E80;
        *(WH *)&a[2] = *(WH *)&D_00480E88;
        a[0] = b[0];
        a[1] = b[1];
        a[2] = b[2];
        ModelSetPos_151110(hdcut, a);
        clr(c2, 0x10);
        c2[0] = 0.0f;
        c2[2] = 0.0f;
        c2[1] = D_0047D1FC;
        ModelSetRot_151080(hdcut, c2);
        if (insect_InsectBattleGetState_50d6f0(o, 0) == 3) {
            ModelObjPlayMotionByName_1867a0(hdcut, insect_D_00524CA0, 4);
        }
        if (insect_InsectBattleTestFlag_50da40(o, 0x43) == 0) {
            tt = o->f5D98;
            if ((tt >= 0.0f && tt <= D_0047D7F8) ||
                (-tt >= 0.0f && -tt <= D_0047D7F8)) {
                f1 = 0.0f;
            }
        }
        ParamTableSetAlpha_1cfb10(o->f0870, id, f1);
        if (o->f5DA8 == 0) {
            v = (id >= 0 && id < 0xC) ? ((id * 4) + 0xC) : -1;
            ParamTableSetAlpha_1cfb10(o->f0870, v, f1);
        }
    }

    if (insect_InsectBattleTestFlag_50da40(o, 8) != 0) {
        el = o->f0884;
        if (el != 0) {
            *(WH *)&e2[0] = *(WH *)&D_00480ED0;
            *(WH *)&e2[2] = *(WH *)&D_00480ED8;
            *(WH *)&d2[0] = *(WH *)&D_00480E80;
            *(WH *)&d2[2] = *(WH *)&D_00480E88;
            f2 = 1.0f;
            d2[0] = e2[0];
            d2[1] = e2[1];
            d2[2] = e2[2];
            ModelSetPos_151110(el, d2);
            el = o->f0884;
            clr(g2, 0x10);
            g2[0] = 0.0f;
            g2[1] = 0.0f;
            g2[2] = 0.0f;
            ModelSetRot_151080(el, g2);
            if (insect_InsectBattleTestFlag_50da40(o, 0x43) == 0) {
                tt = o->f5D98;
                if ((tt >= 0.0f && tt >= D_0047DC30) ||
                    (-tt >= 0.0f && -tt >= D_0047DC30)) {
                    f2 = 0.0f;
                }
            }
            if (o->f5DA8 == 6) {
                f2 = 0.0f;
            }
            ParamTableSetAlpha_1cfb10(o->f0870, 0x9B, f2);
        }
    }

    if (insect_InsectBattleTestFlag_50da40(o, 0x1C) != 0 || insect_InsectBattleTestFlag_50da40(o, 0x1D) != 0) {
        md = 0;
        if (insect_InsectBattleTestFlag_50da40(o, 0x1C) != 0) {
            md = (MD *)o->f0890;
        }
        if (insect_InsectBattleTestFlag_50da40(o, 0x1D) != 0) {
            md = (MD *)o->f1020;
        }
        md->t15(1.0f);
        tt = md->f448;
        if (tt <= 1.0f) {
            tt += 0.125f;
            md->f448 = tt;
        }
    }

    if ((insect_InsectBattleTestFlag_50da40(o, 0x16) == 0 || insect_InsectBattleTestFlag_50da40(o, 0x17) == 0) &&
        UiGetWidgetAlphaTarget_290660(o->f0878, 0x7592) > 0.0f) {
        UiFadeWidgetAlpha_290690(o->f0878, 0x7592, 0.0f, D_0047DADC, -1.0f);
    }

    if (insect_InsectBattleTestFlag_50da40(o, 0x16) != 0) {
        if (insect_InsectBattleTestFlag_50da40(o, 0x17) != 0) {
            f3 = 0.0f;
            if (insect_InsectBattleGetState_50d6f0(o, 0) == 0x11) {
                v = insect_InsectBattleGetStep_50d6a0(o, 0);
                tt = UiGetWidgetAlpha_290770(o->f0878, 0x7592);
                if (v == 1 || (u32)(v - 0x1B) < 2U) {
                    if (tt <= 0.0f || UiGetWidgetAlphaTarget_290660(o->f0878, 0x7592) <= 0.0f) {
                        f3 = 1.0f;
                    }
                } else if (tt < 1.0f) {
                    /* ix54: retail's ELSE arm is 4 dead words, `mtc1 $v0,$f1; c.lt.s $f0,$f1`, plus
                     * the 2-word join branch the `if` alone never asks for.  mwcc DELETES an
                     * EMPTY float `if` outright (ix54 deck A: emptyif, nested, ge and a bare
                     * `(void)(tt < 1.0f)` are all byte-identical to no else at all); a SELF-STORE
                     * survives to codegen, DSE drops the store, and the compare it fed stays. */
                    f3 = f3;
                }
                nd = UiFindWidget_290460(o->f0878, 0x7592)->f20;
                t = o->f5EF1 * 0xE;
                nd[0].f08 = (s16)(t + 0xD8);
                nd[1].f08 = (s16)(t + 0xDE);
                nd[2].f08 = (s16)(t + 0xE0);
                if (tt == 0.0f || tt == 1.0f) {
                    UiFadeWidgetAlpha_290690(o->f0878, 0x7592, f3, D_0047DADC, -1.0f);
                }
            } else {
                UiFadeWidgetAlpha_290690(o->f0878, 0x7592, f3, D_0047DADC, -1.0f);
                k = 0;
                if (insect_InsectBattleTestFlag_50da40(o, 0x34) != 0) {
                    cu = insect_InsectCursorSetFindPage_511e60(o->f4F90, 2);
                    cl = insect_InsectBoardGetPiece_4ee9a0(o->f4960, (s16)(cu->f08 + cu->f0A),
                                             (s16)(cu->f09 + cu->f0B));
                    UiSetWidgetVisible_290010(o->f0878, 0x758D, 1, -1);
                    if (cl != 0) {
                        n = 3;
                        if (cl->f71 != 0) {
                            n = 2;
                        }
                        an = UiFindWidget_290460(o->f0878, 0x758D);
                        InsectBattleMenuFrameNineSliceMaybe_393ac0(o->f5054, an, 0x1F0, 0x24, 0);
                        UiQuadSetByModeRelated_3934d0(o->f5054, UiFindWidget_290460(o->f0878, 0x758E),
                                    0x1EC, 0x20, n, o->f5EF1);
                        t = o->f5DA0 - 0x1F0;
                        w = t >> 1;
                        if (t < 0) {
                            w = (t + 1) >> 1;
                        }
                        UiSetWidgetPos_290f60(o->f0878, 0x758D, w, o->f5DA4 - 0x30);
                        UiFadeWidgetAlpha_290690(o->f0878, 0x758D, 1.0f, 0.125f, -1.0f);
                        px = insect_InsectAbilityTableCollect_51cef0(o->f50E8, cl->f38, cl->f39,
                                                 cl->f18, 1);
                        insect_InsectAbilityTableGetMatchCount_51cee0(o->f50E8);
                        id = 0x1F9;
                        v = insect_InsectPieceIsAce_514ac0(cl);
                        if (v != 0) {
                            id = 0x1FA;
                        }
                        j = insect_InsectMsgGet_512b70(o->f506C, id);
                        ipx = *px;
                        c5 = cl->f5C;
                        c6 = cl->f60;
                        w = cl->f18;
                        p5 = o->f5F82;
                        if (v != 0) {
                            Sprintf_1343b8(p5, j, c5, c6, ipx);
                        } else {
                            Sprintf_1343b8(p5, j, c5, c6, w, ipx);
                        }
                        if (an != 0) {
                            v = insect_InsectMsgTextWidth_512ab0(o->f506C, p5, 2);
                            pt = an->f28;
                            if (pt != 0) {
                                t = 0x1F0 - v;
                                w = t / 2;
                                pt->f00 = (s16)w;
                                pt->f02 = 8;
                                pt->f04 = p5;
                            }
                        }
                        k = 1;
                    }
                }
                if (k == 0) {
                    UiFadeWidgetAlpha_290690(o->f0878, 0x758D, 0.0f, 0.125f, -1.0f);
                }
            }
            nd = &UiFindWidget_290460(o->f0878, 0x7593)->f20[1];
            nd->f08 = 0x2C;
            if ((o->f4FBC & (4 << o->f5EF1)) != 0) {
                nd->f08 = 0x3C;
            }
            v = o->f5DA8;
            if (v == 0 || v == 6) {
                UiSetWidgetVisible_290010(o->f0878, 0x7593, 0, -1);
                UiSetWidgetVisible_290010(o->f0878, 0x7590, 0, -1);
                UiSetWidgetVisible_290010(o->f0878, 0x7591, 0, -1);
            }
            hd = &o->grid[0];
            loopid = 0x756E;
            for (i = 0; i < 2; i++) {
                if (i != 0) {
                    loopid = 0x7575;
                }
                cl = insect_InsectTeamGetPiece_5138d0(hd, 0);
                for (j = 0; j < 5; j++) {
                    tt = insect_InsectPieceGetHpRatio_512e70(cl);
                    n = 0;
                    if (tt <= D_0047D278) {
                        n = 1;
                    }
                    if (tt <= 0.5f) {
                        n = 2;
                    }
                    if (tt <= D_0047D5D0) {
                        n = 3;
                    }
                    if (tt <= 0.0f) {
                        n = 4;
                    }
                    InsectInfoIconSetUvByIdMaybe_3929b0(o->f5054, o->f0878, (s16)(loopid + j), i, n, 0);
                    cl = (Cell *)((u8 *)cl + 0x1E8);
                }
                hd = (GRID *)((u8 *)hd + 0x994);
            }
            if (insect_InsectBattleTestFlag_50da40(o, 0x35) != 0) {
                for (i = 0; i < 2; i++) {
                    v = 0xFF7F7F7F;
                    if (i != o->f5EF1) {
                        v = 0xFF202020;
                    }
                    UiSetTextColor_290a40(o->f0878, D_00480EE0[i], v, 0);
                }
            }
            UiUpdateWidgets_2913a0(o->f0878);
        }

        if (insect_InsectBattleTestFlag_50da40(o, 0x18) != 0) {
            clb28 = o->f5B28;
            cl2 = o->f5B2C;
            p5b = o->f5054;
            if (clb28 != 0) {
                idC = (u16)0xC398;
                idD = (u16)0xC39A;
                idB = idD;
                other = idC;
                idF = (u16)0xC397;
                idE = (u16)0xC3A1;
                idA = (u16)0xC39F;
                idG = (u16)0xC39E;
                sub = 0;
                if (clb28->f71 == 1) {
                    idB = idE;
                    other = idA;
                    idF = idG;
                    idE = idD;
                    sub = 1;
                    idA = idC;
                    idG = (u16)0xC397;
                    side = 0;
                } else {
                    side = 1;
                }
                InsectHudBarSetRatioMaybe_392370(p5b, UiFindWidget_290460(o->f087C, idB), sub, insect_InsectPieceGetHpRatio_512e70(clb28)
);
                UiSetWidgetSubItemValue_291250(o->f087C, other, 0, (long long)(clb28->f1A));
                UiSetWidgetSubItemValue_291250(o->f087C, other, 1, (long long)(clb28->f1E));
                UiSetTextString_28f510(o->f087C, idF, clb28->f5C, 0);
                if (cl2 != 0) {
                    InsectHudBarSetRatioMaybe_392370(p5b, UiFindWidget_290460(o->f087C, idE), side, insect_InsectPieceGetHpRatio_512e70(cl2)
);
                    UiSetWidgetSubItemValue_291250(o->f087C, idA, 0, (long long)(cl2->f1A));
                    UiSetWidgetSubItemValue_291250(o->f087C, idA, 1, (long long)(cl2->f1E));
                    UiSetTextString_28f510(o->f087C, idG, cl2->f5C, 0);
                }
                pt = UiGetWidgetText_28f620(o->f087C, 0xC39E, 0);
                if (pt != 0) {
                    UiSetTextX_28f590(o->f087C, 0xC39E,
                                0xE0 - insect_InsectMsgTextWidth_512ab0(o->f506C, pt->f04, 2), 0);
                }
            }
            f4 = 0.0f;
            f1 = 0.0f;
            if (insect_InsectBattleTestFlag_50da40(o, 0x32) != 0) {
                f4 = 1.0f;
            }
            if (insect_InsectBattleTestFlag_50da40(o, 0x33) != 0) {
                f1 = 1.0f;
            }
            UiFadeWidgetAlpha_290690(o->f087C, 0xC394, f4, 0.125f, -1.0f);
            UiFadeWidgetAlpha_290690(o->f087C, 0xC39B, f1, 0.125f, -1.0f);
            UiUpdateWidgets_2913a0(o->f087C);
        }
        if (insect_InsectBattleTestFlag_50da40(o, 0x19) != 0) {
            UiUpdateWidgets_2913a0(o->f0880);
        }
    }

    insect_InsectBattleLogUpdate_51bd80(o->f5080);
    if (insect_InsectBattleTestFlag_50da40(o, 0x2A) != 0) {
        insect_InsectBattleEffectsUpdate_51d4b0(o->f5178);
    }
    insect_InsectSeqStep_4ea0a0(insect_InsectSeqGet_5108d0(), o->f0558);
    DamagePopupUpdateAll_2d30e0(insect_InsectGetDamagePopupList_5108c0());

    tt = o->f5D8C + 6.0f * o->f5FC8;
    o->f5D8C = tt;
    if (!(tt < 360.0f)) {
        o->f5D8C = tt - 360.0f;
    }

    if (insect_InsectBattleTestFlag_50da40(o, 0x26) != 0) {
        for (ig2 = 0; ig2 < 2; ig2++) {
            hd = &o->grid[ig2];
            clg2 = 0;
            v = -1;
            for (j = 0; j < 5; j++) {
                clg2 = insect_InsectTeamGetPiece_5138d0(hd, j);
                if (clg2 != 0 && insect_InsectPieceIsKing_514b00(clg2) != 0) {
                    v = j;
                    break;
                }
            }
            if (v != -1) {
                t = insect_InsectBattleGetPieceModel_50df60(o, clg2);
                el = &o->arr[ig2 + 2];
                if (el != 0 && t != 0) {
                    ObjGetAttachNodePos_1adec0(t, 0, h2);
                    if (clg2->f38 == 0x10) {
                        h2[1] = h2[1] + 0.5f;
                    }
                    h2[1] = h2[1] + D_0047DC80;
                    ModelSetPos_151110(el, h2);
                    tt = (D_0047D1FC * o->f5D8C) / 180.0f;
                    clr(k2, 0x10);
                    k2[0] = 0.0f;
                    k2[1] = tt;
                    k2[2] = 0.0f;
                    ModelSetRot_151080(el, k2);
                    ((MD *)el)->t04(1.0f);
                    ((MD *)el)->t15(1.0f);
                }
            }
        }
    }

    tt = o->f5D90;
    tt += 6.0f;
    o->f5D90 = tt;
    if (!(tt < 360.0f)) {
        o->f5D90 = tt - 360.0f;
    }

    if (D_00484F94 == 0) {
        D_00484F90 = (s32)(30.0f / o->f5FC8);
        D_00484F94 = 1;
    }
    v = D_00484F90 - 1;
    D_00484F90 = v;
    if (v <= 0) {
        o->f5D94 = (s8)(o->f5D94 + 1);
        if (o->f5D94 > 2) {
            o->f5D94 = 0;
        }
        D_00484F90 = (s32)(30.0f / o->f5FC8);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x44) != 0) {
        TextEntryUpdate_436640(o->f35F4);
    }
}
