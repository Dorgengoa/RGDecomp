/* rgp:protos */
#define RGP_SELF_SoundStreamSlotDtor_1bf6c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void *SoundStreamSlotDtor_1bf6c0(void *o, s16 flag)
{
    void *p;

    if (o != 0) {
        p = (u8 *)o + 0xC;
        if (p != 0) {
            SemaHandleDelete_1c2150(p);
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
