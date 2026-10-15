#include "types.h"

typedef struct {
    u8 pad10[0x10];
    s32 unk10;
} Ctx;

extern void MapMgrSetHeap_1e33f0(s32 a, s32 b);
extern Ctx *GetGameData_1fede0(void);
extern s32 GetMapMgr_201a90(void);
extern s32 GetMapHeap_201aa0(void);
extern void RecStackSlotRelease_201d10(s32 a, void *b);
extern void RecStackHeapSlotRelease_201ea0(s32 a, void *b);
extern void FactoryReset_367e80(void);
extern s32 FactoryGetMapHeap_367f00(void);
extern s32 FactoryGetHeap_367f10(void);
extern s32 GetFactoryObj_367f30(void);
extern void func_5032D0(s32 a, s32 b, s32 c);
extern void func_504850(s32 a);
extern u8 D_004830EC;
extern u8 D_004830F4;

void FactoryTerm_367c00(void) {
    s32 temp_16;
    s32 temp_2;

    temp_2 = GetFactoryObj_367f30();
    if (temp_2 != 0) {
        func_5032D0(temp_2, GetGameData_1fede0()->unk10 + 0xAA0, 0xC00);
        RecStackSlotRelease_201d10(FactoryGetHeap_367f10(), &D_004830EC);
        func_504850(temp_2);
        temp_16 = GetMapMgr_201a90();
        MapMgrSetHeap_1e33f0(temp_16, GetMapHeap_201aa0());
        RecStackHeapSlotRelease_201ea0(FactoryGetMapHeap_367f00(), &D_004830F4);
        FactoryReset_367e80();
    }
}
