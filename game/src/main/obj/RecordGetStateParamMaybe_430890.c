/* rgp:protos */
#define RGP_SELF_RecordGetStateParamMaybe_430890 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 RecordGetStateParamMaybe_430890(void *rgp_a0)
{
    s32   r;
    void *p;

    r = 2;
    p = RecordFindStateEntry_4308d0((void *)rgp_a0);
    if (p != 0) r = *(s16 *)((u8 *)p + 0x6);
    return r;
}
