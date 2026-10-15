#include "types.h"

typedef struct Slot {
    s32 a;
    s32 b;
    s32 c;
} Slot;

typedef struct Obj {
    u8 pad[0x1390];
    Slot slots[2];
} Obj;

static inline Slot *findFree(Obj *o)
{
    s32 i;
    for (i = 0; i < 2; i++) {
        if (o->slots[i].a == 0) {
            return &o->slots[i];
        }
    }
    return NULL;
}

void MenuObjBattlePairAssign_385c70(Obj *arg0, s32 arg1, s32 arg2)
{
    Slot *s;

    if (arg1 == 0 || arg2 == 0) {
        return;
    }
    s = findFree(arg0);
    if (s != NULL) {
        s->a = arg1;
        s->b = arg2;
    }
}
