/* rgp:protos */
#define RGP_SELF_NavMgrAddGraph_30ce30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    s32 m08;
};

s32 NavMgrAddGraph_30ce30(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6)
{
    s32 r0;
    s32 r1;
    s32 r2;
    u32 t0;
    s32 e;
    s32 r5;
    s32 r6;
    s32 r7;
    s32 r8;

    r0 = ((unsigned char)UskMemoryRefIsSet_42d010(p0));
    if (r0 == 0) {
        return 0;
    }
    r1 = NavMgrFindGraphById_30cae0(p0, p2);
    if (r1 != 0) {
        return 0;
    }
    r2 = BitArrayFindValue_42ccd0((u8 *)p0 + 0x1C, 0, 0);
    t0 = p0->m08;
    if ((u32)r2 >= t0) {
        e = 0;
    } else {
        e = p0->m04 + r2 * 288;
    }
    if (e == 0) {
        return 0;
    }
    r5 = UskMemoryRefGet_42d000(p0);
    r6 = NavGraphInit_310ec0(e, p1, p2, p3, p4, p5, p6, r5);
    if (r6 == 0) {
        return 0;
    }
    r7 = NavMgrIndexOf_30cd50((u8 *)p0 + 4, e);
    r8 = NavMgrActivateGraph_30cf70((void *)((s32)p0 + 4), r7);
    e = (r8 != 0) ? e : 0;
    return e;
}
