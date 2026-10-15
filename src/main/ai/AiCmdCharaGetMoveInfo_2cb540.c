#include "types.h"

typedef struct T002cb540 {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[4];
    f32 unkC;
} T002cb540;

extern s32 CharaGetActionTable_214cd0(s32 arg0);
extern T002cb540 *ActCfgTableFindMoveById_223080(s32 arg0, s32 arg1);
extern void ScriptSlotStoreFloatRef_2cc8e0(s32 arg0, f32 arg1);
extern s32 ScriptSlotGetInt_2cc9c0(s32 arg0);
extern s32 D_004DB92C[];

s32 AiCmdCharaGetMoveInfo_2cb540(s64 *arg0, s32 arg1)
{
    s32 g;
    T002cb540 *t;

    if (arg1 == 3) {
        g = CharaGetActionTable_214cd0(D_004DB92C[0]);
        if (g == 0) {
            return 0;
        }
        t = NULL;
        switch (ScriptSlotGetInt_2cc9c0((s32)arg0++)) {
        case 0:
            t = ActCfgTableFindMoveById_223080(g, 0x65);
            break;
        case 1:
            t = ActCfgTableFindMoveById_223080(g, 0x67);
            break;
        case 2:
            t = ActCfgTableFindMoveById_223080(g, 0x66);
            break;
        }
        if (t == NULL) {
            return 0;
        }
        ScriptSlotStoreFloatRef_2cc8e0((s32)arg0++, t->unkC);
        ScriptSlotStoreFloatRef_2cc8e0((s32)arg0, t->unk4);
    }
    return 1;
}
