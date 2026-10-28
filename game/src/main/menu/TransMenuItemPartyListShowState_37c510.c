/* rgp:protos */
#define RGP_SELF_TransMenuItemPartyListShowState_37c510 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#include "types.h"

typedef struct Rect {
    s32 x, y, w, h;
} Rect;

typedef struct Desc {
    void *tex;      /* +0x00 */
    s16 *info;      /* +0x04 */
    s32 pad08[2];
    s32 x;          /* +0x10 */
    s32 y;          /* +0x14 */
    s32 w;          /* +0x18 */
    s32 h;          /* +0x1C */
    Rect rect;      /* +0x20 */
    s16 mode;       /* +0x30 */
} Desc;

typedef struct Cell {
    s16 a[8];
    f32 u, v;
    s16 b, c;
    u16 flags;
} Cell;

typedef struct Actor {
    u8 pad0[0x18];
    s32 id;
} Actor;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memset(void *, s32, u32);
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
extern f32 D_0047D970;
extern void *D_0048470C;
extern s32 D_00484710;
extern s32 D_00484720;
extern s32 D_00484740;
extern void *D_00484770;
extern u8 D_004B2570[];
extern u8 D_004E9230[];

s32 TransMenuItemPartyListShowState_37c510(s32 arg0, s32 arg1)
{
    Desc a __attribute__((aligned(16)));
    Desc b __attribute__((aligned(16)));
    s32 id;
    s32 n;
    s32 w;
    Cell *src;
    Cell *dst;
    s32 i;
    Rect *r;

    if (arg1 != 0) {
        id = ((Actor *)GetGameData_1fede0())->id;
        n = PartyCountMembers_3c2010(id, 1, 1);
        n += PartyCountReserve_3c1c20(id, 1, 1);
        UiSetTextString_28f510(D_00484710, 0x7619, MsgTableLookup_28aa30(D_00484770, 0x3EB), 0);
        UiSetTextString_28f510(D_00484710, 0x761A, MsgTableLookup_28aa30(D_00484770, 0x3EB), 0);
        memset(&a, 0, 0x34);
        memset(&b, 0, 0x34);
        a.tex = UiGetWidgetSprite_28fe10(D_00484710, 0x7619, 0);
        b.tex = UiGetWidgetSprite_28fe10(D_00484710, 0x761A, 0);
        a.info = b.info = ((s16 *)UiGetWidgetText_28f620(D_00484710, 0x761A, 0));
        b.x = 0x28;
        a.x = 0x28;
        a.y = 0xC;
        w = (n - 1) * 0x1A + 0xC;
        b.w = 0x12;
        a.w = 0x12;
        b.h = 8;
        b.rect.x = 0x62;
        a.h = 8;
        b.rect.y = n - n * 14 + 0x45;
        b.rect.w = 0x186;
        b.y = w;
        b.rect.h = 0x12C;
        r = &b.rect;
        a.rect.x = r->x; a.rect.y = r->y; a.rect.w = r->w; a.rect.h = r->h;
        b.rect.y += w / 2 + 0x1A;
        b.mode = 4;
        a.mode = 4;
        UiWindowFitToText_28d0c0(&a, 0, 0, 0);
        UiWindowFitToText_28d0c0(&b, 0, 0, 0);
        UiSetTextY_28f550(D_00484710, 0x7619, a.info[1] - 0x20, 0);
        src = UiGetWidgetSprite_28fe10(D_00484710, 0x7619, 0);
        if (src == 0) {
            return 0;
        }
        { s16 a0_ = ((volatile Cell *)src)->a[0]; UiSetWidgetPos_290f60(D_00484710, 0x7618, a0_ - *(volatile s16 *)((u8 *)src + 0x104) - 0x10, src[0].a[1]); }
        dst = UiGetWidgetSprite_28fe10(D_00484710, 0x7617, 0);
        if (dst == 0) {
            return 0;
        }
        i = 0;
        do {
            Cell *c = &src[i];
            Cell *d = &dst[i];
            d->a[0] = c->a[0];
            d->a[1] = c->a[1];
            d->a[2] = c->a[2];
            d->a[3] = c->a[3];
            d->a[4] = c->a[4];
            d->a[5] = c->a[5];
            d->a[6] = c->a[6];
            d->a[7] = c->a[7];
            d->u = c->u;
            d->v = c->v;
            d->b = c->b;
            d->c = c->c;
            d->flags = c->flags;
            d->flags = 0x40;
            i++;
        } while (i < 3);
        UiSetSpriteSizeUvSize_28f670(D_00484710, 0x7619, 0, 0, 0, 0, 4);
        UiSetTextString_28f510(D_00484710, 0x761A, 0, 0);
        MenuPartyItemSkillListLayoutMaybe_2a2ee0(D_00484740, 0x761A, 0x761D, 0x761B, 0x761C, D_00484770);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x7617, 1, 1);
        UiFadeWidgetAlpha_290690(D_00484710, 0x7617, 1.0f, D_0047D970, 0.0f);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x761A, 1, 1);
        UiFadeWidgetAlpha_290690(D_00484710, 0x761A, 1.0f, D_0047D970, 0.0f);
    }
    if ((u32)(MenuGridCursorInput_28e170(D_00484720, D_004B2570, 0, 0) - 1) < 2) {
        StateMachineSetState_28ede0(D_0048470C, 0x35, 0);
    }
    UiSelFrameAnimStep_28d820(D_004E9230, 0x7604);
    return 1;
}
