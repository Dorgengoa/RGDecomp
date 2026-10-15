#include "types.h"

/* Member of the 13-clone group headed by WorldSubsysLinkAll_3f92e0 (48 B each).
   This member differs from the head in the two member offsets and the
   per-type worker called.  The reading is written up in WorldSubsysLinkAll_3f92e0.c. */

typedef struct Own3f9 {
    u8    pad000[0x4];
    s32   m4;                   /* +0x04 */
    void *m8;                   /* +0x08 */
} Own3f9;

extern void WorldSubsysLinkIdsNop_3fe410(void *sub, s32 arg);

s32 WorldSubsysLinkAll_3fe2b0(Own3f9 *o)
{
    if (o->m8 != 0) {
        WorldSubsysLinkIdsNop_3fe410(o->m8, o->m4);
    }
    return 1;
}
