/* rgp:protos */
#define RGP_SELF_WorldSubsysLinkAll_400470 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Member of the 13-clone group headed by WorldSubsysLinkAll_3f92e0 (48 B each).
   This member differs from the head in the two member offsets and the
   per-type worker called.  The reading is written up in WorldSubsysLinkAll_3f92e0.c. */

typedef struct Own3f9 {
    u8    pad000[0x4];
    s32   m4;                   /* +0x04 */
    u8    pad2[0x4];
    void *m8;                   /* +0x0C */
} Own3f9;

/*rgp*/

s32 WorldSubsysLinkAll_400470(Own3f9 *o, int rgp_a1, int rgp_a2, int rgp_a3)
{
    if (o->m8 != 0) {
        WorldSubsysLinkIds_400b80(o->m8, o->m4, (int)rgp_a2, (int)rgp_a3);
    }
    return 1;
}
