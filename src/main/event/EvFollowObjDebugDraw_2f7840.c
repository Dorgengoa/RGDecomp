#include "types.h"
#pragma opt_propagation off

typedef struct O { u8 pad[0x10]; u8 x10[0xC0]; s32 xD0; u8 padD4[0x40]; s32 x114; } O;
extern void DbgDrawSphere_1cc7e0(s32, void *, f32 *, f32);
extern void EventVolumeRecDebugDraw_2e49b0(s32, s32, void *, f32 *);
extern void XformGetMatrix_2e7750(void *, void *);
extern f32 D_0047F060;
extern f32 D_0047F064;
extern f32 D_0047F068;
extern f32 D_0047F06C;
static inline s32 isNF(O *o) { return !((o->xD0 & 0x40000000) != 0); }
static inline s32 isF(O *o) { return (o->xD0 & 0x40000000) != 0; }
void EvFollowObjDebugDraw_2f7840(O *arg0, s32 arg1)
{
    u8 sp70[0x10];
    u8 sp40[0x30];
    f32 v[4];
    s32 t;
    s32 b;
    f32 *p;

    if (arg1 == 0) {
        return;
    }
    if (!isNF(arg0)) {
        return;
    }
    XformGetMatrix_2e7750(arg0->x10, sp40);
    p = v;
    p[0] = D_0047F060;
    p[1] = D_0047F064;
    p[2] = D_0047F068;
    p[3] = D_0047F06C;
    DbgDrawSphere_1cc7e0(arg1, sp70, p, 40.0f);
    t = arg0->x114;
    if (t != 0) {
        EventVolumeRecDebugDraw_2e49b0(t, arg1, sp40, v);
    }
}
