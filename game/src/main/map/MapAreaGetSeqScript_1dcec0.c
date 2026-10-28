/* rgp:protos */
#define RGP_SELF_MapAreaGetSeqScript_1dcec0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0xF0. */

typedef struct Obj_FUN_001dcec0 {
    u8 pad000[0xF0];
    s32 field;         /* +0xF0 */
} Obj_FUN_001dcec0;

s32 MapAreaGetSeqScript_1dcec0(Obj_FUN_001dcec0 *o)
{
    return o->field;
}
