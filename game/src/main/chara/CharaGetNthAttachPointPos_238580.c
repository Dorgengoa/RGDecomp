/* rgp:protos */
#define RGP_SELF_CharaGetNthAttachPointPos_238580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of MapAreaModelFindModelCfgEntry_1896e0 (byte-identical, in cunits). */

/*rgp*/

struct Obj0;

struct Obj0 {
    u8 pad000[0x3F4];
    s32 m3F4;
};

s32 CharaGetNthAttachPointPos_238580(struct Obj0 *p0, s32 p1, s32 p2, void *rgp_a3)
{
    s32 t0;
    s32 r0;

    t0 = p0->m3F4;
    if (t0 != 0) {
        r0 = ((s32)ObjGetNthAttachPointPos_1ade20(t0, p1, p2, (void *)rgp_a3));
        return r0;
    }
    return 0;
}
