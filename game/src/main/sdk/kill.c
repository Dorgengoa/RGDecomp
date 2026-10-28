/* rgp:protos */
#define RGP_SELF_kill 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* newlib's kill stub: only pid 1 -- the process itself -- is meaningful. */

extern void KernelExit_120d18(s32 sig);

s32 kill(s32 pid, s32 sig)
{
    if (pid == 1) {
        KernelExit_120d18(sig);
    }
    return 0;
}
