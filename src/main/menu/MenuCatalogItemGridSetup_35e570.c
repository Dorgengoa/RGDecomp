#include "types.h"

typedef struct Self {
    u8 pad0[0x1D0];
    f32 f1d0;           /* +0x1D0 */
    u8 pad1d4[4];
    u8 x1d8[0x30];      /* +0x1D8 */
    s32 x208;           /* +0x208 */
    s32 x20c;           /* +0x20C */
    u8 pad210[0x10];
    s32 x220;           /* +0x220 */
    s32 x224;           /* +0x224 */
    u8 pad228[0x20];
    s16 count;          /* +0x248 */
    u8 pad24a[0x2A];
    s32 x274;           /* +0x274 */
    s32 x278;           /* +0x278 */
    u8 pad27c[0xC];
    s32 x288;           /* +0x288 */
    s32 x28c;           /* +0x28C */
} Self;

typedef struct Ref {
    u8 pad0[6];
    s16 h6;
} Ref;

typedef struct Entry {
    u8 pad0[6];
    s16 h6;
    u8 pad8[8];
    Ref *ref;           /* +0x10 */
} Entry;

typedef struct Data {
    u8 pad0[0xA];
    s16 hA;             /* +0x0A */
    u8 padc[0x10];
    u8 f0 : 1;          /* +0x1C */
    u8 f1 : 1;
    u8 f2 : 1;
    u8 f3 : 1;
} Data;

typedef struct Menu {
    u8 pad0[4];
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padc[2];
    s16 hE;
    u8 pad10[2];
    s16 h12;
    s16 h14;
    s16 h16;
    s16 h18;
    s16 h1a;
} Menu;

typedef struct Inner { u8 pad0[0xC]; s32 xC; } Inner;
typedef struct Mid { u8 pad0[0x94]; Inner *x94; } Mid;
typedef struct Actor { u8 pad0[8]; Mid *x8; u8 padc[0xC]; s32 x18; } Actor;
typedef struct Res { u8 pad0[0xC]; s32 xC; } Res;
typedef struct Found { u8 pad0[0x10]; Res *x10; } Found;

