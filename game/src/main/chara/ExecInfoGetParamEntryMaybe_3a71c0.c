/* rgp:protos */
#define RGP_SELF_ExecInfoGetParamEntryMaybe_3a71c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x50. */

typedef struct Obj_FUN_003a71c0 {
    u8 pad000[0x50];
    s32 field;         /* +0x50 */
} Obj_FUN_003a71c0;

s32 ExecInfoGetParamEntryMaybe_3a71c0(Obj_FUN_003a71c0 *o)
{
    return o->field;
}
