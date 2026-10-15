#include "types.h"

extern void MemStackAlign64_14d8e0(s32 arg0);
extern s32 MemStackNew_14e1b0(s32 arg0, s32 arg1);
extern void ScriptVmInitWithCmdTable_250c80(s32 arg0, void *arg1);
extern void *memset(void *arg0, s32 arg1, s32 arg2);
extern u8 D_0044CEA0[0x400];
extern u8 D_004BCEC0[0x400];

typedef struct {
    s32 a0;
    s32 a4;
    s32 a8;
    s32 aC;
    s32 a10;
    void *a14;
    void *a18;
    s32 a1C;
} P;

void EventScriptVmInit_23ffa0(s32 arg0, s32 arg1, s32 arg2)
{
    P sp50;
    s32 temp_16;
    s32 temp_17;

    if (arg0 == 0 || arg1 == 0 || arg2 == 0) {
        return;
    }
    MemStackAlign64_14d8e0(arg2);
    temp_17 = MemStackNew_14e1b0(0x280, arg2);
    temp_16 = MemStackNew_14e1b0(0x30, arg2);
    memset(&sp50, 0, 0x20);
    sp50.a0 = arg1;
    sp50.a4 = temp_17;
    sp50.a8 = 0x50;
    sp50.aC = temp_16;
    sp50.a10 = 4;
    sp50.a14 = D_0044CEA0;
    sp50.a18 = D_004BCEC0;
    sp50.a1C = 0xE9;
    ScriptVmInitWithCmdTable_250c80(arg0, &sp50);
}
