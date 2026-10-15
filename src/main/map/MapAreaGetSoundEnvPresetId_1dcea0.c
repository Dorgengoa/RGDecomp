#include "types.h"

/* Read the s16 at +0x8A. */

typedef struct Obj_FUN_001dcea0 {
    u8 pad000[0x8A];
    s16 field;         /* +0x8A */
} Obj_FUN_001dcea0;

s16 MapAreaGetSoundEnvPresetId_1dcea0(Obj_FUN_001dcea0 *o)
{
    return o->field;
}
