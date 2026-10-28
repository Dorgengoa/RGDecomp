/* rgp:protos */
#define RGP_SELF_AnimBlendBufApplyToModel_171430 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 unk0;
    s32 *unk4;
} Obj104_00171430;

typedef struct {
    u8 pad0[0x104];
    Obj104_00171430 *unk104;
    u8 pad108[0x120 - 0x108];
    u8 unk120[4];
} Obj00171430_1;

typedef struct {
    s32 unk0;
    u8 *unk4;
    u8 pad8[0xC - 8];
    u8 *unkC;
} Obj00171430_0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void AnimBlendBufApplyToModel_171430(Obj00171430_0 *arg0, Obj00171430_1 *arg1) {
    Obj104_00171430 *o;
    s32 n;
    s32 m;
    s32 i;
    s32 v;

    if (arg0 == NULL || arg1 == NULL) return;
    o = arg1->unk104;
    if (o == NULL) return;
    m = (n = o->unk0, ArrayGetCountIndirect_1527c0(arg1->unk120));
    for (i = 0; i < n; i++) {
        v = o->unk4[i];
        if (v == 0) continue;
        AnimSlotApplyToFrame_154580(arg0->unk4 + i * 0x60, v);
    }
    for (i = 0; i < m; i++) {
        v = ArrayGetCheckedIndirect_1527e0(arg1->unk120, i);
        if (v == 0) continue;
        AnimSlotApplyToMaterial_154540(arg0->unkC + i * 0x30, v);
    }
}
