/* rgp:protos */
#define RGP_SELF_LogicErrorDtor_1073b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_0046FF80[];
extern u8 D_0046FD70[];
/*rgp*/
/*rgp*/

void *LogicErrorDtor_1073b0(void *o, s16 flag)
{
    void *p;

    if (o != 0) {
        *(const u8 **)o = D_0046FF80;
        p = (u8 *)o + 0x4;
        if (p != 0) {
            SharedArrayPtrDtor_102ab0(p, -1);
        }
        if (o != 0) {
            *(const u8 **)o = D_0046FD70;
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
