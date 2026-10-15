#include "types.h"

/* Address of the sub-object at +0xAAC. */

typedef struct Obj_FUN_00213810 {
    u8 pad000[0xAAC];
    u8 sub[1];         /* +0xAAC */
} Obj_FUN_00213810;

void *CharaGetAbltName_213810(Obj_FUN_00213810 *o)
{
    return o->sub;
}
