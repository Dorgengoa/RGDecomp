/* rgp:protos */
#define RGP_SELF_SaveFileReadInsectTeams_3e49d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct E12 {
    u8 b[12];
} E12;

typedef struct Obj50 {
    s32 a;
    s32 b;
    E12 e[6];
} Obj50;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 SaveFileReadInsectTeams_3e49d0(u8 *arg0, void *arg1, s32 *arg2, s32 arg3, s32 arg4)
{
    Obj50 o __attribute__((aligned(16)));
    E12 *p;
    u8 t;
    s32 r;
    s32 ret;
    u8 one;

    if (arg1 == 0 || arg3 == 0 || arg4 <= 0) {
        return 0;
    }
    p = o.e;
    do {
        ReqEntryInit_3ee700(p);
        p++;
    } while (p < &o.e[6]);
    ReqListResetMaybe_3ee6b0(&o);
    ReqListResetWithFlagMaybe_3ee640(&o, 0);
    t = o.e[5].b[0];
    one = 1;
    o.e[5].b[0] = (t & ~1) | one;
    r = SaveDataDeserialize_3e5c30(arg0, arg3, arg4, &o);
    if (r <= 0) {
        return 0;
    }
    *arg2 = *(s32 *)(*(u8 **)(arg0 + 0x24) + 4);
    InsectTeamTableCopyTeams_4313e0(*(u8 **)(arg0 + 0x24), arg1);
    return r;
}
