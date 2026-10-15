#include "types.h"

/* Is the s16 at +0x17C6 non-zero? */

typedef struct Obj_FUN_001e6340 {
    u8 pad000[0x17C6];
    s16 field;         /* +0x17C6 */
} Obj_FUN_001e6340;

u8 MapSkyIsLoaded_1e6340(Obj_FUN_001e6340 *o)
{
    u8 set;

    set = o->field != 0;
    return set;
}
