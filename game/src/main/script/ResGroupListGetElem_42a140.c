/* rgp:protos */
#define RGP_SELF_ResGroupListGetElem_42a140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem2a140 {
    u8 pad00[0x20];
} Elem2a140;

typedef struct Obj2a140 {
    u8 pad00[0x4];
    Elem2a140 *list;        /* +0x04 */
    u8 pad08[0x2];
    __extension__ unsigned short flags : 2;          /* +0x0A */
    unsigned short count : 14;
} __attribute__((aligned(2))) Obj2a140;

Elem2a140 *ResGroupListGetElem_42a140(Obj2a140 *o, s32 i)
{
    Elem2a140 *p;

    if (i < 0 || i >= o->count || (p = o->list) == 0) {
        return 0;
    }
    return &p[i];
}
