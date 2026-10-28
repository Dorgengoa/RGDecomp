/* rgp:protos */
#define RGP_SELF_ViBufDataSize_1d5620 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Return the constant 0x80000 -- a zero low half, so one lui. */

s32 ViBufDataSize_1d5620(void)
{
    return 0x80000;
}
