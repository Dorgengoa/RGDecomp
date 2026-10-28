/* rgp:protos */
#define RGP_SELF_FrameCopyUnlinked_14a790 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

struct Q3 { u128 v[3]; };
struct W16 { u32 v[16]; };

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    u8  m24;
    u8  m25;
    s16 m26;
    s8  m28;
    s8  m29;
    s8  m2A;
    s8  m2B;
    s8  m2C;
    s8  m2D;
    s16 m2E;
    struct Q3  m30;
    struct W16 m60;
    struct W16 mA0;
};

void FrameCopyUnlinked_14a790(struct Obj0 *p0, struct Obj0 *p1)
{
    p1->m00 = p0->m00;
    p1->m04 = p0->m04;
    p1->m08 = p0->m08;
    p1->m0C = p0->m0C;
    p1->m10 = p0->m10;
    p1->m14 = p0->m14;
    p1->m18 = p0->m18;
    p1->m1C = p0->m1C;
    p1->m20 = p0->m20;
    p1->m24 = p0->m24;
    p1->m25 = p0->m25;
    p1->m26 = p0->m26;
    p1->m28 = p0->m28;
    p1->m29 = p0->m29;
    p1->m2A = p0->m2A;
    p1->m2B = p0->m2B;
    p1->m2C = p0->m2C;
    p1->m2D = p0->m2D;
    p1->m2E = p0->m2E;
    p1->m30 = p0->m30;
    p1->m60 = p0->m60;
    p1->mA0 = p0->mA0;
    p1->m04 = 0;
    p1->m08 = 0;
    p1->m0C = 0;
    p1->m10 = 0;
    p1->m29 = 1;
}
