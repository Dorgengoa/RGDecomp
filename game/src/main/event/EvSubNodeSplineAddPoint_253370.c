/* rgp:protos */
#define RGP_SELF_EvSubNodeSplineAddPoint_253370 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 EvSubNodeSplineAddPoint_253370(void *a, void *b)
{
    SplinePathAddPoint_256c10((u8 *)b + 0x140, (u8 *)a + 0x10);
    return 0;
}
