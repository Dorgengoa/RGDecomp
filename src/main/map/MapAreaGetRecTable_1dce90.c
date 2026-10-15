#include "types.h"

/* Address of the sub-object at +0x54. */

typedef struct Obj_FUN_001dce90 {
    u8 pad000[0x54];
    u8 sub[1];         /* +0x54 */
} Obj_FUN_001dce90;

void *MapAreaGetRecTable_1dce90(Obj_FUN_001dce90 *o)
{
    return o->sub;
}
