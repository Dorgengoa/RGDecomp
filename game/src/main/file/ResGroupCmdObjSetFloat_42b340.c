/* rgp:protos */
#define RGP_SELF_ResGroupCmdObjSetFloat_42b340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct SArg {
    s32 w[2];
} SArg;

/*rgp*/
/*rgp*/

struct Obj0;

struct Obj0 {
    u8 pad000[0x14];
    f32 m14;
    f32 m18;
};

s32 ResGroupCmdObjSetFloat_42b340(SArg *p0)
{
    struct Obj0 *r0;
    f32 r1;
    f32 r2;

    r0 = ResGroupListCurElem_42a5d0();
    if (r0 == 0) {
        return 1;
    }
    r1 = VariantGetFloat_15f740(p0++);
    r0->m14 = r1;
    r2 = VariantGetFloat_15f740(p0);
    r0->m18 = r2;
    return 1;
}
