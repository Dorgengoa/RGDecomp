#include "types.h"

/* Head of a 13-member clone group (48 B each), the widest multiplier still
   open on MAIN.  Members differ only in the two member offsets and in which
   per-type worker is called.  Forward the owned sub-object to its worker if
   it exists; the result is unconditionally 1. */

typedef struct Own3f9 {
    u8    pad000[0x4];
    s32   m4;                   /* +0x04 */
    void *m8;                   /* +0x08 */
} Own3f9;

extern void WorldSubsysLinkIds_3f94f0(void *sub, s32 arg);

s32 WorldSubsysLinkAll_3f92e0(Own3f9 *o)
{
    if (o->m8 != 0) {
        WorldSubsysLinkIds_3f94f0(o->m8, o->m4);
    }
    return 1;
}
