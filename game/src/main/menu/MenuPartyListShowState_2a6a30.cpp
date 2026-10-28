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

extern "C" Actor *GetGameData_1fede0(void);
class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 IsBusy() { return VCM0(s32, 0x368); }
};
extern "C" VObj *PartyGetSlotChara_3c2fb0(s32, s32);
extern "C" s32 MsgTableLookup_28aa30(void *, s32);
extern "C" void UiSetTextString_28f510(s32, s32, s32, s32);
extern "C" void *memset(void *, s32, u32);
extern "C" void *UiGetWidgetSprite_28fe10(s32, s32, s32);
extern "C" s16 *UiGetWidgetText_28f620(s32, s32, s32);
extern "C" void UiWindowFitToText_28d0c0(Desc *, s32, s32, s32);
extern "C" void UiSetTextY_28f550(s32, s32, s32, s32);
extern "C" void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern "C" void UiSetSpriteSizeUvSize_28f670(s32, s32, s32, s32, s32, s32, s32);
extern "C" void MenuPartyItemSkillListLayoutMaybe_2a2ee0(s32, s32, s32, s32, s32, void *);
extern "C" void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern "C" void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern "C" s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern "C" void StateMachineSetState_28ede0(void *, s32, s32);
extern "C" void UiSelFrameAnimStep_28d820(void *, s32);
extern "C" f32 D_0047D6D0;
extern "C" void *D_0048235C;
extern "C" s32 D_00482360;
extern "C" s32 D_00482364;
extern "C" s32 D_00482374;
extern "C" void *D_004823D8;
extern "C" u8 D_004B2570[];
extern "C" u8 D_004DB430[];

extern "C" s32 MenuPartyListShowState_2a6a30(s32 arg0, s32 arg1)
{
    Desc a __attribute__((aligned(16)));
    Desc b __attribute__((aligned(16)));
    Actor *actor;
    VObj *o;
    s32 n;
    s32 i;
    s32 w;
    Cell *src;
    Cell *dst;
    Rect *r;

    if (arg1 != 0) {
        actor = GetGameData_1fede0();
        n = 0;
        for (i = 0; i < 8; i++) {
            o = PartyGetSlotChara_3c2fb0(actor->id, i);
            if (o != 0 && o->IsBusy() == 0) {
                n++;
            }
        }
        UiSetTextString_28f510(D_00482360, 0x9B, MsgTableLookup_28aa30(D_004823D8, 0x3F1), 0);
        UiSetTextString_28f510(D_00482360, 0x9C, MsgTableLookup_28aa30(D_004823D8, 0x3F1), 0);
        memset(&a, 0, 0x34);
        memset(&b, 0, 0x34);
        a.tex = UiGetWidgetSprite_28fe10(D_00482360, 0x9B, 0);
        b.tex = UiGetWidgetSprite_28fe10(D_00482360, 0x9C, 0);
        a.info = b.info = UiGetWidgetText_28f620(D_00482360, 0x9C, 0);
        b.x = 0x28;
        a.y = 0xC;
        w = (n - 1) * 0x1A + 0xC;
        b.y = w;
        b.w = 0x12;
        b.h = 8;
        a.h = 8;
        a.x = 0x28;
        b.rect.x = 0x62;
        b.rect.y = 69.0f + (f32)(n - n * 14);
        a.w = 0x12;
        b.rect.w = 0x186;
        b.rect.h = 0x12C;
        r = &b.rect;
        a.rect.x = r->x; a.rect.y = r->y; a.rect.w = r->w; a.rect.h = r->h;
        b.rect.y += w / 2 + 0x1A;
        b.mode = 4;
        a.mode = 4;
        UiWindowFitToText_28d0c0(&a, 0, 0, 0);
        UiWindowFitToText_28d0c0(&b, 0, 0, 0);
        UiSetTextY_28f550(D_00482360, 0x9B, a.info[1] - 0x20, 0);
        src = (Cell *)UiGetWidgetSprite_28fe10(D_00482360, 0x9B, 0);
        if (src == 0) {
            return 0;
        }
        { s16 a0_ = ((volatile Cell *)src)->a[0]; UiSetWidgetPos_290f60(D_00482360, 0x9A, a0_ - *(volatile s16 *)((u8 *)src + 0x104) - 0x10, src[0].a[1]); }
        dst = (Cell *)UiGetWidgetSprite_28fe10(D_00482360, 0x99, 0);
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
        UiSetSpriteSizeUvSize_28f670(D_00482360, 0x9B, 0, 0, 0, 0, 4);
        UiSetTextString_28f510(D_00482360, 0x9C, 0, 0);
        MenuPartyItemSkillListLayoutMaybe_2a2ee0(D_00482374, 0x9C, 0x9F, 0x9D, 0x9E, D_004823D8);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x99, 1, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x99, 1.0f, D_0047D6D0, 0.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x9C, 1, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x9C, 1.0f, D_0047D6D0, 0.0f);
    }
    if ((u32)(MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0) - 1) < 2) {
        StateMachineSetState_28ede0(D_0048235C, 0x3E, 0);
    }
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
