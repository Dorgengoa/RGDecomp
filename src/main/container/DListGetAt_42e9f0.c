#include "types.h"

typedef struct Obj0042e9f0 {
    struct Obj0042e9f0 *unk0;
    struct Obj0042e9f0 *unk4;
    u16 unk8;
} Obj0042e9f0;
typedef Obj0042e9f0 O;
O *DListGetAt_42e9f0(O *self, u32 count)
{
    O *node; O *p;
    node = self->unk0;
    if (node == NULL) return NULL;
    if (count >= self->unk8) return NULL;
    p = node;
    while (((p != NULL) ^ 1) == 0 && (s32)count > 0) { p = p->unk4; count -= 1; }
    return p;
}
