#include "types.h"

struct Elem {
    u8 pad000[0x170];
};

struct Obj {
    u8 pad000[0x204];
    s32 count;
    struct Elem *items;
};

extern void DynClothClearWind_169400(struct Elem *e);

void ModelObjClothClearWindAll_1ad2b0(struct Obj *o)
{
    s32 i;

    for (i = 0; i < o->count; i++) {
        DynClothClearWind_169400(&o->items[i]);
    }
}
