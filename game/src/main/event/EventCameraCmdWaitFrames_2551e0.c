/* rgp:protos */
#define RGP_SELF_EventCameraCmdWaitFrames_2551e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Member of the 12-clone group headed by EvSubNodeWaitFrames_252190 (48 B each).
   This member differs from the head in the limit and counter member
   offsets.  The reading is written up in EvSubNodeWaitFrames_252190.c. */

typedef struct Lim252 {
    u8  pad000[0x30];
    s32 limit;                  /* +0x30 */
} Lim252;

typedef struct Cnt252 {
    u8  pad000[0x40];
    s32 count;                  /* +0x40 */
} Cnt252;

s32 EventCameraCmdWaitFrames_2551e0(Lim252 *a, Cnt252 *b)
{
    if (b->count >= a->limit) {
        b->count = 0;
        return 0;
    }
    b->count++;
    return 1;
}
