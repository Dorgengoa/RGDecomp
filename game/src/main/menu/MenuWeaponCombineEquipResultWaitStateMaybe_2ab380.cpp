/* rgp:protos */
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK (round 1): length 0x168 vs retail 0x158. */
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define S8F(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U8F(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern void ReturnZero_207fe0(void);
extern void PlayMenuSe_289ef0(s32);
extern void UiSelFrameAnimStep_28d820(void *, s32);
extern s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void *MenuGetSelItem_2a02d0(s32);
extern void MenuItemGridMarkInUse_2a4860(s32, s32);
extern void MenuWeaponCombineAnimTickMaybe_361cd0(void *);
extern void MenuWeaponCombineAutoHideTick_362700(void *);
extern void **ItemFindOwnerChara_3d4d80(void *, s32);
extern s32 D_0048235C;
extern s32 D_00482364;
extern s32 D_00482374;
extern void *D_00482384;
extern s16 D_004824FC;
extern u8 D_004B2570[];
extern u8 D_004DB430[];

typedef void (*fn398_t)(void **, void *);
typedef void (*fn39c_t)(void **, void *);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(void * x0) { VCM(void, (void *, void *), 0x398, x0); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(void * x0) { VCM(void, (void *, void *), 0x39C, x0); }
};
s32 MenuWeaponCombineEquipResultWaitStateMaybe_2ab380(s32 pad0, s32 arg1)
{
    s32 temp_2;
    s8 temp_4;
    void **temp_2_2;
    void *temp_16;
    void *var_16;
    void *vt;

    if (arg1 != 0) {
        ReturnZero_207fe0();
        D_004824FC = 0;
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
    }
    temp_2 = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 1, 0);
    if (D_004824FC < 0x3C) {
        D_004824FC += 1;
    } else {
        if ((u32) (temp_2 - 1) < 2U) {
            PlayMenuSe_289ef0(5);
            if (U8F(D_00482384, 0x81) != 0) {
                var_16 = PTR(D_00482384, 0x7C);
                if (var_16 == NULL) {
                    var_16 = MenuGetSelItem_2a02d0(D_00482374);
                }
                temp_2_2 = ItemFindOwnerChara_3d4d80(var_16, 0);
                temp_4 = S8F(PTR(var_16, 0x10), 2);
                if (temp_4 == 0) {
                    ((VC_0 *)(temp_2_2))->f(var_16);
                } else if (temp_4 == 1) {
                    ((VC_1 *)(temp_2_2))->f(var_16);
                }
                MenuItemGridMarkInUse_2a4860(D_00482374, 0x74);
                U8F(D_00482384, 0x81) = 0U;
            }
            S8F(D_00482384, 0x82) = 0;
            D_004824FC = 0;
            StateMachineSetState_28ede0(D_0048235C, 0x25, 0);
        }
    }
    temp_16 = D_00482384;
    MenuWeaponCombineAutoHideTick_362700(temp_16);
    MenuWeaponCombineAnimTickMaybe_361cd0(temp_16);
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}

}
