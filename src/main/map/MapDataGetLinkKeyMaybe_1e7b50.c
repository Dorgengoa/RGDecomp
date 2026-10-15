#include "types.h"

/* Read the s16 at +0x26. */

typedef struct Obj_FUN_001e7b50 {
    u8 pad000[0x26];
    s16 field;         /* +0x26 */
} Obj_FUN_001e7b50;

s16 MapDataGetLinkKeyMaybe_1e7b50(Obj_FUN_001e7b50 *o)
{
    return o->field;
}
