/* rgp:protos */
#define RGP_SELF_ResGroupCmdListDefine_42b1c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct SArg {
    s32 w[2];
} SArg;

/*rgp*/
/*rgp*/

extern s32 D_00483FE0;
extern s32 D_00483FEC;
extern s16 D_00484004;

s32 ResGroupCmdListDefine_42b1c0(SArg *p0)
{
    s32 r1;
    s32 r2;
    s32 t0;

    D_00484004 = -1;
    D_00483FEC = 0;
    r1 = VariantGetInt_15f780(p0++);
    r2 = VariantGetInt_15f780(p0);
    t0 = D_00483FE0;
    D_00483FEC = ResGroupListAppendNew_42c400(t0, r1, r2);
    D_00484004 = 0;
    return 1;
}
