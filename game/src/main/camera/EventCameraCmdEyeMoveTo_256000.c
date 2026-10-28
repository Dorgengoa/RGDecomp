/* rgp:protos */
#define RGP_SELF_EventCameraCmdEyeMoveTo_256000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/ /* dst = a - b */
/*rgp*/ /* dst = a + b */
/*rgp*/

struct Obj0 {
    u8 pad000[0x10];
    f32 m10[4];
    f32 m20[4];
    s32 m30;
};

struct Obj1 {
    u8 pad000[0x38];
    s32 m38;
    u8 pad03C[0x14];
    f32 m50[4];
    f32 m60[4];
    u8 pad070[0x60];
    f32 mD0[4];
    f32 mE0[4];
};

/* Guard reads p0->m30 first; the fall-through arm is the "expired" one. */
s32 EventCameraCmdEyeMoveTo_256000(struct Obj0 *p0, struct Obj1 *p1)
{
    f32 v30[4] __attribute__((aligned(16)));

    if (p1->m38 >= p0->m30) {
        sceVu0CopyVector(p1->m50, p0->m10);
        p1->m38 = 0;
        return 0;
    }
    if (p1->m38 <= 0) {
        VecSub_13be40(v30, p0->m10, p1->m50);
        sceVu0DivVector(p1->mD0, v30, (f32)p0->m30);
        p1->mD0[3] = 1.0f;
    } else {
        VecAdd_13be20(p1->m50, p1->m50, p1->mD0);
        p1->m50[3] = 1.0f;
    }
    p1->m38 = p1->m38 + 1;
    return 1;
}
