/* rgp:protos */
#line 1
#include "types.h"
/* factory.bin overlay, 0x004EA590 -- open the factory HUD banner for one
 * message kind.  732 bytes, 184 instructions, 7 conditional branches, 28
 * calls (br/ins 0.038): the branch-light band.
 *
 * Relocation notes: factory_D_0050CA00 and factory_D_0050FDB0 are OVERLAY data at 0x50xxxx,
 * far outside the gp window (_gp 0x00485170 +/- 0x8000), so both are declared
 * as INCOMPLETE arrays and take %hi/%lo.  D_004807E4 (_gp - 0x498C),
 * D_00484A70 (_gp - 0x700) and D_00484A84 (_gp - 0x6EC) are inside the window
 * and stay plain.
 *
 * The call at 0x004EA65C is `lw $25,0($4) / lw $25,0x70($25) / jalr $25`, so
 * this unit is .cpp: only a real C++ `virtual` gives `jalr $t9`.  Slot 0x70 is
 * index (0x70-8)/4 = 26 -- 26 placeholders, then the real one.  Same class as
 * factory_FactoryMoveShowPartInfo_4f4130.
 *
 * ★ ONE gp load into a callee-saved register, not one per use
 * ([[factory-count-the-gp-loads]]): `lw $16, -0x498C($28)` appears once and
 * every later site is `daddu $4, $16, $0`, so D_004807E4 is a NAMED LOCAL.
 *
 * ★ The style record is filled in ASCENDING FIELD-OFFSET order, and the last
 * store lands in func_28F3D0's delay slot because it is written before the
 * call.
 *
 * ★ `bgez / sra 1` twice is a signed `/ 2`, not a shift.
 *
 * ★★ THE ONE-CASE `switch`.  The 0x4189 arm is `beql $3,$2` carrying its own
 * store `addiu $17, $0, 0x4189` in the delay slot.  A plain `if (t == 4)`
 * gives `bne` + `b` with the store in the `b`'s slot -- three words wrong at
 * the right length.  [[overlay-c-pipeline]]'s discriminator decides it: a
 * SWITCH's converted branch carries a CASE BODY'S STORE, a chain's carries the
 * NEXT GUARD'S CONSTANT.  Eight spellings in one probe build; `if`, `else if`,
 * a ternary, two `goto` forms and a three-arm `switch` are all 3 bad or the
 * wrong length, and only the ONE-CASE switch nested in the `else` is exact.
 */

struct Tex {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * pick(s16 id) { return VCM(void *, (void *, s16), 0x70, id); }
};

typedef struct Res { s16 f00; } Res;

typedef struct Buf {
    u8  pad00[0xC];
    s32 f0C;
    u8  pad10[0x9C];
} Buf;                                          /* 0xAC */

typedef struct Sty {
    s32 f00;
    s32 f04;
    s32 f08;
    u8  pad0C[0x4];
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    u8  pad20[0x10];
    s16 f30;
    u8  pad32[0x2];
} Sty;                                          /* 0x34 */

typedef struct Job { u8 pad00[0x8]; s32 f08; } Job;

typedef struct Bank { u8 pad00[0x8]; void *f08; } Bank;
typedef struct Zone { u8 pad00[0x40]; Bank *f40; } Zone;
typedef struct Ctx  { u8 pad00[0x8]; Zone *f08; } Ctx;

extern "C" void *D_004807E4;                    /* _gp - 0x498C */
extern "C" void *D_00484A70;                    /* _gp - 0x700  */
extern "C" u8    D_00484A84;                    /* _gp - 0x6EC  */
extern "C" u8 factory_D_0050CA00[];
extern "C" u8 factory_D_0050FDB0[];

