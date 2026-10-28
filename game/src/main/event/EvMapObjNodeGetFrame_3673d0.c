/* rgp:protos */
#define RGP_SELF_EvMapObjNodeGetFrame_3673d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x144. */

typedef struct Obj_FUN_003673d0 {
    u8 pad000[0x144];
    s32 field;         /* +0x144 */
} Obj_FUN_003673d0;

s32 EvMapObjNodeGetFrame_3673d0(Obj_FUN_003673d0 *o)
{
    return o->field;
}
