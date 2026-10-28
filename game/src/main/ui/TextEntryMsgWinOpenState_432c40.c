/* rgp:protos */
#define RGP_SELF_TextEntryMsgWinOpenState_432c40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Item {
    s16 x;
    s16 y;
    u8 pad4[0x18];
    u32 col;
} Item;
typedef struct Desc {
    s32 m50;
    Item *m54;
    u8 pad58[8];
    s32 m60;
    s32 m64;
    s32 m68;
    s32 m6C;
    s32 m70;
    s32 m74;
    s32 m78;
    s32 m7C;
    s16 m80;
    u8 pad82[2];
} Desc;
typedef struct Self {
    s32 unk0;
    u8 pad4[8];
    s32 unkC;
    u8 pad10[0xD0];
    s16 unkE0;
    u8 padE2[0x164];
    u8 unk246;
} Self;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memset(void *, s32, s32);

s32 TextEntryMsgWinOpenState_432c40(Self *self, s32 arg1)
{
    Desc d __attribute__((aligned(16)));
    s32 id;
    u8 flag;
    s32 kind;
    s32 mode;
    Item *it;

    if (arg1 != 0) {
        flag = 0;
        kind = 0xC8;
        UiSetTextString_28f510(self->unk0, 0x13, 0, 1);
        id = 0;
        mode = 0;
        if (self->unk246 != 0) {
            if (self->unkE0 == 1) {
                kind = 0xE6;
            } else if (self->unkE0 == 2) {
                kind = 0xD2;
            } else if (self->unkE0 == 3) {
                flag = 1;
                kind = 0xDC;
                id = MsgTableLookup_28aa30(self->unkC, 0xDD);
                mode = 1;
            }
        } else if (self->unkE0 != 0) {
            kind = 0xC9;
        }
        UiSetTextString_28f510(self->unk0, 0x13, MsgTableLookup_28aa30(self->unkC, kind), 0);
        memset(&d, 0, 0x34);
        d.m50 = ((s32)UiGetWidgetSprite_28fe10(self->unk0, 0x13, 0));
        d.m54 = ((Item *)UiGetWidgetText_28f620(self->unk0, 0x13, 0));
        d.m60 = 0x3C;
        d.m68 = 0x1C;
        d.m64 = 0xC;
        if ((s8)flag) {
            d.m64 += 0x2E;
        }
        d.m6C = 8;
        d.m70 = 0;
        d.m78 = 0x200;
        d.m74 = 0;
        d.m7C = 0x168;
        d.m80 = 4;
        self->unk246 = 0;
        UiWindowFitToText_28d0c0(&d, &id, mode, 0);
        if ((s8)flag) {
            it = ((Item *)UiGetWidgetText_28f620(self->unk0, 0x13, 0));
            if (it != 0) {
                UiSetTextPos_28f5d0(self->unk0, 0x13, it->x, it->y + 0x2C, 1);
                UiSetTextPos_28f5d0(self->unk0, 0x13, it->x, it->y + 0x2C, 1);
                it->col = 0xFF181840;
                UiSetTextString_28f510(self->unk0, 0x13, MsgTableLookup_28aa30(self->unkC, 0xDD), 1);
            }
        }
        UiSetWidgetsVisibleById_291110(self->unk0, 0x13, 1, 1);
        UiSetWidgetAlpha_2907a0(self->unk0, 0x13, 1.0f);
    }
    TextEntrySetState_434410(self, 0x6D6B, 0);
    return 1;
}
