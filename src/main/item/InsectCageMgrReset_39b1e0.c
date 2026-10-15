#include "types.h"

typedef struct Struct0039b1e0 {
    u8 pad0[0x90];
    s32 unk90;
    u8 pad94[0xA2 - 0x94];
    u8 unkA2;
    u8 padA3[0xB0 - 0xA3];
    s32 unkB0;
    s32 unkB4;
    s32 unkB8;
    f32 unkBC;
    s32 unkC0;
    s32 unkC4;
    s32 unkC8;
    f32 unkCC;
    s32 unkD0;
    s32 unkD4;
    s32 unkD8;
    f32 unkDC;
    s32 unkE0;
    s32 unkE4;
    s32 unkE8;
    f32 unkEC;
    s32 unkF0;
    s32 unkF4;
} Struct0039b1e0;

extern void InsectCageMgrClearIds_39b030(Struct0039b1e0 *a);
extern void InsectCageSlotReset_39bb10(void *a);

void InsectCageMgrReset_39b1e0(u8 *arg0)
{
    s32 var_17;

    var_17 = 0;
    do {
        InsectCageSlotReset_39bb10(arg0 + (var_17 * 0x30));
        var_17 += 1;
    } while (var_17 < 3);
    ((Struct0039b1e0 *) arg0)->unk90 = 0;
    ((Struct0039b1e0 *) arg0)->unkA2 = 0;
    ((Struct0039b1e0 *) arg0)->unkF0 = -1;
    ((Struct0039b1e0 *) arg0)->unkF4 = 0;
    ((Struct0039b1e0 *) arg0)->unkB0 = 0;
    ((Struct0039b1e0 *) arg0)->unkB4 = 0;
    ((Struct0039b1e0 *) arg0)->unkB8 = 0;
    ((Struct0039b1e0 *) arg0)->unkBC = 1.0f;
    ((Struct0039b1e0 *) arg0)->unkC0 = 0;
    ((Struct0039b1e0 *) arg0)->unkC4 = 0;
    ((Struct0039b1e0 *) arg0)->unkC8 = 0;
    ((Struct0039b1e0 *) arg0)->unkCC = 1.0f;
    ((Struct0039b1e0 *) arg0)->unkD0 = 0;
    ((Struct0039b1e0 *) arg0)->unkD4 = 0;
    ((Struct0039b1e0 *) arg0)->unkD8 = 0;
    ((Struct0039b1e0 *) arg0)->unkDC = 1.0f;
    ((Struct0039b1e0 *) arg0)->unkE0 = 0;
    ((Struct0039b1e0 *) arg0)->unkE4 = 0;
    ((Struct0039b1e0 *) arg0)->unkE8 = 0;
    ((Struct0039b1e0 *) arg0)->unkEC = 1.0f;
    InsectCageMgrClearIds_39b030((Struct0039b1e0 *) arg0);
}
