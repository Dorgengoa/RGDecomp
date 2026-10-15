/* PARKED s17b: not attempted, no draft read yet this session. See
   asm/matchings/main/MenuPartyCursorInputCbMaybe_2ba060.s and build/b_drafts/MenuPartyCursorInputCbMaybe_2ba060.txt
   (m2c draft already generated, just not worked). */
/* s49m: MATCH */
#include "types.h"

typedef struct Menu {
    u8 pad0[0x10];
    s16 cur;
    s16 mode;
} Menu;

extern u8 *GetGameData_1fede0(void);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern s32 PartyCountReserve_3c1c20(s32, s32, s32);
extern s32 PadIsTriggered_1839f0(void *, s32);
extern s32 PadIsRepeatTriggered_183dd0(void *, s32);
extern void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
extern u8 *UiFindWidget_290460(s32, s32);
extern void MenuPartyPanelIconSizesResetMaybe_29ddf0(s32, s32);
extern s32 GetMenuResGroup_206a40(void);
extern s32 ResGroupListFindValueById_42c3a0(s32, s32);
extern void MenuSetCursorPos_29faf0(s32, s32, s32);
extern void MenuLayoutPartyPanelMaybe_29cfb0(s32, s32, s32, s32, s32);
extern void MenuLayoutPartyFramesMaybe_29cb70(s32, s32, s32, s32);
extern void MenuSetPartyEquipIcon_29ec60(s32, s32, s32, s32);
extern void MenuPartyCharaIconsLayoutMaybe_29ad30(s32, s32, s16);
extern void MenuShowCharaStats_29bb00(s32, s32);
extern s32 D_00482360;
extern s32 D_00482370;
extern s32 D_00482558;
extern u8 D_004B2570[];

s32 MenuPartyCursorInputCbMaybe_2ba060(Menu *o)
{
    s32 b;
    u8 *pad;
    u8 *p;
    s32 old;
    s32 n;
    u8 *w;
    s32 changed;
    s32 k;
    s32 a;

    p = GetGameData_1fede0();
    a = PartyCountMembers_3c2010(*(s32 *)(p + 0x18), 1, 1);
    b = PartyCountReserve_3c1c20(*(s32 *)(p + 0x18), 1, 1);
    pad = D_004B2570;
    if (o->mode == 0) {
        n = a;
    } else if (o->mode == 1) {
        n = b;
    }
    old = o->cur;
    changed = 0;
    if (PadIsTriggered_1839f0(pad, 4) != 0) {
        if (o->cur > 0) {
            o->cur = o->cur - 1;
            changed = 1;
        } else if (PadIsRepeatTriggered_183dd0(pad, 4) == 0) {
            o->cur = n - 1;
            changed = 1;
        }
    } else if (PadIsTriggered_1839f0(pad, 8) != 0) {
        if (o->cur < n - 1) {
            o->cur = o->cur + 1;
            changed = 1;
        } else if (PadIsRepeatTriggered_183dd0(pad, 8) == 0) {
            o->cur = 0;
            changed = 1;
        }
    }
    if (changed != 0) {
    if (old != o->cur) {
        SoundPlayScaledVolume_1b9520(D_00482558, 4, 0, 1.0f);
    }
    w = UiFindWidget_290460(D_00482360, 0xD7);
    if (w != NULL) {
        MenuPartyPanelIconSizesResetMaybe_29ddf0(D_00482370, 0xD7);
        *(s32 *)(w + 0x20) = ResGroupListFindValueById_42c3a0(GetMenuResGroup_206a40(), o->mode + 0x3A2);
    }
    MenuSetCursorPos_29faf0(D_00482370, o->cur, o->mode);
    MenuLayoutPartyPanelMaybe_29cfb0(D_00482370, 0xD7, o->cur, o->mode, 0);
    MenuLayoutPartyFramesMaybe_29cb70(D_00482370, 0xB8, o->cur, o->mode);
    k = o->cur + o->mode * a;
    MenuSetPartyEquipIcon_29ec60(D_00482370, k, 0x113, 0);
    MenuSetPartyEquipIcon_29ec60(D_00482370, k, 0x114, 1);
    MenuSetPartyEquipIcon_29ec60(D_00482370, k, 0x115, 2);
    MenuSetPartyEquipIcon_29ec60(D_00482370, k, 0x116, 3);
    MenuPartyCharaIconsLayoutMaybe_29ad30(D_00482370, 0xDB, (s16)k);
    MenuShowCharaStats_29bb00(D_00482370, k);
    }
    return 1;
}
