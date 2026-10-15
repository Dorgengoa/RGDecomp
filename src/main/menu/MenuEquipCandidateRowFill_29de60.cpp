#include "types.h"

extern "C" {
extern void UiSetItemIconSprite_288490(void *, void *, s16, s32, s32, s32);
extern void *UiFindWidget_290460(s32, s32);
extern void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
}

class VC_0 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual s32 f();
};
class VC_1 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual s32 f();
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
extern f32 D_0047D40C;
}

struct Self {
    u8 pad0[0x5C];
    u8 x5C[0xA4];
    Item *items[0xF1];
    s32 x4C4;
};

extern "C" s32 MenuEquipCandidateRowFill_29de60(Self *self, s32 arg1, s32 arg2, s32 arg3)
{
    s32 i;
    Cell *c;
    Tile *t;
    Item *it;
    s32 a;
    s32 id;
    s32 j;
    s32 k;
    s16 m;

    m = arg2;
    for (i = 0; i < 8; i++) {
        j = i + 0x10;
        id = ((arg1 & 0xFFFF) + j) & 0xFFFF;
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
        t->x = i * 0x2C + 0x1D;
        if (m == 0) {
            k = i + arg3 * 8;
            t->y = -0x16;
        } else if (m == 1) {
            k = j + (arg3 - 1) * 8;
            t->y = 0x80;
        }
        it = *(Item **)((u8 *)self + k * 4 + 0x100);
        if (it != NULL) {
            UiSetWidgetColor_2905b0(self->x4C4, id, 1.0f, 1.0f, 1.0f, 1.0f);
            if (ItemIsWeapon_3d46c0(it) != 0) {
                a = ItemFindOwnerChara_3d4d80(it, 0)->f();
                if (a < it->f()) {
                    UiSetWidgetColor_2905b0(self->x4C4, id, D_0047D40C, D_0047D40C, D_0047D40C, 1.0f);
                }
            }
            UiSetItemIconSprite_288490(self->x5C, c, (*(Info **)((u8 *)it + 0x10))->x2C, 0x28, 0x2D, 1);
        }
        UiSetWidgetsVisibleById_291110(self->x4C4, id, 1, 1);
    }
    return 1;
}
