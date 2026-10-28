/* rgp:protos */
#define RGP_SELF_WorldSubsysLinkAll_3f92e0 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/

s32 WorldSubsysLinkAll_3f92e0(Own3f9 *o, int rgp_a1, int rgp_a2, int rgp_a3)
{
    if (o->m8 != 0) {
        WorldSubsysLinkIds_3f94f0(o->m8, o->m4, (int)rgp_a2, (int)rgp_a3);
    }
    return 1;
}
