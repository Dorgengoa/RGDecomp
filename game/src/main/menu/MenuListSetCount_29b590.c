/* rgp:protos */
#define RGP_SELF_MenuListSetCount_29b590 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0xF8. */

typedef struct Obj_FUN_0029b590 {
    u8 pad000[0xF8];
    s16 field;         /* +0xF8 */
} Obj_FUN_0029b590;

void MenuListSetCount_29b590(Obj_FUN_0029b590 *o, s16 value)
{
    o->field = value;
}
