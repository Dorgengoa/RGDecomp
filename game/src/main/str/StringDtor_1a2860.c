/* rgp:protos */
#define RGP_SELF_StringDtor_1a2860 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

struct Obj_FUN_001a2860 {
    s32 m00;
    u8 pad004[0x4];
    void *m08;
};

void *StringDtor_1a2860(struct Obj_FUN_001a2860 *o, s16 flag)
{
    if (o != 0) {
        if (o != 0) {
            if ((o->m00 & 1) != 0) {
                OperatorDelete_100840(o->m08);
            }
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
