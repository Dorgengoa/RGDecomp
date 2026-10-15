#include "types.h"

extern s32 SlotGetInt_15f720(s32);
extern s32 strlen(s32);
extern s32 BytesToQwords_18a6c0(s32);
extern s32 MemStackAllocQw_14d950(s32, s32);
extern void strcpy(s32, s32);

extern s32 D_0048125C;

struct Obj0 {
    u8 pad000[0x3C];
    s32 m3C;
};

extern struct Obj0 *D_004812D8;

s32 MapCfgFuncName_18b000(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;

    if (D_004812D8 == 0) {
        return 0;
    }
    r0 = SlotGetInt_15f720(p0);
    if (r0 == 0) {
        return 0;
    }
    r1 = strlen(r0);
    r2 = BytesToQwords_18a6c0((r1 + 1));
    r3 = MemStackAllocQw_14d950(D_0048125C, r2);
    if (r3 != 0) {
        strcpy(r3, r0);
    }
    D_004812D8->m3C = r3;
    return 1;
}
