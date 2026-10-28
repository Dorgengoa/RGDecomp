/* rgp:protos */
#define RGP_SELF_AiCmdRouteTestFlags_2c4440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S8 { s32 a; s32 b; };
struct T { u8 pad000[0xB8]; s32 mB8; };

/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdRouteTestFlags_2c4440(struct S8 *p0)
{
    s32 r1;
    s32 r2;
    struct T *r3;
    s32 m;

    r1 = ScriptSlotGetInt_2cc9c0(p0++);
    r2 = ScriptSlotGetInt_2cc9c0(p0++);
    r3 = ((struct T *)CharaGetAiById_2cedd0(r1));
    if (r3 != 0) {
        m = r3->mB8 & r2;
        if (m != 0) {
            ScriptSlotStoreIntRef_2cc900(p0, 1);
        } else {
            ScriptSlotStoreIntRef_2cc900(p0, 0);
        }
    }
    return 1;
}
