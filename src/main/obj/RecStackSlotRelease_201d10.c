#include "types.h"

/* Known-positive sibling shape of RecStackHeapSlotRelease_201ea0 (byte-identical, in cunits). */

extern s32 GetCurrentScene_1f5be0(void);
extern void RecStackPop_1c4140(s32, s32);
extern void MemStackReset_14d830(s32);

struct Obj0;

struct Obj0 {
    s32 m00;
};

void RecStackSlotRelease_201d10(s32 p0, struct Obj0 *p1)
{
    s32 t0;
    s32 r0;
    s32 t1;

    if (p1 != 0) {
        t0 = p1->m00;
        if (t0 >= 0) {
            r0 = GetCurrentScene_1f5be0();
            t1 = p1->m00;
            RecStackPop_1c4140(r0, t1);
        }
        p1->m00 = -1;
    }
    if (p0 != 0) {
        MemStackReset_14d830(p0);
        return;
    }
}
