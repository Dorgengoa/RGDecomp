/* rgp:protos */
#define RGP_SELF_MenuCursorObjSetVisible_386280 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x8. */

typedef struct Obj_FUN_00386280 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_00386280;

void MenuCursorObjSetVisible_386280(Obj_FUN_00386280 *o, s32 value)
{
    o->field = value;
}
