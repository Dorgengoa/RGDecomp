/* rgp:protos */
#define RGP_SELF_StateMachineSetState_28ede0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Hub function, called from many already-merged src/ files (src/bodies/*,
   src/bodies2/*, src/p22d/*, src/p23a/*) -- their extern declarations pin
   the signature as (s32, s32, s32) returning s32 (some callers discard the
   return value, hence a couple of "void" declarations coexist). */

struct CB0028ede0 {
    u8 pad0[4];
    void (*func)(void *, s32);
};

struct Obj0028ede0 {
    u16 f0;
    u8 pad2[2];
    struct CB0028ede0 *f4;
    s32 f8;
};

/*rgp*/

s32 StateMachineSetState_28ede0(struct Obj0028ede0 *arg0, s32 arg1, s32 arg2)
{
    s32 r;

    if (arg0->f8 == 0) {
        return 0;
    }
    r = ((s32)StateMachineFindState_28ee80(arg0, arg1));
    if (r == 0) {
        return 0;
    }
    arg0->f0 = (u16)arg1;
    arg0->f4 = 0;
    if (arg2 != 0) {
        r = ((s32)StateMachineFindState_28ee80(arg0, arg0->f0));
        arg0->f4 = (struct CB0028ede0 *)r;
        if (r != 0) {
            arg0->f0 = 0;
            arg0->f4->func(arg0, 1);
        }
    }
    return 1;
}
