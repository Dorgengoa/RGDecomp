/* rgp:protos */
#define RGP_SELF_MenuItemSetOpenModeMaybe_2a4ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the u8 at +0x44. */

typedef struct Obj_FUN_002a4ed0 {
    u8 pad000[0x44];
    u8 field;         /* +0x44 */
} Obj_FUN_002a4ed0;

void MenuItemSetOpenModeMaybe_2a4ed0(Obj_FUN_002a4ed0 *o, u8 value)
{
    o->field = value;
}
