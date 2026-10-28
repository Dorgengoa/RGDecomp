/* rgp:protos */
#define RGP_SELF_AiCmdGetGroupMoveTargetMaybe_2c4cc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;
typedef struct E8 { s32 a; s32 b; } E8;

struct H {
    u8 pad000[0xC0];
    u128 mC0;
    u8 pad0D0[0x74];
    s16 m144;
    s16 m146;
};

/*rgp*/
/*rgp*/

extern struct H * const D_004DB930;

s32 AiCmdGetGroupMoveTargetMaybe_2c4cc0(E8 *p0, s32 p1)
{
    union { u128 q; f32 f[4]; } v;
    struct H *h;
    s32 lo;
    s32 hi;

    h = D_004DB930;
    if (h == 0) {
        return 0;
    }
    v.q = h->mC0;
    lo = *(volatile s16 *)&h->m144;
    hi = h->m146;
    ScriptSlotStoreIntRef_2cc900(p0++, lo);
    ScriptSlotStoreFloatRef_2cc8e0(p0++, v.f[0]);
    ScriptSlotStoreFloatRef_2cc8e0(p0++, v.f[1]);
    ScriptSlotStoreFloatRef_2cc8e0(p0++, v.f[2]);
    ScriptSlotStoreFloatRef_2cc8e0(p0++, v.f[3]);
    if (p1 >= 6) {
        ScriptSlotStoreIntRef_2cc900(p0, hi);
    }
    return 1;
}
