#include "types.h"

typedef struct {
    u8 pad0[0x1C];
    s8 unk1C;
    u8 pad1D[3];
    u8 pad20[0x24 - 0x20];
    s32 unk24;
} Obj482374_002B3550;

typedef struct {
    u8 pad0[0x95];
    u8 unk95;
} Obj482384_002B3550;

typedef struct {
    u8 pad0[0x14];
    s16 unk14;
    s16 unk16;
} Elem002B3550;

typedef struct {
    u8 pad0[0x10];
} Buf002B3550;

void GetGameData_1fede0(void);
void PlayMenuSe_289ef0(s32);
Elem002B3550 *UiEntryListFindByTag_28ea40(s32, s32);
void MenuInvGridHighlightMaybe_2a0050(Obj482374_002B3550 *, s32);
void MenuShowItemCount_2a02f0(Obj482374_002B3550 *, s32, s32, s32, s32);
void MenuItemInfoPopupShow_2a33e0(Obj482374_002B3550 *, s32, s32, s32, Buf002B3550 *, s32, s32, s32, f32);
void MenuItemInfoWidgetsCache_2a65f0(Buf002B3550 *);
s32 MenuGetItemAtCell_2a7000(s32, u8 *);
void MenuCageBaitIconUpdate_2a7370(s32, s32);
void MenuItemModeApplyMaybe_2b36e0(s32, s32, s32);
void MenuWeaponCombineGridHighlightMatchingMaybe_361640(Obj482384_002B3550 *, s32);
void MenuWeaponCombineGridRefreshMaybe_3619d0(Obj482384_002B3550 *, s32);
extern s32 D_00482364;
extern Obj482374_002B3550 *D_00482374;
extern Obj482384_002B3550 *D_00482384;
extern u8 D_004823CC;
extern s32 D_004824BC;

s32 MenuItemSelectTab_2b3550(s32 arg0, s32 arg1, s32 arg2) {
    Buf002B3550 buf;
    Elem002B3550 *e;
    s32 r;
    s32 k;
    u8 v;

    MenuItemModeApplyMaybe_2b36e0(arg0, arg1, 0);
    if (D_004823CC != 0) {
        v = D_00482384->unk95;
        if (v == 1 || (s32)(v & 0xFF) == 8) {
            MenuWeaponCombineGridRefreshMaybe_3619d0(D_00482384, 1);
        } else if ((v & 0xFF) == 2 || (v & 0xFF) == 4) {
            MenuWeaponCombineGridHighlightMatchingMaybe_361640(D_00482384, 1);
        }
    } else if (D_004824BC != 0) {
        MenuInvGridHighlightMaybe_2a0050(D_00482374, 1);
    } else if (D_00482374->unk1C != 0) {
        MenuShowItemCount_2a02f0(D_00482374, 0x76, 0x74, 0x77, D_00482374->unk24);
    }
    GetGameData_1fede0();
    e = UiEntryListFindByTag_28ea40(D_00482364, 3);
    r = MenuGetItemAtCell_2a7000(arg0, (u8 *)e + 4);
    k = e->unk14 + e->unk16 * 8;
    MenuItemInfoWidgetsCache_2a65f0(&buf);
    MenuItemInfoPopupShow_2a33e0(D_00482374, r, 0x1AA, 0x1A9, &buf, 0x68, 0x15E, k, 2.0f);
    if ((s16)arg1 != 1) {
        MenuCageBaitIconUpdate_2a7370(r, 1);
    }
    if (arg2 != 0) {
        PlayMenuSe_289ef0(0xB);
    }
    return 1;
}
