#include "types.h"

/* Both arms own their store, and the SET arm is the cold block: retail
   branches away to it (bnel carrying the 1) while the clear arm falls
   through inline -- the goto places it after the tail. */

typedef struct Obj_FUN_003d5f60 {
    u8 pad000[0x2C];
    s16 m2C;
} Obj_FUN_003d5f60;

void OptionsSetEventLogEnabled_3d5f60(Obj_FUN_003d5f60 *o, s32 on)
{
    if (on != 0) {
        goto set;
    }
    o->m2C = 0;
    return;
set:
    o->m2C = 1;
}
