/* rgp:protos */
#line 1
#include "types.h"

struct R_00331b50 {
    u8 pad[0x448];
    f32 f448;
};

struct B_00331b50 {
    u8 pad[0x190];
};

struct G_00331b50 : public B_00331b50 {
    VC_VPTR_MEMBER;
    
    
    
    R_00331b50 * v4() { return VCM0(R_00331b50 *, 0x18); }
};

struct T_00331b50 { s32 a, b; };

extern "C" G_00331b50 *D_004826E0;
extern "C" int ScriptSlotGetInt_3348b0(T_00331b50 *);
extern "C" f32 ScriptSlotGetFloat_334890(T_00331b50 *);

extern "C" s32 ScriptCmdCurObjSetAlpha_331b50(T_00331b50 *q)
{
    f32 f;
    R_00331b50 *r;

    ScriptSlotGetInt_3348b0(q++);
    if (D_004826E0 == 0) return 0;
    f = ScriptSlotGetFloat_334890(q);
    r = D_004826E0->v4();
    if (r == 0) return 0;
    r->f448 = f;
    return 1;
}
