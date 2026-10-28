/* rgp:protos */
#define RGP_SELF_MidiSeqDataInit_1b5ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001b5ed0 {
    u8 pad000[0x4];
    s16 m04;         /* +0x4 */
    s16 m06;         /* +0x6 */
    s32 m08;         /* +0x8 */
} Obj_FUN_001b5ed0;

void MidiSeqDataInit_1b5ed0(Obj_FUN_001b5ed0 *o)
{
    o->m04 = 1;
    o->m06 = 0;
    o->m08 = 0;
}
