/* rgp:protos */
#define RGP_SELF_MesWinSumLineHeights_272250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern s32 D_0045F208;

s32 MesWinSumLineHeights_272250(s32 arg0, s32 arg1)
{
    s32 acc;
    s32 i;
    s16 val;

    acc = 0;
    val = D_0045F208 + 4;
    for (i = 0; i < arg1; i++) {
        acc += val;
        acc += ((short)MesWinGetLineSpacing_2722e0(arg0, i));
    }
    return acc;
}
