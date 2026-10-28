/* rgp:protos */
#define RGP_SELF_GameDataStatusClearAllPartial_3e6760 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Two optional teardowns and a constant 1. Each field is loaded straight into
   $4, so the guard tests the argument register itself; retail reloads +0x1C
   in the first guard's `beql` delay slot, which is what puts the second load
   before the branch on both paths. */

typedef struct Obj003e6760 {
    u8 pad00[0x14];
    void *unk14;
    u8 pad18[0x4];
    void *unk1C;
} Obj003e6760;

/*rgp*/
/*rgp*/

s32 GameDataStatusClearAllPartial_3e6760(Obj003e6760 *self)
{
    if (self->unk14 != 0) {
        CharaMgrPoolStatusClearAllPartial_3a8690(self->unk14);
    }
    if (self->unk1C != 0) {
        ObjMgrStatusClearAllPartial_3ba810(self->unk1C);
    }
    return 1;
}
