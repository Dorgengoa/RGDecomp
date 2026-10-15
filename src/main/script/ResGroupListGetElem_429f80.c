#include "types.h"

typedef struct Elem29f80 {
    u8 pad00[0x10];
} Elem29f80;

typedef struct Obj29f80 {
    u8 pad00[0x4];
    Elem29f80 *list;        /* +0x04 */
    u8 pad08[0x2];
    u16 flags : 2;          /* +0x0A */
    u16 count : 14;
} Obj29f80;

Elem29f80 *ResGroupListGetElem_429f80(Obj29f80 *o, s32 i)
{
    Elem29f80 *p;

    if (i < 0 || i >= o->count || (p = o->list) == 0) {
        return 0;
    }
    return &p[i];
}
