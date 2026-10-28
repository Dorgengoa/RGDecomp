/* rgp:protos */
#define RGP_SELF_AiCmdRouteSetFlags_2c44d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct E8 { s32 a; s32 b; };

struct Obj0 {
    u8 pad000[0xB8];
    s32 mB8;
};

/*rgp*/
/*rgp*/

s32 AiCmdRouteSetFlags_2c44d0(struct E8 *p0)
{
    struct E8 *q;
    s32 r0;
    s32 r1;
    s32 r2;
    struct Obj0 *r3;
    s32 t0;
    s32 t1;

    q = p0;
    r0 = ScriptSlotGetInt_2cc9c0(q++);
    r1 = ScriptSlotGetInt_2cc9c0(q++);
    r2 = ScriptSlotGetInt_2cc9c0(q);
    r3 = ((struct Obj0 *)CharaGetAiById_2cedd0(r0));
    if (r3 != 0) {
        if (r2 != 0) {
            t0 = r3->mB8;
            r3->mB8 = (t0 | r1);
        } else {
            t1 = r3->mB8;
            r3->mB8 = (t1 & ~r1);
        }
    }
    return 1;
}
