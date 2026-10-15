#include "types.h"

/* Address of the sub-object at +0xE0. */

typedef struct Obj_FUN_00310eb0 {
    u8 pad000[0xE0];
    u8 sub[1];         /* +0xE0 */
} Obj_FUN_00310eb0;

void *NavGraphGetName_310eb0(Obj_FUN_00310eb0 *o)
{
    return o->sub;
}
