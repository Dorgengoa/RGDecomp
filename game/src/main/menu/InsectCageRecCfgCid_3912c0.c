/* rgp:protos */
#define RGP_SELF_InsectCageRecCfgCid_3912c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T3912C0 { s16 f00; s16 f02; };

extern s8 D_00483438;
extern u8 *D_0048343C;
extern struct T3912C0 *D_00483440;

/*rgp*/

s32 InsectCageRecCfgCid_3912c0(s32 arg0)
{
    D_00483440 = (struct T3912C0 *)(D_0048343C + D_00483438 * 148);
    D_00483440->f00 = VariantGetInt_15f780(arg0);
    D_00483440->f02 = 0;
    D_00483438 = D_00483438 + 1;
    return 1;
}
