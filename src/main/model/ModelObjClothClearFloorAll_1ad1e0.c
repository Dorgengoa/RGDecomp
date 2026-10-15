#include "types.h"

struct Elem {
    u8 pad000[0x170];
};

struct Obj {
    u8 pad000[0x204];
    s32 count;
    struct Elem *items;
};

extern void DynClothClearFloor_1693e0(struct Elem *e);

void ModelObjClothClearFloorAll_1ad1e0(struct Obj *o)
{
    s32 i;

    for (i = 0; i < o->count; i++) {
        DynClothClearFloor_1693e0(&o->items[i]);
    }
}
