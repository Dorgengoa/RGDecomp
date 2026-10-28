/* rgp:protos */
#define RGP_SELF_MenuClearPanelHandles_35b8e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0035b8e0 {
    u8 pad000[0x134];
    s32 m134;         /* +0x134 */
    s32 m138;         /* +0x138 */
    s32 m13C;         /* +0x13C */
} Obj_FUN_0035b8e0;

void MenuClearPanelHandles_35b8e0(Obj_FUN_0035b8e0 *o)
{
    o->m134 = 0;
    o->m138 = 0;
    o->m13C = 0;
}
