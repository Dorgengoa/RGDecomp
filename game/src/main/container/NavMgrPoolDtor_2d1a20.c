/* rgp:protos */
#define RGP_SELF_NavMgrPoolDtor_2d1a20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

struct Obj_FUN_002d1a20 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
};

void *NavMgrPoolDtor_2d1a20(struct Obj_FUN_002d1a20 *o, s16 flag)
{
    if (o != 0) {
        o->m00 = 0;
        o->m04 = 0;
        o->m08 = 0;
        o->m0C = 0;
        o->m10 = 0;
        o->m14 = 0;
        BitArrayReset_42cf90((u8 *)o + 0x18);
        if ((void *)((s32)o + 0x18) != 0) {
            BitArrayReset_42cf90((void *)((s32)o + 0x18));
            if (&o->m18 != 0) {
                o->m18 = 0;
                o->m1C = 0;
                if (&o->m18 != 0) {
                    o->m18 = 0;
                    o->m1C = 0;
                    if (&o->m18 != 0) {
                        o->m18 = 0;
                        o->m1C = 0;
                    }
                }
            }
        }
        if (&o->m08 != 0) {
            o->m08 = 0;
            o->m0C = 0;
            o->m10 = 0;
            o->m14 = 0;
            if (&o->m08 != 0) {
                o->m08 = 0;
                o->m0C = 0;
                o->m10 = 0;
                o->m14 = 0;
                if (&o->m08 != 0) {
                    o->m08 = 0;
                    o->m0C = 0;
                    o->m10 = 0;
                }
            }
        }
        if (o != 0) {
            o->m00 = 0;
            o->m04 = 0;
            if (o != 0) {
                o->m00 = 0;
                o->m04 = 0;
                if (o != 0) {
                    o->m00 = 0;
                    o->m04 = 0;
                }
            }
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
