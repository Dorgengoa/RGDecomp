/* rgp:protos */
#define RGP_SELF_EvDoorObjDrawCursor_303b30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_00303b30 {
    u8 pad000[0xD0];
    u32 flags;
    u8 pad0D4[0xC];
} Obj_00303b30;

/*rgp*/

void EvDoorObjDrawCursor_303b30(Obj_00303b30 *o)
{
    s32 set;
    s32 clr;

    set = (o->flags & 0x80000000) != 0;
    clr = !set;
    if (clr != 0) {
        DoorCursorDraw_304aa0(o + 1);
    }
}
