#include "types.h"

/* Read the s32 at +0x10. */

typedef struct Obj_FUN_002e4d80 {
    u8 pad000[0x10];
    s32 field;         /* +0x10 */
} Obj_FUN_002e4d80;

s32 EventVolumeRecGetVolumes_2e4d80(Obj_FUN_002e4d80 *o)
{
    return o->field;
}
