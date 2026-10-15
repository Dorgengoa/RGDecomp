#include "types.h"

/* Three identical clone-a-slot blocks.  The 4 lwc1 then 4 swc1 (batched) is
   ONE struct assignment of a 4-float, 4-byte-aligned struct -- not lq/sq, so
   the type is NOT the 16-byte aligned Vec4.  The first call leaves $5 alone
   because the incoming p1 is still live in it. */

typedef struct F4 { f32 x, y, z, w; } F4;

struct Obj {
    u8 pad000[0x14];
    F4 *m14;  /* 0x14 */
    F4 *m18;  /* 0x18 */
    F4 *m1C;  /* 0x1C */
};

extern void *MemStackNew_14e230(s32 size, void *ctx);

s32 FrameDupXformSlots_14a5f0(struct Obj *p0, void *p1)
{
    s32 ok;
    F4 *t0;

    ok = 1;
    if (p0->m14 != 0) {
        t0 = (F4 *)MemStackNew_14e230(0x10, p1);
        if (t0 != 0) {
            *t0 = *p0->m14;
            p0->m14 = t0;
        } else {
            ok = 0;
        }
    }
    if (p0->m18 != 0) {
        t0 = (F4 *)MemStackNew_14e230(0x10, p1);
        if (t0 != 0) {
            *t0 = *p0->m18;
            p0->m18 = t0;
        } else {
            ok = 0;
        }
    }
    if (p0->m1C != 0) {
        t0 = (F4 *)MemStackNew_14e230(0x10, p1);
        if (t0 != 0) {
            *t0 = *p0->m1C;
            p0->m1C = t0;
        } else {
            ok = 0;
        }
    }
    return ok;
}