extern Actor *GetGameData_1fede0(void);
extern void InvViewCtorFromOwner_3cec70(void *, Actor *, s32, s32, s32, s32);
extern void IterInit_370170(void *, void *);
extern Entry *IterNext_370040(void *);
extern void UiSetSpriteSizeUvSize_28f670(s32, s32, s32, s32, s32, s32, s32);
extern void UiSetTextString_28f510(s32, s32, void *, s32);
extern void *MsgTableLookup_28aa30(s32, s32);
extern s32 InvIdGetMinorIndex_3d5440(s16);
extern s32 InvIdGetMidIndex_3d52b0(s16);
extern Data *DataTableFindRowById_3fd770(s32, s16);
extern void MenuCatalogItemIconUv_35ccf0(Self *, s16, s32 *, s32 *);
extern void UiSetSpriteUvRect_28f9d0(s32, s32, s32, s32, s32, s32, s32);
extern void UiSetSpriteSize_28fc30(s32, s32, s32, s32, s32);
extern f32 UiPageScrollBarLayout_289710(Self *, s32, s32, s32, s32, s32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern Menu *UiEntryListFindByTag_28ea40(s32, s32);
extern Found *InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void UiSelFrameSetPos_28daa0(void *, s32, s32, s32);
extern void MenuCatalogItemGridFill_35d5e0(Self *);
extern void MenuCatalogCursorUpdate_35eb10(Self *, s32);
extern u8 D_00462C60[];
extern s32 D_004823D8;

void MenuCatalogItemGridSetup_35e570(Self *self)
{
    u32 lst[8];
    u32 it[2];
    s32 x;
    s32 y;
    Actor *actor;
    s32 i;
    s32 max;
    Entry *e;
    s32 base;
    s32 v;
    s32 slot;
    Data *d;
    s32 sy;
    s32 sx;
    Menu *m;
    Found *o;
    s32 t;

    actor = GetGameData_1fede0();
    InvViewCtorFromOwner_3cec70(lst, actor, 6, -1, -1, -1);
    IterInit_370170(it, lst);
    for (i = 0; i < 12; i++) {
        UiSetSpriteSizeUvSize_28f670(self->x274, 0x1FA, 0, 0, 0, 0, i);
        UiSetSpriteSizeUvSize_28f670(self->x274, 0x1FB, 0, 0, 0, 0, i);
        UiSetSpriteSizeUvSize_28f670(self->x274, 0x201, 0, 0, 0, 0, i);
        UiSetSpriteSizeUvSize_28f670(self->x274, 0x202, 0, 0, 0, 0, i * 2);
        UiSetSpriteSizeUvSize_28f670(self->x274, 0x202, 0, 0, 0, 0, (u32)i * 2 + 1);
    }
    for (i = 0; i < 4; i++) {
        UiSetSpriteSizeUvSize_28f670(self->x274, 0x24E, 0, 0, 0, 0, i);
    }
    UiSetTextString_28f510(self->x274, 0x207, D_00462C60, 0);
    UiSetTextString_28f510(self->x274, 0x207, MsgTableLookup_28aa30(D_004823D8, 0x1388), 1);
    self->count = 0;
    max = 0;
    while ((e = IterNext_370040(it)) != 0) {
        self->count++;
        base = InvIdGetMinorIndex_3d5440(e->h6);
        v = InvIdGetMidIndex_3d52b0(e->h6);
        if (max < v) {
            max = v;
        }
        if (v < 3) {
            slot = base + v * 4;
            d = DataTableFindRowById_3fd770(actor->x8->x94->xC, e->ref->h6);
            if (d != 0) {
                MenuCatalogItemIconUv_35ccf0(self, d->hA, (s32 *)&x, (s32 *)&y);
                sx = x;
                sy = y;
                UiSetSpriteUvRect_28f9d0(*(volatile s32 *)&self->x274, 0x1FA, *(volatile s32 *)&x, *(volatile s32 *)&y, 0x40, 0x32, slot);
                UiSetSpriteSize_28fc30(self->x274, 0x1FA, 0x40, 0x32, slot);
                UiSetSpriteSizeUvSize_28f670(self->x274, 0x201, 0x4C, 0x54, 0x4C, 0x54, slot);
                if (d->f3) {
                    UiSetSpriteUvRect_28f9d0(self->x274, 0x1FA, x, y, 0, 0, slot);
                    UiSetSpriteSize_28fc30(self->x274, 0x1FA, 0, 0, slot);
                    UiSetSpriteUvRect_28f9d0(self->x274, 0x1FB, sx, sy, 0x40, 0x32, slot);
                    UiSetSpriteSize_28fc30(self->x274, 0x1FB, 0x40, 0x32, slot);
                    UiSetSpriteSizeUvSize_28f670(self->x274, 0x202, 0x56, 0x30, 0x56, 0x30, slot * 2);
                } else if (d->f2) {
                    UiSetSpriteUvRect_28f9d0(self->x274, 0x1FA, x, y, 0, 0, slot);
                    UiSetSpriteSize_28fc30(self->x274, 0x1FA, 0, 0, slot);
                    UiSetSpriteUvRect_28f9d0(self->x274, 0x1FB, sx, sy, 0x40, 0x32, slot);
                    UiSetSpriteSize_28fc30(self->x274, 0x1FB, 0x40, 0x32, slot);
                    UiSetSpriteSizeUvSize_28f670(self->x274, 0x202, 0x56, 0x30, 0x56, 0x26, slot * 2 + 1);
                }
            }
        }
    }
    self->f1d0 = 0.0f;
    self->f1d0 = UiPageScrollBarLayout_289710(self, 0x1F8, 0x116, 3, max + 1, 0);
    UiSetWidgetPos_290f60(self->x274, 0x1F8, 0x173, 0x1D);
    m = UiEntryListFindByTag_28ea40(self->x278, 0x24);
    m->h12 = max;
    o = InvFindByCategoryIndex_3c86e0(actor->x18, 6, 0, 0, 0, 0);
    if (o == 0) {
        UiSetWidgetsVisibleById_291110(self->x274, 0x1FC, 0, 1);
    } else {
        UiSetWidgetsVisibleById_291110(self->x274, 0x1FC, 1, 1);
        UiSetTextString_28f510(self->x274, 0x207, (void *)o->x10->xC, 0);
    }
    m->h14 = self->x208;
    m->h16 = self->x20c;
    m->h18 = self->x220;
    m->h1a = self->x224;
    self->x288 = self->x20c;
    self->x28c = self->x224;
    UiSetWidgetPos_290f60(self->x274, 0x1F8, 0x173, (f32)m->h1a * self->f1d0 + 29.0f);
    UiSetWidgetPos_290f60(self->x274, 0x20D, m->h4 + m->h14 * m->h8, m->h6 + m->h16 * m->hA);
    UiSelFrameSetPos_28daa0(self->x1d8, 0x1F6, m->h14 * m->h8 + 0x1E, m->h16 * m->hA + 0x22);
    t = m->h16;
    m->h16 = m->hE;
    MenuCatalogItemGridFill_35d5e0(self);
    m->h16 = t;
    MenuCatalogCursorUpdate_35eb10(self, 0);
}
