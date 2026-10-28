/* rgp:protos */
#define RGP_SELF_ResGroupListGetElem_429de0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem29de0 {
    u8 pad00[0x20];
} Elem29de0;

typedef struct Obj29de0 {
    u8 pad00[0x4];
    Elem29de0 *list;        /* +0x04 */
    u8 pad08[0x2];
    __extension__ unsigned short flags : 2;          /* +0x0A */
    unsigned short count : 14;
} __attribute__((aligned(2))) Obj29de0;

Elem29de0 *ResGroupListGetElem_429de0(Obj29de0 *o, s32 i)
{
    Elem29de0 *p;

    if (i < 0 || i >= o->count || (p = o->list) == 0) {
        return 0;
    }
    return &p[i];
}