extern "C" void  factory_FactoryMenuBannerSetStyle_4eae00(s32 on);
extern "C" void  memset(void *p, s32 v, s32 n);
extern "C" void  MsgFormat_28a9a0(void *p, void *s, void *a, s32 n);
extern "C" void  MsgFormatParamsCtor_28aa00(void *p);
extern "C" void *MsgTableLookup_28aa30(void *bank, s32 id);
extern "C" void  UiWindowFitToText_28d0c0(Sty *s, s32 a, s32 b, s32 c);
extern "C" s32   UiGetWidgetTextHeight_28f3d0(void *w, u16 id, s32 k);
extern "C" void  UiSetTextString_28f510(void *w, u16 id, void *p, s32 k);
extern "C" s32   UiGetWidgetText_28f620(void *w, u16 id, s32 k);
extern "C" void  UiSetSpritePos_28fd10(void *w, u16 id, s32 a, s32 b, s32 c);
extern "C" s32   UiGetWidgetSprite_28fe10(void *w, u16 id, s32 k);
extern "C" void  UiSetWidgetVisible_290010(void *w, u16 id, s32 a, s32 b);
extern "C" void  UiFadeWidgetAlpha_290690(void *w, u16 id, f32 a, f32 b, f32 c);
extern "C" void  UiSetWidgetsVisibleById_291110(void *w, u16 id, s32 a, s32 b);
extern "C" Job  *FactoryGetRequestPtr_367ec0(void);
extern "C" Ctx  *GetGameData_1fede0(void);
extern "C" void *GetDrawCtx_15de80(void);
extern "C" s32   DrawEnvGetHeight_1451d0(void *h);

extern "C" void factory_FactoryMenuShowNotice_4ea590(s32 kind);

void factory_FactoryMenuShowNotice_4ea590(s32 kind)
{
    Buf   buf __attribute__((aligned(16)));
    Sty   sty __attribute__((aligned(16)));
    void *w;
    Tex  *tex;
    Res  *res;
    Ctx  *ctx;
    s32   id;
    s32   n;
    s32   t;

    factory_FactoryMenuBannerSetStyle_4eae00(0);
    w = D_004807E4;
    UiSetTextString_28f510(w, 0x1A, factory_D_0050CA00, 0);
    if (kind == 0xAA) {
        MsgFormatParamsCtor_28aa00(&buf);
        memset(&buf, 0, 0xAC);
        memset(factory_D_0050FDB0, 0, 0x20);
        t = FactoryGetRequestPtr_367ec0()->f08;
        id = -1;
        if (t != 2) {
            switch (t) {
            case 4:
                id = 0x4189;
                break;
            }
        } else {
            id = 0x418F;
        }
        ctx = GetGameData_1fede0();
        if (ctx == 0) {
            return;
        }
        tex = (Tex *)ctx->f08->f40->f08;
        res = (Res *)tex->pick(id);
        if (res == 0) {
            return;
        }
        buf.f0C = res->f00;
        MsgFormat_28a9a0(factory_D_0050FDB0, MsgTableLookup_28aa30(D_00484A70, kind), &buf, 1);
        UiSetTextString_28f510(w, 0x1A, factory_D_0050FDB0, 0);
    } else {
        UiSetTextString_28f510(w, 0x1A, MsgTableLookup_28aa30(D_00484A70, kind), 0);
    }
    UiSetTextString_28f510(w, 0x1A, factory_D_0050CA00, 1);
    UiSetTextString_28f510(w, 0x1A, factory_D_0050CA00, 2);
    memset(&sty, 0, 0x34);
    sty.f00 = UiGetWidgetSprite_28fe10(w, 0x1A, 0);
    sty.f04 = UiGetWidgetText_28f620(w, 0x1A, 0);
    sty.f08 = 0xAA;
    sty.f10 = 0x3B;
    sty.f14 = 0x13;
    sty.f18 = 0x29;
    sty.f1C = 0xB;
    sty.f30 = 1;
    n = UiGetWidgetTextHeight_28f3d0(w, 0x1A, 0) + 0x13;
    UiSetSpritePos_28fd10(w, 0x1B, 0xB9, DrawEnvGetHeight_1451d0(GetDrawCtx_15de80()) / 2 - n / 2 + 8, 0);
    UiWindowFitToText_28d0c0(&sty, 0, 0, 0);
    D_00484A84 = 0;
    UiSetWidgetVisible_290010(w, 0x1A, 1, -1);
    UiSetWidgetsVisibleById_291110(w, 0x1B, 1, 1);
    UiSetWidgetsVisibleById_291110(w, 0x1C, 0, 1);
    UiSetWidgetsVisibleById_291110(w, 0x1D, 0, 1);
    UiFadeWidgetAlpha_290690(w, 0x1A, 1.0f, 0.125f, -1.0f);
}
