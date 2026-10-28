#include "types.h"

extern "C" {
extern void UiSetItemIconSprite_288490(void *, void *, s16, s32, s32, s32);
extern void *UiFindWidget_290460(s32, s32);
extern void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
}

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0xE8); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x70); }
};

struct Tile {
    s16 x;
    s16 y;
    s16 x4;
    s16 x6;
    u8 pad8[4];
    s16 xC;
    s16 xE;
};

struct Info {
    u8 pad0[0x2C];
    s16 x2C;
};

struct Item : VC_1 {
};

struct Cell {
    u8 pad0[0x20];
    Tile *tile;
};

extern "C" {
extern s32 ItemIsWeapon_3d46c0(Item *);
extern VC_0 *ItemFindOwnerChara_3d4d80(Item *, s32);
extern f32 D_0047D660;
}

struct Self {
    u8 pad0[0x5C];
    u8 x5C[0xA4];
    Item *items[0xF1];
    s32 x4C4;
};

extern "C" s32 MenuEquipCandidateGridRefresh_29e080(Self *self, s32 arg1, s32 arg2, s32 arg3)
{
    s32 i;
    Cell *c;
    Tile *t;
    s32 row;
    s32 col;
    Item *it;
    s32 a;
    s32 id;
    s32 k;

    for (i = 0; i < 0x10; i++) {
        id = ((arg1 & 0xFFFF) + i) & 0xFFFF;
        c = (Cell *)UiFindWidget_290460(self->x4C4, id);
        if (c == NULL) {
            return 0;
        }
        t = c->tile;
        if (t == NULL) {
            return 0;
        }
        t->xE = 0;
        t->xC = 0;
        t->x6 = 0;
        t->x4 = 0;
        k = i + arg3 * 8;
        if (i < arg2) {
            if (i < 8) {
                col = i;
                row = 0;
            } else {
                col = i - 8;
                row = 1;
            }
            t->x = col * 0x2C + 0x1D;
            t->y = row * 0x32 + 0x1C;
            it = *(Item **)((u8 *)self + k * 4 + 0x100);
            if (it != NULL) {
                UiSetWidgetColor_2905b0(self->x4C4, id, 1.0f, 1.0f, 1.0f, 1.0f);
                if (ItemIsWeapon_3d46c0(it) != 0) {
                    a = ItemFindOwnerChara_3d4d80(it, 0)->f();
                    if (a < it->f()) {
                        UiSetWidgetColor_2905b0(self->x4C4, id, D_0047D660, D_0047D660, D_0047D660, 1.0f);
                    }
                }
                UiSetItemIconSprite_288490(self->x5C, c, (*(Info **)((u8 *)it + 0x10))->x2C, 0x28, 0x2D, 1);
            }
            UiSetWidgetsVisibleById_291110(self->x4C4, id, 1, 1);
        }
    }
    return 1;
}
