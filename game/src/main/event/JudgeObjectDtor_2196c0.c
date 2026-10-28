/* rgp:protos */
#define RGP_SELF_JudgeObjectDtor_2196c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_00471AA0[];
/*rgp*/

void *JudgeObjectDtor_2196c0(void *obj, s16 n)
{
    if (obj != 0) {
        *(u8 **)((u8 *)obj + 0xB0) = D_00471AA0;
        if (n > 0) {
            OperatorDelete_100840(obj);
        }
    }
    return obj;
}
