/* rgp:protos */
#define RGP_SELF_EffectReleaseByKey_2e1260 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct ElemFUN_002e1260 {
    u8 pad0[0x174];
    s32 unk174;
    s32 unk178;
    u8 pad17C[0x1D4 - 0x17C];
    s32 unk1D4;
} ElemFUN_002e1260;

/*rgp*/
/*rgp*/

void EffectReleaseByKey_2e1260(s32 arg0, s32 arg1)
{
    s32 i;
    ElemFUN_002e1260 *e;

    for (i = 0; i < 0x30; i++) {
        e = (ElemFUN_002e1260 *)((u8 *)arg0 + i * 0x70);
        if (e->unk174 >= 0 && e->unk1D4 >= 0) {
            EffDefDestroyInstancesByTag_19ff40(arg0 + 0x58, e->unk178, arg1);
        }
    }
    EffectEntriesReleaseNodesByTag_2de610(arg0 + 0x1674, arg1);
}
