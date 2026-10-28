/* rgp:protos */
#define RGP_SELF_EvCmdObjHasMotion_259c90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 x, y, z; } V259c90;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdObjHasMotion_259c90(s64 *arg0, s32 arg1)
{
    V259c90 v __attribute__((aligned(16)));
    s32 s1;
    s32 s2;
    s32 a;
    s32 b;
    u8 *t;

    if (arg1 != 3) {
        return 0;
    }
    a = ScriptGetInt_26a2a0((s32)arg0++);
    b = ScriptGetCodeAddr_26a200((s32)arg0++);
    ScriptSetRefInt_26a1e0((s32)arg0, 0);
    t = ((u8 *)ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), a));
    if (t == NULL) {
        return 1;
    }
    v.x = *(s32 *)(t + 0x1F0);
    v.y = *(s32 *)(t + 0x1F4);
    v.z = *(s32 *)(t + 0x1F8);
    if (((s32)MotionListFindByName_1721d0(&v, b, &s1, &s2)) != 0) {
        ScriptSetRefInt_26a1e0((s32)arg0, 1);
    }
    return 1;
}
