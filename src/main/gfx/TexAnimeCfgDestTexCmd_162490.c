#include "types.h"

extern s16 *NameTableFindByName_159fb0(s32, s32, s32);
extern s32 SlotGetInt_15f720(s32);
extern s32 VariantGetInt_15f780(s32);
extern s32 D_00481138;
extern s32 D_00481148;
extern s16 *D_00495E78[];
extern s16 D_00495E80[];
extern s16 D_00495E82[];
extern s16 D_00495E84[];
extern s16 D_00495E86[];
extern s16 D_00495E88[];
extern s16 D_00495E8A[];
extern s8 D_00495EA0[];

s32 TexAnimeCfgDestTexCmd_162490(s64 *arg0, s32 arg1)
{
    s32 v;

    v = SlotGetInt_15f720((s32)arg0++);
    if (v == 0) {
        return 0;
    }
    D_00495E78[0] = NameTableFindByName_159fb0(D_00481138, v, -1);
    D_00495E84[0] = VariantGetInt_15f780((s32)arg0++) << 4;
    D_00495E86[0] = VariantGetInt_15f780((s32)arg0++) << 4;
    if (arg1 > 3) {
        D_00495E88[0] = VariantGetInt_15f780((s32)arg0++) << 4;
        D_00495E8A[0] = VariantGetInt_15f780((s32)arg0++) << 4;
        if (arg1 > 5) {
            D_00495EA0[0] = VariantGetInt_15f780((s32)arg0);
        }
    } else {
        D_00495E88[0] = D_00495E80[0];
        D_00495E8A[0] = D_00495E82[0];
    }
    if (D_00495E78[0] != NULL && D_00481148 < 0) {
        D_00481148 = *D_00495E78[0];
    }
    return 1;
}
