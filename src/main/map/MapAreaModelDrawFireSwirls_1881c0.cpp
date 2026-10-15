#include "types.h"
#pragma opt_propagation off
extern "C" {

typedef struct {
    f32 a;
    s32 b;
} Pair_1881c0;

typedef struct {
    s32 count;
    u8 pad4[8];
    u8 **list;
} Sub580_1881c0;

typedef struct {
    u8 pad0[0x580];
    Sub580_1881c0 sub;
    u8 pad590[0x1664 - 0x590];
    u8 unk1664[0x14];
    s32 unk1678;
    s32 unk167C;
} Obj_1881c0;

extern void MtxIdentity_13d2e0(void *);
extern f32 TimeOfDayGetHour_18d920(void);
extern void FuncDataTableDrawFireSwirls_18e900(void *, void *, Pair_1881c0 *, s32);
extern void NodeCalcWorldMatrixThunk_186130(void *, void *);

void MapAreaModelDrawFireSwirls_1881c0(Obj_1881c0 *arg0)
{
    u8 **var_19;
    Pair_1881c0 spA8;
    u8 sp60[0x40];
    s32 var_18;
    u8 *temp_16;
    Sub580_1881c0 *sub;

    spA8.a = 0.0f;
    spA8.a = TimeOfDayGetHour_18d920();
    spA8.b = arg0->unk1678;
    sub = &arg0->sub;
    var_19 = sub->list;
    MtxIdentity_13d2e0(sp60);
    FuncDataTableDrawFireSwirls_18e900(sp60, arg0->unk1664, &spA8, arg0->unk167C);
    if (var_19 != NULL) {
        for (var_18 = 0; var_18 < sub->count; var_18++, var_19++) {
            temp_16 = *var_19;
            bool z = *(s8 *)(temp_16 + 0x6C) == 0;
            if (!z) {
                NodeCalcWorldMatrixThunk_186130(temp_16, sp60);
                FuncDataTableDrawFireSwirls_18e900(sp60, temp_16 + 0x114, &spA8, arg0->unk167C);
            }
        }
    }
}

}
