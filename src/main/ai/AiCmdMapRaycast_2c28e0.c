#include "types.h"

typedef struct V4 { f32 x, y, z, w; } V4;
typedef struct Hit { u8 b[0x6000]; } Hit;

extern f32 VecDistance_13d3d0(V4 *, V4 *);
extern s32 MeshRaycastWrapper_16f610(Hit *, s32, V4 *, V4 *, V4 *, s32, s32);
extern void VecMinMax_1cb570(V4 *, V4 *, V4 *, V4 *);
extern s32 MapEvCollectCollPolysMaybe_1ff270(Hit *, s32, V4 *, s32);
extern void ScriptSlotStoreFloatRef_2cc8e0(u64 *, f32);
extern void ScriptSlotStoreIntRef_2cc900(u64 *, s32);
extern f32 ScriptSlotGetFloat_2cc9a0(u64 *);
extern s32 ScriptSlotGetInt_2cc9c0(u64 *);

s32 AiCmdMapRaycast_2c28e0(u64 *p, s32 n)
{
    f32 r;
    s32 k;
    s32 cnt;
    s32 res;

    if (n >= 11) {
        Hit buf;
        V4 a;
        V4 b;
        V4 out;
        V4 hi;
        V4 lo;

        a.x = ScriptSlotGetFloat_2cc9a0(p++);
        a.y = ScriptSlotGetFloat_2cc9a0(p++);
        a.z = ScriptSlotGetFloat_2cc9a0(p++);
        b.x = ScriptSlotGetFloat_2cc9a0(p++);
        b.y = ScriptSlotGetFloat_2cc9a0(p++);
        b.z = ScriptSlotGetFloat_2cc9a0(p++);
        b.w = 1.0f;
        a.w = 1.0f;
        k = ScriptSlotGetInt_2cc9c0(p++);
        r = VecDistance_13d3d0(&a, &b);
        VecMinMax_1cb570(&lo, &hi, &a, &b);
        hi.w = 1.0f;
        lo.w = 1.0f;
        hi.x -= r;
        hi.y -= r;
        hi.z -= r;
        lo.x += r;
        lo.y += r;
        lo.z += r;
        cnt = MapEvCollectCollPolysMaybe_1ff270(&buf, 0x100, &lo, -1);
        res = MeshRaycastWrapper_16f610(&buf, cnt, &a, &b, &out, 1, k);
        if (res >= 0) {
            ScriptSlotStoreIntRef_2cc900(p++, 1);
        } else {
            ScriptSlotStoreIntRef_2cc900(p++, 0);
        }
        ScriptSlotStoreFloatRef_2cc8e0(p++, out.x);
        ScriptSlotStoreFloatRef_2cc8e0(p++, out.y);
        ScriptSlotStoreFloatRef_2cc8e0(p, out.z);
    } else {
        Hit buf;
        V4 a;
        V4 b;
        V4 out;
        V4 hi;
        V4 lo;

        a.x = ScriptSlotGetFloat_2cc9a0(p++);
        a.y = ScriptSlotGetFloat_2cc9a0(p++);
        a.z = ScriptSlotGetFloat_2cc9a0(p++);
        b.x = ScriptSlotGetFloat_2cc9a0(p++);
        b.y = ScriptSlotGetFloat_2cc9a0(p++);
        b.z = ScriptSlotGetFloat_2cc9a0(p++);
        b.w = 1.0f;
        a.w = 1.0f;
        r = VecDistance_13d3d0(&a, &b);
        VecMinMax_1cb570(&lo, &hi, &a, &b);
        hi.w = 1.0f;
        lo.w = 1.0f;
        hi.x -= r;
        hi.y -= r;
        hi.z -= r;
        lo.x += r;
        lo.y += r;
        lo.z += r;
        cnt = MapEvCollectCollPolysMaybe_1ff270(&buf, 0x100, &lo, -1);
        res = MeshRaycastWrapper_16f610(&buf, cnt, &a, &b, &out, 1, 0);
        if (n == 9) {
            ScriptSlotStoreFloatRef_2cc8e0(p++, out.x);
            ScriptSlotStoreFloatRef_2cc8e0(p++, out.y);
            ScriptSlotStoreFloatRef_2cc8e0(p, out.z);
        } else if (n == 7) {
            if (res < 0) {
                ScriptSlotStoreIntRef_2cc900(p, 0);
            } else {
                ScriptSlotStoreIntRef_2cc900(p, 1);
            }
        }
    }
    return 1;
}
