/* rgp:protos */
#define RGP_SELF_WorldDataCmdSetPendingEncounter_3b8dc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Pool {
    u8  pad000[0x94];
    s32 m94;
    u8  pad098[0x2];
    u8  b0 : 1;
    u8  b1 : 1;
    u8  b2 : 1;
    u8  b3 : 5;
} Pool;

extern Pool *D_004830F8;
/*rgp*/
/*rgp*/
/*rgp*/

s32 WorldDataCmdSetPendingEncounter_3b8dc0(void *rgp_a0)
{
    Pool *p = D_004830F8;
    s32 t;

    if (!p->b2) return 1;
    t = VariantGetInt_15f780((void *)rgp_a0);
    if (t >= 0) {
        GameDataSetPendingEncounterId_3e67b0(p->m94, t);
    }
    SoundCmdNopRelated_207eb0();
    return 1;
}
