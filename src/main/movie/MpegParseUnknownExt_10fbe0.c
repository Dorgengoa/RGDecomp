#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_00456330[];

extern s32 MpegReportError_115a90(s32, void *);

s32 MpegParseUnknownExt_10fbe0(s32 a4)
{
    return MpegReportError_115a90(a4, D_00456330);
}
