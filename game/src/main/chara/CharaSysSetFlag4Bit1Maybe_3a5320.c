/* rgp:protos */
#define RGP_SELF_CharaSysSetFlag4Bit1Maybe_3a5320 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* `addiu $3,$0,-3` (= ~2) + `daddiu $5,$0,2` then `and`/`or`: a SINGLE-BIT
   bitfield store, LSB-first, mask 0x02 -> bit 1 set to 1. */
typedef struct P3A5320 {
    u8 pad000[0x4];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 6;
} P3A5320;
void CharaSysSetFlag4Bit1Maybe_3a5320(P3A5320 *p) { p->b1 = 1; }
