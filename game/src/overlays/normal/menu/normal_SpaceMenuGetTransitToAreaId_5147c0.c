/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuGetTransitToAreaId_5147c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005147C0 -- reads a state code off the object hanging at +0x18 of
 * whatever func_1FEDE0 returns, mapping the single value 10 to 7.
 * `return 7` is the LAST statement so it falls through into the epilogue;
 * writing `if (st == 10) return 7; return st;` costs an extra `b`. */
typedef struct S {
    u8  pad000[0x1A8];
    s16 f1A8;
} S;

typedef struct A {
    u8 pad000[0x18];
    S  *f18;
} A;

/*rgp*/

s32 normal_SpaceMenuGetTransitToAreaId_5147c0(void)
{
    A *a;
    s32 st;

    a = ((A *)GetGameData_1fede0());
    if (a == NULL) {
        return -1;
    }
    st = a->f18->f1A8;
    if (st == 10) {
        st = 7;
    }
    return st;
}
