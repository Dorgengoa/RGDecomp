/* rgp:protos */
#define RGP_SELF_CharaCmdCharaRot_22e060 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaCmdCharaRot_22e060(s32 *self, char *s, s32 argc)
{
    void *w;
    void *t;
    void *obj;
    f32 b;
    f32 a;
    f32 c;

    if (argc != 4) {
        return 0;
    }
    w = GetCurrentScene_1f5be0();
    if (w == NULL) {
        return 1;
    }
    t = ObjRecGetLiveObject_1c4a90(w, *self);
    if (t == NULL) {
        return 1;
    }
    obj = GetLiveObjById_1ce420(*self, ScriptArgGetInt_302d70(s));
    if (obj == NULL) {
        return 1;
    }
    a = ScriptArgGetFloat_302cf0(s + 0xF);
    b = ScriptArgGetFloat_302cf0(s + 0xA);
    c = ScriptArgGetFloat_302cf0(s + 0x5);
    {
        f32 v[4] __attribute__((aligned(16))) = {0};

        v[0] = c;
        v[1] = b;
        v[2] = a;
        ModelSetRot_151080(obj, v);
    }
    return 1;
}
