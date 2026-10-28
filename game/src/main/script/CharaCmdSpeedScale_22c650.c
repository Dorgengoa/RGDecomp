/* rgp:protos */
#define RGP_SELF_CharaCmdSpeedScale_22c650 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaCmdSpeedScale_22c650(s32 *arg0, s32 arg1, s32 arg2)
{
    Vec v __attribute__((aligned(16)));
    Vec m[4] __attribute__((aligned(16)));
    Vec r __attribute__((aligned(16)));
    f32 a;
    f32 b;
    f32 c;
    s32 obj;
    u8 *p;
    u32 n;

    if (arg2 != 1 && arg2 != 3) {
        return 1;
    }
    obj = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), *arg0));
    if (obj == 0) {
        return 1;
    }
    a = ScriptArgGetFloat_302cf0(arg1);
    if (arg2 > 2) {
        b = ScriptArgGetFloat_302cf0(arg1 + 5);
    } else {
        b = a;
    }
    if (arg2 > 2) {
        c = ScriptArgGetFloat_302cf0(arg1 + 10);
    } else {
        c = a;
    }
    CharaGetVelocity_238890(obj, &v);
    v.y *= b;
    CharaGetSrtMatrix_2388c0(obj, m);
    n = 0x10;
    p = (u8 *)&r;
    if (p != NULL) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    r.x = VecDotXZ_1cba70(&v, &m[0]);
    r.y = v.y;
    r.z = VecDotXZ_1cba70(&v, &m[2]);
    r.z *= c;
    r.x *= a;
    v.z = r.x * m[0].z + r.z * m[2].z;
    v.x = r.x * m[0].x + r.z * m[2].x;
    CharaSetVelocityFromVec_238790(obj, &v);
    return 1;
}
