#include "types.h"

typedef struct { f32 x, y, z, w; } V4;
typedef struct { f32 lo[4]; f32 hi[4]; } Box;

s32 MeshRaycastWrapper_16f610(u8 *, s32, V4 *, V4 *, V4 *, s32, s32);
s32 SceneMapAreasCollectCollTrisMaybe_1c5090(s32, u8 *, Box *, s32);
s32 GetStaticScene_1c6c70(void);
s32 SplinePathIsDone_256950(u8 *);
void SplinePathStep_256970(u8 *, u8 *, u8 *);
void SplinePathStart_256aa0(u8 *);
void SplinePathBuild_256ac0(u8 *);
void sceVu0CopyVector(V4 *, u8 *);

s32 EvSubNodeSplineMove_2531f0(u8 *arg0, u8 *arg1) {
    V4 v;
    Box box;
    u8 buf[0x3000];
    V4 a;
    V4 b;
    V4 c;
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
        n = SceneMapAreasCollectCollTrisMaybe_1c5090(GetStaticScene_1c6c70(), buf, &box, 0x80);
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
