#include "types.h"
/* stack-block coverage guard (CameraBaseLookAt_15fae0 shape): retail's side / up / dir
   rows are one block read by MatRows_400b30(&side), but `up` is written inline, never
   passed to a call, so no C local maps to its slot: the rule must not build the block */
typedef struct { f32 x, y, z, w; } V4;
extern void PutPoint_400b00(V4 *p, s32 v);
extern void MatRows_400b30(V4 *m);

s32 HoleBlock_400a80(s32 v)
{
    V4 side;
    V4 up;
    V4 dir;

    PutPoint_400b00(&side, v);
    PutPoint_400b00(&dir, v);
    up.x = 1.0f;
    MatRows_400b30(&side);
    return 0;
}
