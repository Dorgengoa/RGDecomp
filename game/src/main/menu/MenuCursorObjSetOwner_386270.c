/* rgp:protos */
#define RGP_SELF_MenuCursorObjSetOwner_386270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x0. */

typedef struct Obj_FUN_00386270 {
    s32 field;         /* +0x00 */
} Obj_FUN_00386270;

void MenuCursorObjSetOwner_386270(Obj_FUN_00386270 *o, s32 value)
{
    o->field = value;
}
