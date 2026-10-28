/* rgp:protos */
#line 1
#include "types.h"
/* normal 0x00507990 -- real C++ virtual dispatch: jalr targets $25 ($t9),
 * which the sibling normal_ShopMenuItemInfoShow_509520.cpp documents as the tell for a
 * genuine `virtual` call (a plain struct-of-fnptrs would jalr $v0). mwcc
 * puts the first virtual at vtable+0x08, so offset 0x4CC is slot
 * (0x4CC-8)/4 = 305 -- pad with 305 dummy virtuals to land the call. */

struct Obj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 s305() { return VCM0(s32, 0x4CC); }
};

typedef struct Ctx {
    u8  pad000[0x18];
    s32 f18;
} Ctx;

extern "C" s32 D_0048456C;          /* gp - 0xC04 */
extern "C" s32 D_00484578;          /* gp - 0xBF8 */

extern "C" Ctx *GetGameData_1fede0(void);
extern "C" Obj *PartyGetLeaderChara_3c2820(s32 a0);
extern "C" void normal_LeaderHudPanelSlide_509040(s32, s32);
extern "C" void normal_LeaderHudSetPanelMode_506b10(s32 a0, s32 a1);
extern "C" void normal_LeaderHudSetField74Related_506b60(s32 a0, s32 a1);
extern "C" void normal_LeaderHudWeaponRefresh_508990(void);
extern "C" void normal_LeaderHudGaugeLevelRefresh_507ff0(void);

extern "C" s32 normal_LeaderHudReload_507990(void);

s32 normal_LeaderHudReload_507990(void)
{
    Ctx *ctx;
    Obj *obj;

    ctx = GetGameData_1fede0();
    if (ctx == 0) {
        return 0;
    }
    obj = PartyGetLeaderChara_3c2820(ctx->f18);
    if (obj != 0) {
        D_00484578 = obj->s305();
    } else {
        D_00484578 = -1;
    }
    normal_LeaderHudPanelSlide_509040(1, 0);
    normal_LeaderHudSetPanelMode_506b10(D_0048456C, 3);
    normal_LeaderHudSetField74Related_506b60(D_0048456C, 0);
    normal_LeaderHudWeaponRefresh_508990();
    normal_LeaderHudGaugeLevelRefresh_507ff0();
    return 1;
}
