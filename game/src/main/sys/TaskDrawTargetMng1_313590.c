/* rgp:protos */
#define RGP_SELF_TaskDrawTargetMng1_313590 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004E7E60[];

/*rgp*/

s32 TaskDrawTargetMng1_313590(void)
{
    return (TargetMngDraw1_31edf0(D_004E7E60), (s32)0);
}
