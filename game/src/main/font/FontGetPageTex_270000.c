/* rgp:protos */
#define RGP_SELF_FontGetPageTex_270000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_004C3140[8];

s32 FontGetPageTex_270000(s32 i)
{
    if (i < 0 || i >= 8) return 0;
    return D_004C3140[i];
}
