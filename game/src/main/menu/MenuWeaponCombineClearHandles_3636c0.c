/* rgp:protos */
#define RGP_SELF_MenuWeaponCombineClearHandles_3636c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_003636c0 {
    u8 pad000[0x83];
    u8 m83;         /* +0x83 */
    s32 m84;         /* +0x84 */
    s32 m88;         /* +0x88 */
    s32 m8C;         /* +0x8C */
} Obj_FUN_003636c0;

void MenuWeaponCombineClearHandles_3636c0(Obj_FUN_003636c0 *o)
{
    o->m84 = 0;
    o->m88 = 0;
    o->m8C = 0;
    o->m83 = 0;
}
