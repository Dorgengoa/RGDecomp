/* rgp:protos */
#define RGP_SELF_MenuCursorBobUpdate_35b1b0 1
#include "port/game_protos.h"
#line 1
/* PARK s16d: 1 round trip, length 0x1A0 vs retail 0x198 (2 words over);
   several field widths (unk4/unk6/unk16/unkA) are guesses. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_0047D458;

typedef struct {
    u8 pad0[0x5c];
    f32 unk5C;
    u8 pad60[0xd4];
    s32 unk134;
    s32 unk138;
    u8 pad13C[0x30];
    u8 unk16C;
} T35b1b0_arg0;

void MenuCursorBobUpdate_35b1b0(T35b1b0_arg0 *arg0, s32 arg1)
{

    f32 f1;
    f32 f20;
    s32 mode;
    void *p;
    void *p16;
    s32 x;
    s32 y;

    f1 = arg0->unk5C + D_0047D3B8;
    arg0->unk5C = f1;
    if (f1 > 0.0f) {
        arg0->unk5C = D_0047D458;
    }
    f20 = 12.0f * Sinf_128fd0(arg0->unk5C);
    switch (arg0->unk16C) {
        case 0:
        p = UiEntryListFindByTag_28ea40(arg0->unk138, 0x28);
        p16 = (u8 *)p + 4;
        x = (s32)((f32)(*(s16 *)((u8 *)p + 0x4)) + f20);
        y = *(s16 *)((u8 *)p + 0x6) + (*(s16 *)((u8 *)p + 0x16) * (*(s16 *)((u8 *)p + 0xA)));
        if (arg1 != 0) {
            UiSetWidgetPos_290f60(arg0->unk134, 0x243, x, y);
        } else {
            UiMoveWidgetUniform_290f50(arg0->unk134, 0x243, x, y, 0.25f, 0);
        }
        UiSetWidgetPos_290f60(arg0->unk134, 0x244, 0,
                     *(s16 *)((u8 *)p16 + 0x12) * (*(s16 *)((u8 *)p16 + 0x6)));
        return;
    case 1:
        p = UiEntryListFindByTag_28ea40(arg0->unk138, 0x20);
        x = (s32)((f32)(*(s16 *)((u8 *)p + 0x4)) + f20);
        y = *(s16 *)((u8 *)p + 0x6) + (*(s16 *)((u8 *)p + 0x16) * (*(s16 *)((u8 *)p + 0xA)));
        if (arg1 != 0) {
            UiSetWidgetPos_290f60(arg0->unk134, 0x1E4, x, y);
        } else {
            UiMoveWidgetUniform_290f50(arg0->unk134, 0x1E4, x, y, 0.25f, 0);
        }
        UiSelFrameAnimStep_28d820((u8 *)arg0 + 0x144, 0x1DE);
        return;
    }
}
