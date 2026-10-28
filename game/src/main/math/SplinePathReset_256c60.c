/* rgp:protos */
#define RGP_SELF_SplinePathReset_256c60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

/*rgp*/

struct Obj0 {
    u128 m000[0x10];
    s32 m100;
    s32 m104;
    u8 m108[0x39C];
    s32 m4A4;
    s32 m4A8;
};

void SplinePathReset_256c60(struct Obj0 *p0)
{
    s32 i;

    for (i = 0; i < 0x10; i++) {
        p0->m000[i] = 0;
    }
    p0->m100 = 0;
    p0->m104 = 0;
    SplineInit_257860(p0->m108);
    p0->m4A4 = 0;
    p0->m4A8 = 0;
}
