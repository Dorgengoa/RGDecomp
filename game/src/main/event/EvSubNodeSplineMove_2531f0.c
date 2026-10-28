/* rgp:protos */
#define RGP_SELF_EvSubNodeSplineMove_2531f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V4;
typedef struct { f32 lo[4]; f32 hi[4]; } Box;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvSubNodeSplineMove_2531f0(u8 *arg0, u8 *arg1) {
    V4 v __attribute__((aligned(16)));
    Box box __attribute__((aligned(16)));
    u8 buf[0x3000] __attribute__((aligned(16)));
    V4 a __attribute__((aligned(16)));
    V4 b __attribute__((aligned(16)));
    V4 c __attribute__((aligned(16)));
    s32 i;
    s32 n;

    if (*(s32 *)(arg1 + 0x40) <= 0) {
        SplinePathBuild_256ac0(arg1 + 0x140);
        SplinePathStart_256aa0(arg1 + 0x140);
        *(s32 *)(arg1 + 0x40) = 1;
    }
    sceVu0CopyVector(&v, arg1 + 0x70);
    SplinePathStep_256970(arg1 + 0x140, arg1 + 0x70, arg1 + 0x84);
    if (*(s32 *)(arg0 + 0x20) == 1) {
        for (i = 0; i < 3; i++) {
            box.lo[i] = 10.0f + *(f32 *)(arg1 + i * 4 + 0x70);
            box.hi[i] = *(f32 *)(arg1 + i * 4 + 0x70) - 10.0f;
        }
        n = SceneMapAreasCollectCollTrisMaybe_1c5090(((s32)GetStaticScene_1c6c70()), buf, &box, 0x80);
        sceVu0CopyVector(&a, arg1 + 0x70);
        a.y = a.y + 10.0f;
        a.w = 1.0f;
        sceVu0CopyVector(&b, arg1 + 0x70);
        b.y = b.y + 10.0f;
        b.w = 1.0f;
        if (MeshRaycastWrapper_16f610(buf, n, &a, &b, &c, 1, 0) >= 0) {
            *(f32 *)(arg1 + 0x74) = c.y;
        }
    }
    if (SplinePathIsDone_256950(arg1 + 0x140) != 0) {
        *(s32 *)(arg1 + 0x40) = 0;
        return 0;
    }
    return 1;
}
