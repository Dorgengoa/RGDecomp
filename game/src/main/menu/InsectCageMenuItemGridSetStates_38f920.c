/* rgp:protos */
#define RGP_SELF_InsectCageMenuItemGridSetStates_38f920 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_dead_assignments off

typedef struct {
    u8 pad0[0x18];
    s32 x18;
} Ctx;

typedef struct {
    u8 pad0[0x1C];
    u16 x1C;
    u8 pad1E[2];
} Ent;

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
extern u8 D_004659F0[0x400];
extern u8 D_004659F8[0x400];
extern f32 D_0047D240;
extern f32 D_0047D288;
extern f32 D_0047D440;

void InsectCageMenuItemGridSetStates_38f920(s32 arg0, s32 arg1)
{
    Ctx *c;
    s32 i;
    s32 last;
    s32 a;
    s32 b;
    s32 h;
    Ent *e;
    s32 v;
    s32 r;

    c = ((Ctx *)GetGameData_1fede0());
    i = InvMakeIdFromCategory_3c88b0(c->x18, 0, arg0, 0, 0);
    last = InvMakeIdFromCategory_3c88b0(c->x18, 0, arg0, *(s32 *)D_004659F0 - 1, *(s32 *)D_004659F8 - 1);
    a = MenuObjCountActive_390ec0();
    InsectCageMenuGetCurCageItem_391030();
    b = InsectCageMenuGetCursorObj_390f70();
    h = GetMenuWidgetRoot_390d70();
    if (arg1 != 0) {
        UiSetWidgetColor_2905b0(h, 0x76, D_0047D288, D_0047D288, D_0047D288, 1.0f);
        { f32 o = 1.0f; UiSetWidgetColor_2905b0(h, 0x75, D_0047D440, D_0047D440, D_0047D440, o); }
        { f32 o = 1.0f; UiSetWidgetColor_2905b0(h, 0x74, D_0047D240, D_0047D240, D_0047D240, o); }
    } else {
        UiSetWidgetColor_2905b0(h, 0x76, 1.0f, 1.0f, 1.0f, 1.0f);
        UiSetWidgetColor_2905b0(h, 0x75, 1.0f, 1.0f, 1.0f, 1.0f);
        UiSetWidgetColor_2905b0(h, 0x74, 1.0f, 1.0f, 1.0f, 1.0f);
    }
    e = ((Ent *)UiGetWidgetSprite_28fe10(h, 0x76, 0));
    for (;;) {
        v = ((s32)InvFindByInvId_3c87d0(c->x18, i, 0));
        e->x1C &= 0xFFC7;
        if (arg1 == 0) {
            e->x1C |= 8;
        } else {
            r = InsectCageMenuItemUseStatus_38fb50(v, b, a);
            if (r == 1) {
                e->x1C |= 0x20;
            } else if (r == 0) {
                e->x1C |= 8;
            } else {
                e->x1C |= 0x10;
            }
        }
        if (i == last) {
            break;
        }
        i++;
        e++;
    }
}
