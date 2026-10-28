/* rgp:protos */
#define RGP_SELF_EvCmdObjSetClothSimEnabled_25d030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj {
    u8 pad000[0x460];
    s32 m460;
};

/*rgp*/
/*rgp*/

s32 EvCmdObjSetClothSimEnabled_25d030(void *a0)
{
    void *q;
    struct Obj *o;

    q = a0;
    a0 = (u8 *)a0 + 8;
    o = ((struct Obj *)EventSceneGetObj_2676e0(ScriptGetInt_26a2a0(q)));
    if (o == 0) {
        return 0;
    }
    o->m460 = (s32)ScriptGetInt_26a2a0(a0);
    return 1;
}
