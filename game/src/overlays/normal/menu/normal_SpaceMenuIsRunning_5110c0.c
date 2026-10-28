/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuIsRunning_5110c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005110C0 -- gate on the gp object at 0x004846B8 being present and
 * in state 0xB.
 * The guard is the CONTAINING form, not an early return: retail's
 * `beql $2,$0,EPI` / `bnel $3,$2,EPI` put the shared result in the branch-likely
 * delay slot, which only happens when the trailing `return 0` is the function's
 * last statement.  Spelling it `if (p == NULL) return 0;` costs 3 words. */
typedef struct N {
    u8 pad000[0x14];
    u8 f14;
} N;

extern void *D_004846B8;

/*rgp*/

s32 normal_SpaceMenuIsRunning_5110c0(void)
{
    N *p = (N *)D_004846B8;

    if (p != NULL) {
        if (p->f14 == 0xB) {
            normal_SpaceMenuRelease_511010();
        } else {
            return 1;
        }
    }
    return 0;
}
