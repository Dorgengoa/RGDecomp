/* rgp:protos */
#define RGP_SELF_AnyOfFourIdsNegative_3eec60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
    s16 m04;
    s16 m06;
};

s32 AnyOfFourIdsNegative_3eec60(struct Obj0 *p0)
{
    if (p0->m00 >= 0) {
        if (p0->m02 >= 0) {
            if (p0->m04 >= 0) {
                if (p0->m06 >= 0) goto zero;
            }
        }
    }
    return 1;
zero:
    return 0;
}
