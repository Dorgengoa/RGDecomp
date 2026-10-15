#include "vec.h"

typedef struct Cmd { s32 a, b; } Cmd;

extern f32 TaggedGetFloat_26a280(s32);
extern s32 ScriptGetInt_26a2a0(s32);
extern s32 ScriptGetCodeAddr_26a200(s32);
/* setup order i1,i2,i3,f1,i4,f2,i5,f3 */
extern void EventCameraNodeAddOrbitCastSet_253b10(s32, s32, Vec4 *, f32, s32, f32, s32, f32);
extern s32 D_00482060;

/* two guards, both `>=`: retail FALLS THROUGH the bnez/bnel into the fetch,
   so the fetch is the if body.  $17 (u) is zeroed before $16 (w), which is
   the source declaration order. */
s32 EvCmdCameraOrbitCastSet_2641b0(Cmd *p0, s32 n)
{
    Vec4 v;
    f32 x, y, z;
    s32 id;
    s32 u = 0;
    s32 w = 0;

    VEC4_ZERO(v);
    id = ScriptGetInt_26a2a0((s32)p0++);
    v.x = TaggedGetFloat_26a280((s32)p0++);
    v.y = TaggedGetFloat_26a280((s32)p0++);
    v.z = TaggedGetFloat_26a280((s32)p0++);
    v.w = 1.0f;
    x = TaggedGetFloat_26a280((s32)p0++);
    y = TaggedGetFloat_26a280((s32)p0++);
    z = TaggedGetFloat_26a280((s32)p0++);
    if (n >= 8) {
        w = ScriptGetCodeAddr_26a200((s32)p0++);
    }
    if (n >= 9) {
        u = ScriptGetInt_26a2a0((s32)p0);
    }
    EventCameraNodeAddOrbitCastSet_253b10(D_00482060, id, &v, x, u, y, w, z);
    return 1;
}
