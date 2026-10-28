/* rgp:protos */
#define RGP_SELF_MapAreaDefGetRecTable_1dcf20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x54. */

typedef struct Obj_FUN_001dcf20 {
    u8 pad000[0x54];
    u8 sub[1];         /* +0x54 */
} Obj_FUN_001dcf20;

void *MapAreaDefGetRecTable_1dcf20(Obj_FUN_001dcf20 *o)
{
    return o->sub;
}
