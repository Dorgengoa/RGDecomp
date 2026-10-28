/* rgp:protos */
#define RGP_SELF_EvSubNodeWaitFrames_252190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Head of a 12-member clone group (48 B each).  Members differ only in the
   two member offsets.  A per-frame countdown: advance the counter while it is
   below the owner's limit, otherwise reset it and report that it wrapped. */

typedef struct Lim252 {
    u8  pad000[0x20];
    s32 limit;                  /* +0x20 */
} Lim252;

typedef struct Cnt252 {
    u8  pad000[0x58];
    s32 count;                  /* +0x58 */
} Cnt252;

s32 EvSubNodeWaitFrames_252190(Lim252 *a, Cnt252 *b)
{
    if (b->count >= a->limit) {
        b->count = 0;
        return 0;
    }
    b->count++;
    return 1;
}
