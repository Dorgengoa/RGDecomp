/* rgp:protos */
#define RGP_SELF_HatenaMarkBindModel_3451a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

extern u8 D_004628E8[];
extern u8 D_004628F0[];

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
};

s32 HatenaMarkBindModel_3451a0(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;

    if (p1 == 0) {
        return 1;
    }
    p0->m00 = p1;
    r0 = ModelGetRootFrame_1511a0(p1);
    p0->m08 = r0;
    if (r0 == 0) {
        return 2;
    }
    r1 = ((s32)FrameFindByName_149ed0(p0->m08, D_004628E8));
    p0->m04 = r1;
    if (r1 == 0) {
        return 3;
    }
    r2 = ((s32)FrameFindByName_149ed0(p0->m08, D_004628F0));
    p0->m08 = r2;
    if (r2 != 0) {
        return 0;
    }
    return 4;
}
