#include "types.h"

extern void IpuSkipBits_10de00(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void IpuSkipBitsThunk_10de00(s32 p0, s32 p1)
{
    IpuSkipBits_10de00(p0, p1);
}
