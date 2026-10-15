#include "types.h"

typedef struct Obj_00303b70 {
    u8 pad000[0xD0];
    u32 flags;
    u8 pad0D4[0xC];
} Obj_00303b70;

extern void DoorCursorFadePulseUpdate_305120(void *p);

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
