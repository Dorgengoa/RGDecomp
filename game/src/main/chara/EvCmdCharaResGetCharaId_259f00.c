/* rgp:protos */
#define RGP_SELF_EvCmdCharaResGetCharaId_259f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

struct Obj0 {
    u8 pad000[0x2];
    s16 m02;
};

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdCharaResGetCharaId_259f00(E8 *p0)
{
    s32 r0;
    s32 r1;
    struct Obj0 *r2;
    s16 t0;

    r0 = ((s32)GetCharaResMgr_1fdb60());
    r1 = ScriptGetInt_26a2a0(p0++);
    r2 = ((struct Obj0 *)CharaResFindById_1f0530(r0, r1));
    if (r2 != 0) {
        t0 = r2->m02;
        ScriptSetRefInt_26a1e0(p0, t0);
    } else {
        ScriptSetRefInt_26a1e0(p0, -1);
    }
    return 1;
}
