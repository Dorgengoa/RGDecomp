/* rgp:protos */
#define RGP_SELF_SlotRecordValidate_3e52b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
extern struct { s32 v; s32 pad[3]; } D_004658F0;
/*rgp*/

s32 SlotRecordValidate_3e52b0(void *a, s32 b, s32 c, s32 d, s32 e)
{
    if (b == 0 || c < D_004658F0.v) return 0;
    return SaveHeaderValidate_3e5100(a, b, d, e);
}
