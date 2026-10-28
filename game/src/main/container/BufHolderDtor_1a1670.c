/* rgp:protos */
#define RGP_SELF_BufHolderDtor_1a1670 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

struct Obj_FUN_001a1670 {
    u8 pad000[0x8];
    void *m08;
};

void *BufHolderDtor_1a1670(struct Obj_FUN_001a1670 *o, s16 flag)
{
    if (o != 0) {
        if (o != 0) {
            if (o != 0) {
                if (o->m08 != 0) {
                    OperatorDelete_100840(o->m08);
                }
            }
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
