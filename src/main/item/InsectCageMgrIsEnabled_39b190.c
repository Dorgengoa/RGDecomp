#include "types.h"

/* Read the u8 at +0xA2. */

typedef struct Obj_FUN_0039b190 {
    u8 pad000[0xA2];
    u8 field;         /* +0xA2 */
} Obj_FUN_0039b190;

u8 InsectCageMgrIsEnabled_39b190(Obj_FUN_0039b190 *o)
{
    return o->field;
}
