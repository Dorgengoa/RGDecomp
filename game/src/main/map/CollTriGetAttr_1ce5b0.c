/* rgp:protos */
#define RGP_SELF_CollTriGetAttr_1ce5b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the u16 at +0x4A. */

typedef struct Obj_FUN_001ce5b0 {
    u8 pad000[0x4A];
    u16 field;         /* +0x4A */
} Obj_FUN_001ce5b0;

u16 CollTriGetAttr_1ce5b0(Obj_FUN_001ce5b0 *o)
{
    return o->field;
}
