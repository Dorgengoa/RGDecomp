#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_001e7850 {
    s32 field;         /* +0x00 */
} Obj_FUN_001e7850;

s32 MapDataGetHeap_1e7850(Obj_FUN_001e7850 *o)
{
    return o->field;
}
