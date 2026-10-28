/* rgp:protos */
#define RGP_SELF_DynFrameCmd_168d20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

extern struct Obj0 * D_00481154;
extern s32 D_0048115C;
extern s32 D_00481160;

struct Obj0;

struct Obj0 {
    u8 pad000[0x90];
    s32 m90;
    s32 m94;
};

s32 DynFrameCmd_168d20(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 t1;
    struct Obj0 *t2;

    r0 = SlotGetInt_15f720(p0);
    if (r0 == 0) {
        return 0;
    }
    r1 = ((s32)FrameFindByName_149ed0(D_0048115C, r0));
    t1 = D_00481160;
    t2 = D_00481154;
    D_00481160 = (t1 + 1);
    if (t1 >= 0) {
        if (t2->m90 > t1) {
            *(s32 *)((u8 *)t2->m94 + (t1 << 2)) = r1;
        }
    }
    return 1;
}
