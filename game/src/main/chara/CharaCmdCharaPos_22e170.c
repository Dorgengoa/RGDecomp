/* rgp:protos */
#define RGP_SELF_CharaCmdCharaPos_22e170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The ObjRecGetLiveObject_1c4a90 result is only tested, never used.  The four gp
   floats seed the vector and three of them are then overwritten. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern f32 D_0047E690;
extern f32 D_0047E694;
extern f32 D_0047E698;
extern f32 D_0047E69C;

struct Obj0 {
    s32 m00;
};

s32 CharaCmdCharaPos_22e170(struct Obj0 *p0, s32 p1, s32 argc)
{
    f32 v[4] __attribute__((aligned(16)));
    s32 r0;
    s32 rec;
    s32 a;
    s32 o;
    f32 x;
    f32 y;
    f32 z;

    if (argc != 4) {
        return 0;
    }
    r0 = GetCurrentScene_1f5be0();
    if (r0 == 0) {
        return 1;
    }
    rec = ((s32)ObjRecGetLiveObject_1c4a90(r0, p0->m00));
    if (rec == 0) {
        return 1;
    }
    a = ScriptArgGetInt_302d70(p1);
    o = GetLiveObjById_1ce420(p0->m00, a);
    if (o == 0) {
        return 1;
    }
    x = ScriptArgGetFloat_302cf0(p1 + 0xF);
    y = ScriptArgGetFloat_302cf0(p1 + 0xA);
    z = ScriptArgGetFloat_302cf0(p1 + 5);
    v[0] = D_0047E690;
    v[1] = D_0047E694;
    v[2] = D_0047E698;
    v[3] = D_0047E69C;
    v[0] = z;
    v[1] = y;
    v[2] = x;
    ModelSetPos_151110(o, v);
    return 1;
}
