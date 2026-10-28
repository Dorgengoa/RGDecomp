/* rgp:protos */
#define RGP_SELF_AiCmdGetMp_2c6f20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct E2c6f20 { s32 a; s32 b; };

extern void *D_004DB928[];
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdGetMp_2c6f20(struct E2c6f20 *p, s32 kind)
{
    s32 a;
    s32 b;
    s32 r;
    void *x;

    if (*(s32 *)p == 0) {
        x = ScriptSlotGetInt_2cc9c0(p++);
        a = 0;
        r = ActorGetMpById_2cd780(x, &a);
        ScriptSlotStoreIntRef_2cc900(p++, r);
        if (kind == 3) {
            ScriptSlotStoreIntRef_2cc900(p, a);
        }
    } else {
        x = D_004DB928[0];
        b = 0;
        r = ActorGetMpById_2cd780(x, &b);
        ScriptSlotStoreIntRef_2cc900(p++, r);
        if (kind == 2) {
            ScriptSlotStoreIntRef_2cc900(p, b);
        }
    }
    return 1;
}
