/* rgp:protos */
#define RGP_SELF_TreasureBoxScriptEnd_278c40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x18E];
    s16 m18E;
};

struct Obj2 {
    u8 pad000[0xA44];
    s32 mA44;
};

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 TreasureBoxScriptEnd_278c40(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    struct Obj1 *t0;
    s32 t1;
    s32 r1;
    struct Obj2 *r2;
    s32 t2;
    s32 t3;

    r0 = ((struct Obj0 *)GetGameData_1fede0());
    t0 = r0->m18;
    t1 = t0->m18E;
    r1 = ((s32)GetActionMgr_1fdb50());
    r2 = ((struct Obj2 *)ActionMgrFindById_233b50(r1, t1));
    if (r2 != 0) {
        t2 = r2->mA44;
        t3 = t2 & 0xEFFFFFFF;
        r2->mA44 = t3;
        r2->mA44 = t3 & 0xF7FFFFFF;
    }
    return (SetFieldControlActive_27bd30(1), (s32)0);
}
