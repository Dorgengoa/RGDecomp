#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_002e5720 {
    s32 field;         /* +0x00 */
} Obj_FUN_002e5720;

s32 EventRecGetHeapBuf_2e5720(Obj_FUN_002e5720 *o)
{
    return o->field;
}
