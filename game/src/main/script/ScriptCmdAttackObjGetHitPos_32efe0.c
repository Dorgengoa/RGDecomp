/* rgp:protos */
#define RGP_SELF_ScriptCmdAttackObjGetHitPos_32efe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;
typedef struct E8 { s32 a; s32 b; } E8;

struct Obj {
    u8 pad000[0x80];
    s32 m80;
    u8 pad084[0xEC];
    u128 m170;
};

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdAttackObjGetHitPos_32efe0(E8 *p0, s32 p1)
{
    union { u128 q; f32 f[4]; } v;
    s32 m;
    s32 k;
    struct Obj *o;
    u8 flag;

    if (p1 != 4 && p1 != 5) {
        return 0;
    }
    flag = 0;
    m = ((s32)GetObjRefTable_313de0());
    k = ScriptSlotGetInt_3348b0(p0);
    o = ((struct Obj *)HandleRegistryLookup_314aa0(m, k));
    if (o != 0) {
        v.q = o->m170;
        ScriptSlotStoreFloatRef_3347d0(p0 + 1, v.f[0]);
        ScriptSlotStoreFloatRef_3347d0(p0 + 2, v.f[1]);
        ScriptSlotStoreFloatRef_3347d0(p0 + 3, v.f[2]);
        flag = (o->m80 & 2) != 0;
    }
    if (p1 == 5) {
        ScriptSlotStoreIntRef_3347f0(p0 + 4, flag);
    }
    return 1;
}
