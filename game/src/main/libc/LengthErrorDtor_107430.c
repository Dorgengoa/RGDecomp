/* rgp:protos */
#define RGP_SELF_LengthErrorDtor_107430 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_0046FF60[];
extern u8 D_0046FF80[];
extern u8 D_0046FD70[];
/*rgp*/
/*rgp*/

void *LengthErrorDtor_107430(void *o, s16 flag)
{
    void *p;

    if (o != 0) {
        *(const u8 **)o = D_0046FF60;
        if (o != 0) {
            *(const u8 **)o = D_0046FF80;
            p = (u8 *)o + 0x4;
            if (p != 0) {
                SharedArrayPtrDtor_102ab0(p, -1);
            }
            if (o != 0) {
                *(const u8 **)o = D_0046FD70;
            }
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
