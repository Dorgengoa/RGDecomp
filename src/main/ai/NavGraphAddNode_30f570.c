#include "types.h"

typedef struct E24 { u8 pad[0x24]; } E24;
typedef struct Vec3 { f32 x, y, z; } Vec3;

extern s32 NavFindNearestNode_310820(void *, s32, s32);
extern u32 NavGraphGetMaxNodes_310ca0(void *);
extern u32 NavGraphGetNodeCount_310cb0(void *);
extern s32 NavGraphGetNodes_310cc0(void *);
extern void NavXformPointToLocal_310d50(void *, Vec3 *, s32);
extern s32 NavGraphIsValid_311140(void);
extern f32 NavNodeDistSq_3118d0(s32, s32);
extern void NavNodeInit_3119d0(s32, u32, s32, f32, f32, f32);

u32 NavGraphAddNode_30f570(u8 *arg0, s32 arg1, f32 f)
{
    Vec3 v;
    s32 t;
    u32 n;
    u32 c;

    if (NavGraphIsValid_311140() == 0) return -1;
    if (NavGraphGetMaxNodes_310ca0(arg0) <= NavGraphGetNodeCount_310cb0(arg0)) return -1;
    if (!(f <= 0.0f)) {
        t = NavFindNearestNode_310820(arg0, arg1, 0);
        if (t != 0 && NavNodeDistSq_3118d0(t, arg1) <= f * f) return -1;
    }
    NavXformPointToLocal_310d50(arg0, &v, arg1);
    n = NavGraphGetNodeCount_310cb0(arg0);
    NavNodeInit_3119d0((s32)((E24 *)NavGraphGetNodes_310cc0(arg0) + n), n, 0, v.x, v.y, v.z);
    c = *(u16 *)(arg0 + 0xA8) + 1;
    if (*(s32 *)(arg0 + 0xA0) != 0 && c <= *(u16 *)(arg0 + 0xAA)) *(u16 *)(arg0 + 0xA8) = c;
    return n;
}
