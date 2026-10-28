/* rgp:protos */
#define RGP_SELF_MapAreaGetShuffleCount_1dcdc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0xE6. */

typedef struct Obj_FUN_001dcdc0 {
    u8 pad000[0xE6];
    s16 field;         /* +0xE6 */
} Obj_FUN_001dcdc0;

s16 MapAreaGetShuffleCount_1dcdc0(Obj_FUN_001dcdc0 *o)
{
    return o->field;
}
