/* rgp:protos */
#define RGP_SELF_MenuItemGetOpenModeMaybe_2a4ec0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the u8 at +0x44. */

typedef struct Obj_FUN_002a4ec0 {
    u8 pad000[0x44];
    u8 field;         /* +0x44 */
} Obj_FUN_002a4ec0;

u8 MenuItemGetOpenModeMaybe_2a4ec0(Obj_FUN_002a4ec0 *o)
{
    return o->field;
}
