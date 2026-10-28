/* rgp:protos */
#define RGP_SELF_SplineInit_257860 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

struct Ent {
    u8 pad000[0x38];
};

struct Obj0 {
    struct Ent m000[0x10];
    s32 m380;
    s32 m384;
    s32 m388;
    u8 pad38C[0xC];
    s32 m398;
};

void SplineInit_257860(struct Obj0 *p0)
{
    s32 i;

    for (i = 0; i < 0x10; i++) {
        SplineSegmentInit_2578f0(&p0->m000[i]);
    }
    p0->m380 = 0;
    p0->m384 = 0;
    p0->m388 = 0;
    p0->m398 = 0;
}
