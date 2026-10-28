/* rgp:protos */
#define RGP_SELF_WorldSubsysSetupLinkAll_4081b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Member of the 13-clone group headed by WorldSubsysLinkAll_3f92e0 (48 B each).
   This member differs from the head in the two member offsets and the
   per-type worker called.  The reading is written up in WorldSubsysLinkAll_3f92e0.c. */

typedef struct Own3f9 {
    u8    pad000[0x8];
    s32   m4;                   /* +0x08 */
    void *m8;                   /* +0x0C */
} Own3f9;

/*rgp*/

s32 WorldSubsysSetupLinkAll_4081b0(Own3f9 *o)
{
    if (o->m8 != 0) {
        WorldSubsysLinkIds_408c00(o->m8, o->m4);
    }
    return 1;
}
