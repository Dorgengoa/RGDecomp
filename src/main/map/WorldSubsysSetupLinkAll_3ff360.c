#include "types.h"

/* Member of the 13-clone group headed by WorldSubsysLinkAll_3f92e0 (48 B each).
   This member differs from the head in the two member offsets and the
   per-type worker called.  The reading is written up in WorldSubsysLinkAll_3f92e0.c. */

typedef struct Own3f9 {
    u8    pad000[0x8];
    s32   m4;                   /* +0x08 */
    u8    pad2[0x4];
    void *m8;                   /* +0x10 */
} Own3f9;

extern void WorldSubsysLinkIds_3ff5f0(void *sub, s32 arg);

s32 WorldSubsysSetupLinkAll_3ff360(Own3f9 *o)
{
    if (o->m8 != 0) {
        WorldSubsysLinkIds_3ff5f0(o->m8, o->m4);
    }
    return 1;
}
