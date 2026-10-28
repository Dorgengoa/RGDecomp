/* rgp:protos */
#define RGP_SELF_ReqEntryInit_3ee700 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* `addiu $3,$0,-2` (= ~1) + `daddiu $5,$0,1`: single-bit bitfield, bit 0 = 1. */
typedef struct P3EE700 {
    u8  b0 : 1;
    u8  b1 : 7;
    u8  pad001[0x3];
    s32 m04;
    s32 m08;
} P3EE700;
void ReqEntryInit_3ee700(P3EE700 *p)
{
    p->b0 = 1;
    p->m04 = 0;
    p->m08 = 0;
}
