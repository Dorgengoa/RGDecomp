#include "types.h"

/* MAIN EvTargetPointObjDebugDraw_2f91b0 -- same stack shape as EvFollowObjDebugDraw_2f7840. */

typedef struct V4 { f32 x, y, z, w; } V4;
typedef struct Mtx { f32 m[12]; } Mtx;

extern s32 TargetRefGetMatrix_2e6870(u8 *, Mtx *);
extern f32 TargetRefGetRadius_2e7100(u8 *);
extern void DbgDrawSphere_1cc7e0(void *, V4 *, V4 *, f32);
extern void DrawWireCube_1cc1b0(void *, Mtx *, V4 *);
extern f32 D_0047F020;
extern f32 D_0047F024;
extern f32 D_0047F028;
extern f32 D_0047F02C;

void EvTargetPointObjDebugDraw_2f91b0(u8 *p, void *q)
{
    V4 scratch;
    Mtx m;
    V4 v;

    if (q != 0) {
        if ((*(s32 *)(p + 0xD0) & 0x2000000) != 0) {
            TargetRefGetMatrix_2e6870(p + 0xA0, &m);
            v.x = D_0047F020;
            v.y = D_0047F024;
            v.z = D_0047F028;
            v.w = D_0047F02C;
            DbgDrawSphere_1cc7e0(q, &scratch, &v, TargetRefGetRadius_2e7100(p + 0xA0));
            DrawWireCube_1cc1b0(q, &m, &v);
        }
    }
}
