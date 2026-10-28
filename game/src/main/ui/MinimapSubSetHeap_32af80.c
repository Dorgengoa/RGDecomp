/* rgp:protos */
#define RGP_SELF_MinimapSubSetHeap_32af80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x4. */

typedef struct Obj_FUN_0032af80 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_0032af80;

void MinimapSubSetHeap_32af80(Obj_FUN_0032af80 *o, s32 value)
{
    o->field = value;
}
