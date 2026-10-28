/* rgp:protos */
#define RGP_SELF_DiscStatusInit_39eed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern s16 D_004836D8;
extern s16 D_004836DC;
extern s16 D_004836E0;

void DiscStatusInit_39eed0(void)
{
    D_004836DC = 0;
    D_004836E0 = 0;
    D_004836D8 = 0;
}
