/* rgp:protos */
#define RGP_SELF_MapAreaModelObjsClearOwner_188f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent_FUN_00188f60 {
    u8 pad000[0x34];
    s32 f34;
    s32 f38;
} Ent_FUN_00188f60;

typedef struct Obj_FUN_00188f60 {
    u8 pad000[0x504];
    s32 f504;
    Ent_FUN_00188f60 **f508;
} Obj_FUN_00188f60;

void MapAreaModelObjsClearOwner_188f60(Obj_FUN_00188f60 *o)
{
    s32 i;
    s32 n;
    Ent_FUN_00188f60 **arr;
    Ent_FUN_00188f60 *e;

    n = o->f504;
    arr = o->f508;
    for (i = 0; i < n; i++) {
        e = arr[i];
        if (e != 0) {
            e->f34 = 0;
            e->f38 = 0;
        }
    }
}
