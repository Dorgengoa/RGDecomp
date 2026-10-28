/* rgp:protos */
#define RGP_SELF_SceneParentStackSetup_202030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045C140[];

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x2C];
    s32 m2C;
    u8 pad030[0x4];
    s32 m34;
};

struct Obj1 {
    u8 pad000[0x4350];
    s32 m4350;
};

void SceneParentStackSetup_202030(void)
{
    struct Obj1 *r0;
    struct Obj1 * rv7;
    struct Obj0 *r1;
    s32 t0;
    s32 t1;
    s32 r2;
    s32 t2;
    s32 rv6;
    s32 r4;
    s32 r5;

    r0 = GetCurrentScene_1f5be0();
    rv7 = (struct Obj1 *)r0;
    if (r0 != 0) {
        r1 = (struct Obj0 *)GetMainStack_1c6dc0();
        t0 = r1->m34;
        t1 = r1->m2C;
        r2 = MemStackAllocQw_14d950(r1, ((t0 - t1) + 0xFFFD7FFC));
        SceneMainStackInit_1c4370(r0, r2, ((t0 - t1) + 0xFFFD7FFC));
        t2 = r0->m4350;
        if (t2 == -1) {
            r4 = RecStackPush_1c4240(r0, D_0045C140);
            r0->m4350 = r4;
            rv6 = r4;
        } else {
            r5 = RecStackPopAndReset_1c41e0(r0, t2);
            rv6 = r5;
        }
        rv7 = (struct Obj1 *)rv6;
    }
}
