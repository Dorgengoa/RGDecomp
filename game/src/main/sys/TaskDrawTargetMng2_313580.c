/* rgp:protos */
#define RGP_SELF_TaskDrawTargetMng2_313580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004E7E60[];

/*rgp*/

s32 TaskDrawTargetMng2_313580(void)
{
    return (TargetMngDraw2_31edb0(D_004E7E60), (s32)0);
}
