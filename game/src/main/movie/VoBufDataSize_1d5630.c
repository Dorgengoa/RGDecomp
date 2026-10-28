/* rgp:protos */
#define RGP_SELF_VoBufDataSize_1d5630 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Return the constant 0x1C0000 -- a zero low half, so one lui. */

s32 VoBufDataSize_1d5630(void)
{
    return 0x1C0000;
}
