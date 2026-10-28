/* rgp:protos */
#define RGP_SELF_EvCmdLetterboxFade_244a30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vm_slot.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

s32 EvCmdLetterboxFade_244a30(Slot *p0, s32 p1)
{
    s32 r0;
    struct Obj0 *r1;
    f32 v;

    r0 = ScriptGetInt_2490f0(p0++);
    r1 = GetLetterbox_27bd80();
    v = 10.0f;
    if (p1 == 2) {
        v = TaggedGetFloat_2490d0(p0);
    }
    if (r0 != 0) {
        r1->m18 = -0x20;
        LetterboxSetFade_277ea0(r1, 1.0f, v, 0.0f);
    } else {
        LetterboxSetFade_277ea0(r1, 0.0f, v, 0.0f);
    }
    return 1;
}
