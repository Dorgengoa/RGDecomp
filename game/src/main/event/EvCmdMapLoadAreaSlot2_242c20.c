/* rgp:protos */
#define RGP_SELF_EvCmdMapLoadAreaSlot2_242c20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

typedef struct S34 {
    s32 unk0[4];
    void *unk10;
    s32 unk14[8];
} S34;

extern void Sprintf_1343b8(void *, void *, void *);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045EA78[];

s32 EvCmdMapLoadAreaSlot2_242c20(s64 *arg0, s32 arg1)
{
    u8 sp80[0x20] __attribute__((aligned(16)));
    S34 sp40 __attribute__((aligned(16)));
    S34 *var_18;
    s32 temp_16;
    void *temp_18;
    s32 t;

    if (arg1 != 2) {
        return 0;
    }
    temp_16 = ((s32)GetMapMgr_201a90());
    temp_18 = GetGameData_1fede0();
    t = ScriptGetCodeAddr_249050((s32)arg0++);
    var_18 = ((S34 *)TableFindByName_416b00(S32(PTR(PTR(temp_18, 8), 0x34), 8), t));
    if (var_18 != NULL) {
        Sprintf_1343b8(sp80, D_0045EA78, var_18->unk10);
        sp40 = *var_18;
        sp40.unk10 = sp80;
        MapMgrLoadAreaSlot2_1e30f0(temp_16, &sp40, 0, ScriptGetInt_2490f0((s32)arg0));
    }
    return 1;
}
