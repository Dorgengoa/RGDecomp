#include "types.h"

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x274];
    s32 m274;
    s32 m278;
    u8 pad27C[0x8];
    s32 m284;
};

struct Obj1 {
    u8 pad000[0xA];
    s16 m0A;
    u8 pad00C[0xA];
    s16 m16;
};

extern struct Obj1 * UiEntryListFindByTag_28ea40(s32, s32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);

void MenuCatalogPlaceRowCursor_360350(struct Obj0 *p0)
{
    struct Obj1 *r0;
    s32 n;

    r0 = UiEntryListFindByTag_28ea40(p0->m278, 0x24);
    n = r0->m16 * r0->m0A + 0x21;
    if (p0->m284 == 1) {
        UiSetWidgetPos_290f60(p0->m274, 0x1F4, 0x1F, n);
    }
    if (p0->m284 == 2) {
        UiSetWidgetPos_290f60(p0->m274, 0x1F5, 0x1F, n);
    }
}
