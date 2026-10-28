/* rgp:protos */
#define RGP_SELF_InsectCageMgrSetHeap_39b1a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x90. */

typedef struct Obj_FUN_0039b1a0 {
    u8 pad000[0x90];
    s32 field;         /* +0x90 */
} Obj_FUN_0039b1a0;

void InsectCageMgrSetHeap_39b1a0(Obj_FUN_0039b1a0 *o, s32 value)
{
    o->field = value;
}
