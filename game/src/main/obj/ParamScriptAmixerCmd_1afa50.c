/* rgp:protos */
#define RGP_SELF_ParamScriptAmixerCmd_1afa50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S8 { s32 a; s32 b; };

/*rgp*/
/*rgp*/

extern struct { s32 v; s32 pad[3]; } D_0049D4E4;
extern struct { s32 v; s32 pad[3]; } D_0049D4E8;

s32 ParamScriptAmixerCmd_1afa50(struct S8 *p0, s32 p1)
{
    s32 pv;
    struct S8 *q;
    s32 r0;
    s32 r2;

    pv = p1;
    q = p0;
    r0 = VariantGetInt_15f780(q++);
    D_0049D4E4.v = r0;
    SlotGetInt_15f720(q++);
    if (pv >= 3) {
        r2 = VariantGetInt_15f780(q);
        D_0049D4E8.v = r2;
    }
    return 1;
}
