#include "types.h"

typedef struct G00189f40 {
    u8 pad0[0x60];
    s32 unk60;
    s32 unk64;
    s32 unk68;
} G00189f40;

extern s8 *SlotGetInt_15f720(s32);
extern s32 VariantGetInt_15f780(s32);
extern s32 strcmp(const s8 *, const s8 *);
extern s8 D_00459C38[];
extern s8 D_00459C40[];
extern s8 D_00459C48[];
extern s8 D_00459C50[];
extern s8 D_00459C58[];
extern G00189f40 *D_004812DC;

s32 MapCfgFuncEventData_189f40(s64 *arg0, s32 arg1)
{
    s8 *s;

    if (D_004812DC == NULL) {
        return 0;
    }
    D_004812DC->unk68 = VariantGetInt_15f780((s32)arg0++);
    if (arg1 > 1) {
        s = SlotGetInt_15f720((s32)arg0);
        D_004812DC->unk64 = 0;
        if (s != NULL) {
            if (strcmp(s, D_00459C38) == 0) {
                D_004812DC->unk60 = 1;
            } else if (strcmp(s, D_00459C40) == 0) {
                D_004812DC->unk60 = 2;
            } else if (strcmp(s, D_00459C48) == 0) {
                D_004812DC->unk60 = 2;
                D_004812DC->unk64 = 1;
            } else if (strcmp(s, D_00459C50) == 0) {
                D_004812DC->unk60 = 4;
                D_004812DC->unk64 = 1;
            } else if (strcmp(s, D_00459C58) == 0) {
                D_004812DC->unk60 = 2;
                D_004812DC->unk64 = 2;
            } else {
                return 0;
            }
        }
    }
    return 1;
}
