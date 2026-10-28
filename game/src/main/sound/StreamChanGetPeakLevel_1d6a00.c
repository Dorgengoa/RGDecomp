/* rgp:protos */
#define RGP_SELF_StreamChanGetPeakLevel_1d6a00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_001d6a00 {
    u8 pad000[0x80];
    s16 m80;         /* +0x80 */
} Obj4_FUN_001d6a00;

/*rgp*/

s32 StreamChanGetPeakLevel_1d6a00(Obj4_FUN_001d6a00 *o)
{
    return SoundStreamSlotGetPeakLevel_1bc9e0(o->m80);
}
