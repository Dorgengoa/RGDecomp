/* rgp:protos */
#define RGP_SELF_EffDefCmdEffFrameHierarchy_19b7e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Event-script command handler: argument block $4, argument COUNT $5, VM
   context $6 (the object is ctx[0]).  Same POST-INCREMENT lever as
   EffDefCmdAnimeData_19c250: `f720(args++)` is what emits `addiu $19,$19,0x8` in the
   first call's delay slot.  Five-argument tail call -- $8 is the fifth
   integer argument under the PS2 EABI. */
/*rgp*/
/*rgp*/
typedef struct Arg { s32 a; s32 b; } Arg;
s32 EffDefCmdEffFrameHierarchy_19b7e0(Arg *args, s32 n, void **ctx)
{
    u8 *o = (u8 *)ctx[0];
    void *a;
    void *b;
    a = SlotGetInt_15f720(args++);
    if (a == 0) {
        return 0;
    }
    b = 0;
    if (n >= 2) {
        b = SlotGetInt_15f720(args);
    }
    SceneTreeInsertNamed_19ade0(*(void **)(o + 0x24), *(void **)(o + 0x20), a, 0, b);
    return 1;
}
