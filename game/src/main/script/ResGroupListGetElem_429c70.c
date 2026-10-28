/* rgp:protos */
#define RGP_SELF_ResGroupListGetElem_429c70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem29c70 {
    u8 pad00[0x40];
} Elem29c70;

typedef struct Obj29c70 {
    u8 pad00[0x4];
    Elem29c70 *list;        /* +0x04 */
    u8 pad08[0x2];
    __extension__ unsigned short flags : 2;          /* +0x0A */
    unsigned short count : 14;
} __attribute__((aligned(2))) Obj29c70;

Elem29c70 *ResGroupListGetElem_429c70(Obj29c70 *o, s32 i)
{
    Elem29c70 *p;

    if (i < 0 || i >= o->count || (p = o->list) == 0) {
        return 0;
    }
    return &p[i];
}
