/* rgp:protos */
#define RGP_SELF_ScriptCmdObjPlaySound_32d090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

struct Obj {
    u8 pad000[0x4FC];
    s32 m4FC;
};

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdObjPlaySound_32d090(E8 *p0, s32 p1)
{
    s32 a;
    s32 b;
    f32 t;
    s32 r;
    struct Obj *o;

    if (p1 <= 0) {
        return 0;
    }
    a = ScriptSlotGetInt_3348b0(p0);
    b = ScriptSlotGetInt_3348b0(p0 + 1);
    t = 1.0f;
    if (p1 > 2) {
        t = ScriptSlotGetFloat_334890(p0 + 2);
    }
    r = GetCurrentScene_1f5be0();
    o = ((struct Obj *)ObjRecGetLiveObject_1c4a90(r, a));
    if (o == 0) {
        return 1;
    }
    SoundPlayScaledVolume_1b9520(o->m4FC, b, 0, t);
    return 1;
}
