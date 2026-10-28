/* rgp:protos */
#define RGP_SELF_EvSubNodeWinColorTo_2522f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004BDDB0[];

struct Obj0 {
    u8 pad000[0x10];
    u8 m10[0x10];
    s32 m20;
};

struct Obj1 {
    u8 pad000[0x50];
    s32 m50;
    u8 pad054[0xC];
    s32 m60;
    u8 pad064[0xBC];
    u8 m120[0x10];
};

s32 EvSubNodeWinColorTo_2522f0(struct Obj0 *p0, struct Obj1 *p1)
{
    f32 v50[4] __attribute__((aligned(16)));
    f32 v40[4] __attribute__((aligned(16)));
    f32 v30[4] __attribute__((aligned(16)));

    if (p1->m50 >= p0->m20) {
        EventCastSetWinColor_257dc0(D_004BDDB0, p1->m60, p0->m10);
        p1->m50 = 0;
        return 0;
    }
    if (p1->m50 <= 0) {
        EventCastGetWinColor_257d50(D_004BDDB0, p1->m60, v40);
        VecSub_13be40(v50, (f32 *)p0->m10, v40);
        sceVu0DivVector(p1->m120, v50, (f32)p0->m20);
    } else {
        EventCastGetWinColor_257d50(D_004BDDB0, p1->m60, v30);
        VecAdd_13be20(v30, v30, p1->m120);
        EventCastSetWinColor_257dc0(D_004BDDB0, p1->m60, v30);
    }
    p1->m50 = p1->m50 + 1;
    return 1;
}
