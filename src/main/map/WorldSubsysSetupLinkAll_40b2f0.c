#include "types.h"

/* Member of the 13-clone group headed by WorldSubsysLinkAll_3f92e0 (48 B each).
   This member differs from the head in the two member offsets and the
   per-type worker called.  The reading is written up in WorldSubsysLinkAll_3f92e0.c. */

typedef struct Own3f9 {
    u8    pad000[0x8];
    s32   m4;                   /* +0x08 */
    void *m8;                   /* +0x0C */
} Own3f9;

extern void WorldSubsysLinkIds_40b490(void *sub, s32 arg);

s32 WorldSubsysSetupLinkAll_40b2f0(Own3f9 *o)
{
    if (o->m8 != 0) {
        WorldSubsysLinkIds_40b490(o->m8, o->m4);
    }
    return 1;
}
