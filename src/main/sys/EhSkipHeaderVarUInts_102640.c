#include "types.h"

extern u8 *DecodeVarUInt_100ed0(u8 *p, u32 *pval);

u8 *EhSkipHeaderVarUInts_102640(s8 *p)
{
    u32 dummy;
    s32 flags = p[0] & 0x40;
    u8 *q;

    q = DecodeVarUInt_100ed0((u8 *)p + 1, &dummy);
    q = DecodeVarUInt_100ed0(q, &dummy);
    if (flags) {
        q = DecodeVarUInt_100ed0(q, &dummy);
    }
    return q;
}
