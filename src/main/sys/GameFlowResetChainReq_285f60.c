#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern s16 D_004821C0;
extern s16 D_004821C2;
extern s32 D_004821C4;
extern s32 D_004821C8;

void GameFlowResetChainReq_285f60(void)
{
    D_004821C4 = 0;
    D_004821C8 = 0;
    D_004821C0 = -1;
    D_004821C2 = -1;
}
