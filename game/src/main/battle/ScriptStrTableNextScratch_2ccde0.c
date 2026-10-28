/* rgp:protos */
#define RGP_SELF_ScriptStrTableNextScratch_2ccde0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern volatile s32 D_004825E4;
extern s32 *D_004825DC;

s32 ScriptStrTableNextScratch_2ccde0(s32 *out)
{
    s32 i;
    s32 k;
    s32 j;

    i = D_004825E4;
    k = i + 8;
    j = i + 1;
    D_004825E4 = j;
    D_004825E4 = j % 4;
    *out = k;
    return D_004825DC[k];
}
