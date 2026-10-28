/* rgp:protos */
#define RGP_SELF_SoundStreamTableDtor_1c2790 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void *SoundStreamTableDtor_1c2790(void *o, s16 flag)
{
    if (o != 0) {
        DestroyArray_1005b0((u8 *)o + 0x4, (void *)SoundStreamDtor_1bfc30, 0x84, 8);
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
