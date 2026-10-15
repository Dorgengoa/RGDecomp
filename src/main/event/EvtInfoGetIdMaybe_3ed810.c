#include "types.h"

extern void * EvtInfoLookupRecordMaybe_3ed760(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
};

s32 EvtInfoGetIdMaybe_3ed810(s32 p0)
{
    struct Obj0 *r0;
    s16 t0;

    r0 = EvtInfoLookupRecordMaybe_3ed760(p0);
    if (r0 != 0) {
        t0 = r0->m00;
        return t0;
    }
    return -1;
}
