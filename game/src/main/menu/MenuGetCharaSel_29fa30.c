/* rgp:protos */
#define RGP_SELF_MenuGetCharaSel_29fa30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x68. */

typedef struct Obj_FUN_0029fa30 {
    u8 pad000[0x68];
    s32 field;         /* +0x68 */
} Obj_FUN_0029fa30;

s32 MenuGetCharaSel_29fa30(Obj_FUN_0029fa30 *o)
{
    return o->field;
}
