/* rgp:protos */
#define RGP_SELF_ResGroupCmdObjSetPair_42aae0 1
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
    u8 pad000[6];
    s16 m06;
    s16 m08;
};

s32 ResGroupCmdObjSetPair_42aae0(SArg *p0)
{
    struct Obj0 *r0;
    s32 r1;
    s32 r2;

    r0 = ResGroupListCurElem_42a510();
    if (r0 == 0) {
        return 1;
    }
    r1 = VariantGetInt_15f780(p0++);
    r0->m06 = r1;
    r2 = VariantGetInt_15f780(p0);
    r0->m08 = r2;
    return 1;
}
