/* rgp:protos */
#define RGP_SELF_MenuFadeSetColor_29ff90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0029ff90 {
    u8 pad000[0x50];
    u8 m50;         /* +0x50 */
    u8 m51;         /* +0x51 */
    u8 m52;         /* +0x52 */
} Obj_FUN_0029ff90;

void MenuFadeSetColor_29ff90(Obj_FUN_0029ff90 *o, u8 p0, u8 p1, u8 p2)
{
    o->m50 = p0;
    o->m51 = p1;
    o->m52 = p2;
}
