#include "types.h"

/* Read the s16 at +0xE0. */

typedef struct Obj_FUN_002f8f40 {
    u8 pad000[0xE0];
    s16 field;         /* +0xE0 */
} Obj_FUN_002f8f40;

s16 EvObjAreaFadeIsAreaLoaded_2f8f40(Obj_FUN_002f8f40 *o)
{
    return o->field;
}
