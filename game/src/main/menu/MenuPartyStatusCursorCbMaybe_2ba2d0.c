/* rgp:protos */
#define RGP_SELF_MenuPartyStatusCursorCbMaybe_2ba2d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
    s16 unk12;
} Obj0Arg0;

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
} Obj001fede0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00482360;
extern s32 D_00482370;
extern s16 D_0048253E;

s32 MenuPartyStatusCursorCbMaybe_2ba2d0(Obj0Arg0 *arg0)
{
    s32 temp_17;
    void *temp_2;

    MenuPartyCursorClampMaybe_2ba420((void *)arg0);
    temp_2 = UiFindWidget_290460(D_00482360, 0xD7);
    if (temp_2 != NULL) {
        MenuPartyPanelIconSizesResetMaybe_29ddf0(D_00482370);
        *(s32 *)((u8 *) temp_2 + 0x20) = ResGroupListFindValueById_42c3a0(((s32)GetMenuResGroup_206a40()), arg0->unk12 + 0x3A2);
    }
    MenuSetCursorPos_29faf0(D_00482370, arg0->unk10, arg0->unk12);
    MenuLayoutPartyPanelMaybe_29cfb0(D_00482370, 0xD7, arg0->unk10, arg0->unk12);
    MenuLayoutPartyFramesMaybe_29cb70(D_00482370, 0xB8, arg0->unk10, arg0->unk12);
    {s32 c=PartyCountMembers_3c2010(((Obj001fede0 *)GetGameData_1fede0())->unk18,1,1);s32 y=arg0->unk12,x=arg0->unk10;temp_17=x+y*c;}
    MenuSetPartyEquipIcon_29ec60(D_00482370, temp_17, 0x113, 0);
    MenuSetPartyEquipIcon_29ec60(D_00482370, temp_17, 0x114, 1);
    MenuSetPartyEquipIcon_29ec60(D_00482370, temp_17, 0x115, 2);
    MenuSetPartyEquipIcon_29ec60(D_00482370, temp_17, 0x116, 3);
    MenuPartyCharaIconsLayoutMaybe_29ad30(D_00482370, 0xDB, (s16)temp_17);
    MenuShowCharaStats_29bb00(D_00482370, temp_17);
    D_0048253E = arg0->unk12;
    return 1;
}
