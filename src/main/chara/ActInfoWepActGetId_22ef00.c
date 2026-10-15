#include "types.h"

/* Read the s16 at +0x2. */

typedef struct Obj_FUN_0022ef00 {
    u8 pad000[0x2];
    s16 field;         /* +0x2 */
} Obj_FUN_0022ef00;

s16 ActInfoWepActGetId_22ef00(Obj_FUN_0022ef00 *o)
{
    return o->field;
}
