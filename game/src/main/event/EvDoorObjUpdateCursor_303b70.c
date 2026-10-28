/* rgp:protos */
#define RGP_SELF_EvDoorObjUpdateCursor_303b70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_00303b70 {
    u8 pad000[0xD0];
    u32 flags;
    u8 pad0D4[0xC];
} Obj_00303b70;

/*rgp*/

void EvDoorObjUpdateCursor_303b70(Obj_00303b70 *o)
{
    s32 set;
    s32 clr;

    set = (o->flags & 0x80000000) != 0;
    clr = !set;
    if (clr != 0) {
        DoorCursorFadePulseUpdate_305120(o + 1);
    }
}
