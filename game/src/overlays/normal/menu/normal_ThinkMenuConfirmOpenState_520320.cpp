/* rgp:protos */
#line 1
#include "types.h"
/* normal 0x00520320 -- the shop/talk portrait panel's one-shot build: the
 * 0x753C frame, three 0x753F sub-images taken out of D_00481BBC, the actor
 * model spawned through func_3C86E0 and pointed at the 0x753F widget, then the
 * four 0x753F corner offsets.  The tail runs on EVERY call.
 *
 * `$4` is never read -- another member of the f(void *, s32) state-handler
 * family; the guard is on `b`, and the function returns 1.
 * One VIRTUAL call (`lw $25,0($2) / lw $25,0x4C($25) / jalr $25`), so this unit
 * is .cpp: a struct of function pointers gives `jalr $v0`, only a real C++
 * `virtual` gives `jalr $t9`.  mwcc puts the first virtual at vtable +0x08, so
 * 0x4C is index (0x4C-8)/4 = 17; the placeholder list is expanded by
 * build/n_gen520320.py from that OFFSET so the index cannot drift.
 *
 * `w = func_28F620(...)` is captured in func_1FEDE0's DELAY SLOT, which reads
 * as the wrong call's result -- the two calls are consecutive statements.
 * `addiu $6,$0,1 / daddu $7,$6,$0` is mwcc SHARING the constant between
 * arguments 3 and 4, not two source constants. */

struct Ent {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void attach(void *p) { VCM(void, (void *, void *), 0x4C, p); }  /* slot 17 -> vtable +0x4C */
};

typedef struct Hdl  { u8 pad00[4]; s16 f04; s16 f06; u8 pad08[0x14 - 8];
                      s16 f14; s16 f16; } Hdl;
typedef struct Wgt  { u8 pad00[4]; void *f04; } Wgt;
typedef struct Ctx  { u8 pad00[0x18]; s32 f18; } Ctx;
typedef struct Sess { u8 pad00[0x11]; s8 f11; } Sess;

extern "C" u8 normal_D_00528030;

extern "C" f32    D_0047DADC;     /* gp - 0x7694 */
extern "C" void  *D_00481BBC;     /* gp - 0x35B4 */
extern "C" void  *D_00484920;     /* gp - 0x850  */
extern "C" s32    D_00484928;     /* gp - 0x848  */
extern "C" Sess  *D_00484934;     /* gp - 0x83C  */
extern "C" s32    D_00484944;     /* gp - 0x82C  */

extern "C" Ctx         *GetGameData_1fede0(void);
extern "C" f32          GameSceneGetTimeStep_1ceba0(s32 a);
extern "C" s32          GetCurrentScene_1f5be0(void);
extern "C" const void  *MsgTableLookup_28aa30(void *a, s32 id);
extern "C" Hdl         *UiEntryListFindByTag_28ea40(const u8 *a, s32 id);
extern "C" void         StateMachineSetState_28ede0(void *a, s32 id, s32 c);
extern "C" void         UiSetTextCenteredX_28f300(void *a, u16 id, s32 c, s32 d);
extern "C" void         UiSetTextString_28f510(void *a, u16 id, const void *p, s32 d);
extern "C" Wgt         *UiGetWidgetText_28f620(void *a, u16 id, s32 c);
extern "C" void         UiFadeWidgetAlpha_290690(void *a, u16 id, f32 x, f32 y, f32 z);
extern "C" void         UiSetWidgetPos_290f60(void *a, u16 id, s32 x, s32 y);
extern "C" void         UiSetWidgetsVisibleById_291110(void *a, u16 id, s32 c, s32 d);
extern "C" Ent         *InvFindByCategoryIndex_3c86e0(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern "C" void         normal_ThinkMenuPromptScrollStep_521660(f32 x);

extern "C" s32 normal_ThinkMenuConfirmOpenState_520320(void *a, s32 b);

s32 normal_ThinkMenuConfirmOpenState_520320(void *a, s32 b)
{
    Wgt *w;
    Ctx *c;
    Hdl *h;
    Ent *o;

    if (b != 0) {
        UiSetWidgetsVisibleById_291110(D_00484920, 0x753C, 1, 1);
        UiSetWidgetPos_290f60(D_00484920, 0x753C, 0x92, 0xA2);
        UiFadeWidgetAlpha_290690(D_00484920, 0x753C, 1.0f, D_0047DADC, 0.0f);
        UiSetTextString_28f510(D_00484920, 0x753F, MsgTableLookup_28aa30(D_00481BBC, 0x56), 1);
        UiSetTextString_28f510(D_00484920, 0x753F, MsgTableLookup_28aa30(D_00481BBC, 0x52), 2);
        UiSetTextString_28f510(D_00484920, 0x753F, MsgTableLookup_28aa30(D_00481BBC, 0x53), 3);
        w = UiGetWidgetText_28f620(D_00484920, 0x753F, 0);
        c = GetGameData_1fede0();
        h = UiEntryListFindByTag_28ea40(&normal_D_00528030, 0x7531);
        o = InvFindByCategoryIndex_3c86e0(c->f18, 0, D_00484934->f11, h->f14, h->f16, 0);
        if (o != 0 && w != 0) {
            o->attach(w->f04);
        }
        h = UiEntryListFindByTag_28ea40(&normal_D_00528030, 0x7532);
        UiSetWidgetPos_290f60(D_00484920, 0x7543, h->f04, h->f06);
        UiSetTextCenteredX_28f300(D_00484920, 0x753F, 0x7B, 0);
        UiSetTextCenteredX_28f300(D_00484920, 0x753F, 0x7B, 1);
        UiSetTextCenteredX_28f300(D_00484920, 0x753F, 0x50, 2);
        UiSetTextCenteredX_28f300(D_00484920, 0x753F, 0xA0, 3);
        D_00484944 = 0;
    }
    normal_ThinkMenuPromptScrollStep_521660(GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0()));
    StateMachineSetState_28ede0(&D_00484928, 0x7535, 0);
    return 1;
}
