/* rgp:protos */
#define RGP_SELF_RecordGetStateParam2Maybe_430850 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 RecordGetStateParam2Maybe_430850(void *rgp_a0)
{
    s32   r;
    void *p;

    r = 2;
    p = RecordFindStateEntry_4308d0((void *)rgp_a0);
    if (p != 0) r = *(s16 *)((u8 *)p + 0x8);
    return r;
}
