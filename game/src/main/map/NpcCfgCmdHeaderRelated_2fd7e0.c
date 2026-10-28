/* rgp:protos */
#define RGP_SELF_NpcCfgCmdHeaderRelated_2fd7e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8_002FD7E0 {
    u8 b[8];
} E8_002FD7E0;

/*rgp*/
extern s16 D_004E6624;

s32 NpcCfgCmdHeaderRelated_2fd7e0(E8_002FD7E0 *p0, s32 p1)
{
    s32 r1;
    E8_002FD7E0 *q;

    q = p0;
    if (p1 != 2) {
        return 0;
    }
    VariantGetInt_15f780(q++);
    r1 = VariantGetInt_15f780(q);
    *(s16 *)&D_004E6624 = r1;
    return 1;
}
