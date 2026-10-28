/* rgp:protos */
#define RGP_SELF_TextStyleHasClipRect_26f5f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x20. */

typedef struct Obj_FUN_0026f5f0 {
    u8 pad000[0x20];
    s16 field;         /* +0x20 */
} Obj_FUN_0026f5f0;

s16 TextStyleHasClipRect_26f5f0(Obj_FUN_0026f5f0 *o)
{
    return o->field;
}
