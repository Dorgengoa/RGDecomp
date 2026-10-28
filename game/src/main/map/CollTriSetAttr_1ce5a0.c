/* rgp:protos */
#define RGP_SELF_CollTriSetAttr_1ce5a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x4A. */

typedef struct Obj_FUN_001ce5a0 {
    u8 pad000[0x4A];
    s16 field;         /* +0x4A */
} Obj_FUN_001ce5a0;

void CollTriSetAttr_1ce5a0(Obj_FUN_001ce5a0 *o, s16 value)
{
    o->field = value;
}
