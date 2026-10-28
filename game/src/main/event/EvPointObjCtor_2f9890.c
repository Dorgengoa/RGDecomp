/* rgp:protos */
#define RGP_SELF_EvPointObjCtor_2f9890 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of NodeObjBasicCtor_18c570 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/

extern u8 D_00471960[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xDC];
    void *mDC;
};

struct Obj0 *EvPointObjCtor_2f9890(struct Obj0 *p0)
{
    s32 r0;
    s32 r1;

    r0 = ((s32)EvObjCtor_2f9f00(p0));
    p0->mDC = D_00471960;
    r1 = (EvObjResetThunk_2f9eb0(p0), (s32)0);
    return p0;
}
