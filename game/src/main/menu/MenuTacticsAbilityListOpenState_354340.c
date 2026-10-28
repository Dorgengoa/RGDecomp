/* rgp:protos */
#define RGP_SELF_MenuTacticsAbilityListOpenState_354340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    u8 pad8[0x14 - 8];
    s16 unk14;
    s16 unk16;
} Elem0028EA40_00354340;

typedef struct {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
} Elem20_00354340;

typedef struct {
    u8 pad0[0x20];
    Elem20_00354340 *unk20;
} Elem0028EA40_2;

typedef struct {
    u8 pad0[0x72];
    s16 unk72;
} Obj0048237C_00354340;

/*rgp*/                         /* extern */
/*rgp*/      /* extern */
/*rgp*/                   /* extern */
/*rgp*/                   /* extern */
/*rgp*/              /* extern */
/*rgp*/             /* extern */
/*rgp*/    /* extern */
/*rgp*/                   /* extern */
/*rgp*/    /* extern */
/*rgp*/              /* extern */
/*rgp*/              /* extern */
void strcpy(void *, void *);                        /* extern */
extern u8 D_00462AA0[0x20];
extern f32 D_0047D5D0;
extern f32 D_0047D600;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern Obj0048237C_00354340 *D_0048237C;
extern s32 D_004823D8;
extern s16 D_00482F14;

s32 MenuTacticsAbilityListOpenState_354340(s32 arg0, s32 arg1) {
    Elem0028EA40_00354340 *temp_2;
    Elem0028EA40_2 *temp_2_2;
    Elem20_00354340 *temp_3;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x23, 0);
        temp_2 = ((Elem0028EA40_00354340 *)UiEntryListFindByTag_28ea40(D_00482364, 0x23));
        temp_2->unk14 = D_00482F14;
        temp_2->unk16 = 0;
        UiSetWidgetPos_290f60(D_00482360, 0x1A6, temp_2->unk4, temp_2->unk6);
        temp_2_2 = ((Elem0028EA40_2 *)UiFindWidget_290460(D_00482360, 0xC6));
        if (temp_2_2 == NULL) {
            return 0;
        }
        temp_3 = temp_2_2->unk20;
        if (temp_3 == NULL) {
            return 0;
        }
        {
            {
                temp_3->unk4 = 0x156;
                temp_3->unk6 = 0x16;
                temp_3->unk8 = 0x34;
                temp_3->unkA = 0x1E;
                temp_3->unkC = 0x4C;
                temp_3->unkE = 0x18;
                strcpy((u8 *) temp_2_2 + 4, D_00462AA0);
                D_0048237C->unk72 = 0;
                UiSetWidgetsVisibleById_291110(D_00482360, 0xC6, 1, 1);
                UiSetWidgetAlpha_2907a0(D_00482360, 0xC6, 0.5f);
                UiSetWidgetPos_290f60(D_00482360, 0xC6, 0x18, 0x39);
                UiSetWidgetsVisibleById_291110(D_00482360, 0x38, 1, 1);
                UiSetWidgetsVisibleById_291110(D_00482360, 0x37, 1, 1);
                UiSetWidgetColor_2905b0(D_00482360, 0x37, 0.0f, 0.0f, 0.0f, D_0047D600);
                UiSetWidgetPos_290f60(D_00482360, 0x38, 0x11A, -0x28);
                UiSetWidgetPos_290f60(D_00482360, 0x37, 0x11D, -0x25);
                UiMoveWidgetUniform_290f50(D_00482360, 0x38, 0x11A, 0x12, D_0047D5D0, 0);
                UiMoveWidgetUniform_290f50(D_00482360, 0x37, 0x11D, 0x15, D_0047D5D0, 0);
                UiSetTextString_28f510(D_00482360, 0x38, MsgTableLookup_28aa30(D_004823D8, 0xBB8), 0);
            }
        }
    }
    StateMachineSetState_28ede0(D_0048235C, 0xA0, 0);
    return 1;
}
