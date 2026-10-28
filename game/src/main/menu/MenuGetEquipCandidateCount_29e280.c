/* rgp:protos */
#define RGP_SELF_MenuGetEquipCandidateCount_29e280 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0xFC. */

typedef struct Obj_FUN_0029e280 {
    u8 pad000[0xFC];
    s16 field;         /* +0xFC */
} Obj_FUN_0029e280;

s16 MenuGetEquipCandidateCount_29e280(Obj_FUN_0029e280 *o)
{
    return o->field;
}
