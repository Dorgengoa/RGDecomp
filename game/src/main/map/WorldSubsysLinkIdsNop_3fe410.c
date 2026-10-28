/* rgp:protos */
#define RGP_SELF_WorldSubsysLinkIdsNop_3fe410 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Iter_FUN_003fe410 {
    u8 d[0x8];
} Iter_FUN_003fe410;

/*rgp*/
/*rgp*/

s32 WorldSubsysLinkIdsNop_3fe410(u8 *a, s32 b, int rgp_a2, int rgp_a3)
{
    Iter_FUN_003fe410 it __attribute__((aligned(16)));
    u8 *p;

    if (b == 0) {
        return 0;
    }
    p = a;
    if (a != 0) {
        p = p + 0x88;
    }
    IterInit_370170(&it, p, (int)rgp_a2, (int)rgp_a3);
    while (IterNext_370040(&it) != 0) {
    }
    return 1;
}
