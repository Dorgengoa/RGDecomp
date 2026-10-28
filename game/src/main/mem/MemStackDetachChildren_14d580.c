/* rgp:protos */
#define RGP_SELF_MemStackDetachChildren_14d580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node_FUN_0014d580 {
    u8 pad000[0x40];
    s32 f40;
    s32 f44;
    struct Node_FUN_0014d580 *f48;
    u8 pad04C[0x4];
} Node_FUN_0014d580;

typedef struct Obj_FUN_0014d580 {
    u8 pad000[0x4C];
    Node_FUN_0014d580 *f4C;
} Obj_FUN_0014d580;

/*rgp*/

void MemStackDetachChildren_14d580(Obj_FUN_0014d580 *o)
{
    Node_FUN_0014d580 *c;
    Node_FUN_0014d580 *n;

    MemStackResetChildren_14d170(o);
    c = o->f4C;
    o->f4C = 0;
    while (c != 0) {
        MemStackDetachChildren_14d580((Obj_FUN_0014d580 *)c);
        c->f40 = 0;
        c->f44 = 0;
        n = c->f48;
        c->f48 = 0;
        c = n;
    }
}
