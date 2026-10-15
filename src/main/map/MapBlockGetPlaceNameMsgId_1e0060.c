#include "types.h"

/* Read the s16 at +0x6E. */

typedef struct Obj_FUN_001e0060 {
    u8 pad000[0x6E];
    s16 field;         /* +0x6E */
} Obj_FUN_001e0060;

s16 MapBlockGetPlaceNameMsgId_1e0060(Obj_FUN_001e0060 *o)
{
    return o->field;
}
