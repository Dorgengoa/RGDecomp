/* rgp:protos */
#define RGP_SELF_ModelResGetMeshCount_14c5c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Null-checked pointer chase: the likely beql carries the 0 result in its
   own delay slot. */

typedef struct Sub_FUN_0014c5c0 {
    u8 pad000[0x20];
    s32 m20;
} Sub_FUN_0014c5c0;

typedef struct Obj_FUN_0014c5c0 {
    Sub_FUN_0014c5c0 *p;
} Obj_FUN_0014c5c0;

s32 ModelResGetMeshCount_14c5c0(Obj_FUN_0014c5c0 *o)
{
    Sub_FUN_0014c5c0 *p;

    p = o->p;
    if (p != 0) {
        return p->m20;
    }
    return 0;
}
