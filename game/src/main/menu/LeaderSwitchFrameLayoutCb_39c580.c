/* rgp:protos */
#define RGP_SELF_LeaderSwitchFrameLayoutCb_39c580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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
extern u8 D_004E9610[0x400];

typedef struct { u8 pad[0x12]; s16 unk12; } A39c;

s32 LeaderSwitchFrameLayoutCb_39c580(A39c *arg0)
{
    void *o;
    s32 h;
    void *w;
    s32 t;

    o = GetGameData_1fede0();
    if (o == NULL) {
        return 0;
    }
    h = ((s32)GetMenuResGroup_206a40());
    if (h == 0) {
        return 0;
    }
    w = UiFindWidget_290460(D_004E9610, 2);
    if (w == NULL) {
        return 0;
    }
    if (PartyCountMembers_3c2010(*(s32 *)((u8 *)o + 0x18), 1, 1) >= 3) {
        t = ResGroupListFindValueById_42c3a0(h, 0x715D);
        *(s32 *)((u8 *)w + 0x20) = t;
        if (t == 0) {
            return 0;
        }
        UiLayoutWindowFrame_28b8e0(t, 0x60, 0x3E, 2);
    } else {
        t = ResGroupListFindValueById_42c3a0(h, 0x715E);
        *(s32 *)((u8 *)w + 0x20) = t;
        if (t == 0) {
            return 0;
        }
        UiLayoutFrameRectsMaybe_28bbb0(t, 0x60, 0x24);
    }
    UiSetSpriteW_28fbf0(D_004E9610, 2, 0, arg0->unk12 + 4);
    UiSetSpriteUvW_28f850(D_004E9610, 2, 0, arg0->unk12 + 4);
    UiSetWidgetPos_290f60(D_004E9610, 1, 0xD2, arg0->unk12 * 0x1B + 0xC4);
    return 1;
}
