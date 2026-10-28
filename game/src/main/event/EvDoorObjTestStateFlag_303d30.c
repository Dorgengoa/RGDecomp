/* rgp:protos */
#define RGP_SELF_EvDoorObjTestStateFlag_303d30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj {
    u8 pad000[0x1A4];
    s32 mF;
};

struct Root {
    u8 pad00[0x10];
    void *m10;
};

/*rgp*/
/*rgp*/

s32 EvDoorObjTestStateFlag_303d30(struct Obj *o)
{
    struct Root *r;

    if (o->mF == 0) {
        return 1;
    }
    r = ((struct Root *)GetGameData_1fede0());
    return StateFlagTestByName_3ccd10(r->m10, *(volatile s32 *)&o->mF);
}
