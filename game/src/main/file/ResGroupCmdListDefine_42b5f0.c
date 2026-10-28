/* rgp:protos */
#define RGP_SELF_ResGroupCmdListDefine_42b5f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct SArg {
    s32 w[2];
} SArg;

/*rgp*/
/*rgp*/

extern s32 D_00483FE0;
extern s32 D_00483FE4;
extern s32 D_00483FE8;
extern s16 D_00484000;

s32 ResGroupCmdListDefine_42b5f0(SArg *p0)
{
    s32 r1;
    s32 r2;
    s32 t0;

    D_00484000 = -1;
    D_00483FE4 = 0;
    D_00483FE8 = 0;
    r1 = VariantGetInt_15f780(p0++);
    r2 = VariantGetInt_15f780(p0);
    t0 = D_00483FE0;
    D_00483FE4 = ResGroupListAppendNew_42c530(t0, r1, r2);
    D_00484000 = 0;
    return 1;
}
