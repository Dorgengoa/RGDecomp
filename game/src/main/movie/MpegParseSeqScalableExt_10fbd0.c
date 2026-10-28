/* rgp:protos */
#define RGP_SELF_MpegParseSeqScalableExt_10fbd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_00456300[];

extern s32 MpegReportError_115a90(s32, void *);

s32 MpegParseSeqScalableExt_10fbd0(s32 a4)
{
    return MpegReportError_115a90(a4, D_00456300);
}
