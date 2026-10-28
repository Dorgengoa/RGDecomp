/* rgp:protos */
#define RGP_SELF_EntryListGetHeap_3237d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_003237d0 {
    s32 field;         /* +0x00 */
} Obj_FUN_003237d0;

s32 EntryListGetHeap_3237d0(Obj_FUN_003237d0 *o)
{
    return o->field;
}
