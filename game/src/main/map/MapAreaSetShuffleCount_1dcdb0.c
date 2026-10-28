/* rgp:protos */
#define RGP_SELF_MapAreaSetShuffleCount_1dcdb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0xE6. */

typedef struct Obj_FUN_001dcdb0 {
    u8 pad000[0xE6];
    s16 field;         /* +0xE6 */
} Obj_FUN_001dcdb0;

void MapAreaSetShuffleCount_1dcdb0(Obj_FUN_001dcdb0 *o, s16 value)
{
    o->field = value;
}
