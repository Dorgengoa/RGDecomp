#include "types.h"

extern void sceVu0CopyVector(void *, const void *);
extern void VecSub_13be40(f32 *, const f32 *, const f32 *); /* dst = a - b */
extern void VecNormalize_13bd90(f32 *, const f32 *);              /* normalise    */
extern f32 Atan2f_1291a8(f32, f32);                         /* atan2        */
extern f32 VecDistance_13d3d0(const f32 *, const f32 *);

struct Obj0 {
    u8 pad000[0x10];
    f32 m10[4];
    f32 m20[4];
};

struct Obj1 {
    u8 pad000[0x50];
    f32 m50[4];
    f32 m60[4];
    f32 m70;
    f32 m74;
    f32 m78;
};

/* Stack locals are allocated in REVERSE declaration order, so v50 (0x50)
   is declared first and v20 (0x20) last. */
s32 EventCameraCmdSetAt_256790(struct Obj0 *p0, struct Obj1 *p1)
{
    f32 v50[4];
    f32 v40[4];
    f32 v30[4];
    f32 v20[4];

    sceVu0CopyVector(p1->m60, p0->m20);
    VecSub_13be40(v50, p1->m60, p1->m50);
    v40[0] = v50[0];
    v40[1] = 0.0f;
    v40[2] = v50[2];
    v40[3] = 0.0f;
    VecNormalize_13bd90(v40, v40);
    p1->m70 = Atan2f_1291a8(-v40[0], -v40[2]);
    p1->m74 = p1->m50[1] - p1->m60[1];
    sceVu0CopyVector(v30, p1->m50);
    v30[1] = 0.0f;
    sceVu0CopyVector(v20, p1->m60);
    v20[1] = 0.0f;
    p1->m78 = VecDistance_13d3d0(v30, v20);
    return 0;
}
