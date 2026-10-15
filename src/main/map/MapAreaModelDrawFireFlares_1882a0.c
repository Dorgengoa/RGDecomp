#include "types.h"

void MtxIdentity_13d2e0(void *);
void DrawListAddTexLoad_1418c0(s32, s32, f32);
void GetDrawCtxNameTable_15de40(void);
s32 GetDrawCtx_15de80(void);
f32 TimeOfDayGetHour_18d920(void);
typedef struct { f32 f; s32 x; } P98;
void FuncDataTableDrawFireFlaresMaybe_18eb30(void *, void *, P98 *, s32, s32, f32);
void NodeCalcWorldMatrixThunk_186130(void *, void *);

void MapAreaModelDrawFireFlares_1882a0(u8 *arg0, s32 arg1)
{
    P98 sp98;
    u8 sp50[0x40];
    s32 id;
    u8 **list;
    s32 *pc;
    s32 i;
    u8 *e;

    sp98.f = 0.0f;
    sp98.f = TimeOfDayGetHour_18d920();
    sp98.x = *(s32 *)(arg0 + 0x1678);
    id = GetDrawCtx_15de80();
    GetDrawCtxNameTable_15de40();
    DrawListAddTexLoad_1418c0(id, arg1, 1.0f);
    list = *(u8 ***)(arg0 + 0x58C);
    pc = (s32 *)(arg0 + 0x580);
    MtxIdentity_13d2e0(sp50);
    FuncDataTableDrawFireFlaresMaybe_18eb30(sp50, arg0 + 0x1664, &sp98, 0, 0, 1.0f);
    if (list != NULL) {
        for (i = 0; i < *pc; i++, list++) {
            e = *list;
            if (*(s32 *)(e + 0x114) & 2) {
                NodeCalcWorldMatrixThunk_186130(e, sp50);
                FuncDataTableDrawFireFlaresMaybe_18eb30(sp50, e + 0x114, &sp98, 0, 0, 1.0f);
            }
        }
    }
}
