/* rgp:protos */
#define RGP_SELF_S16ArrayGetCount_1ce1b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x6. */

typedef struct Obj_FUN_001ce1b0 {
    u8 pad000[0x6];
    s16 field;         /* +0x6 */
} Obj_FUN_001ce1b0;

s16 S16ArrayGetCount_1ce1b0(Obj_FUN_001ce1b0 *o)
{
    return o->field;
}
