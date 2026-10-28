/* rgp:protos */
#define RGP_SELF_MenuCatalogPageClearHandles_360e40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00360e40 {
    u8 pad000[0x250];
    s32 m250;         /* +0x250 */
    u8 pad254[0x20];
    s32 m274;         /* +0x274 */
    s32 m278;         /* +0x278 */
    s32 m27C;         /* +0x27C */
} Obj_FUN_00360e40;

void MenuCatalogPageClearHandles_360e40(Obj_FUN_00360e40 *o)
{
    o->m274 = 0;
    o->m278 = 0;
    o->m27C = 0;
    o->m250 = 0;
}
