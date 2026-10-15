#include "types.h"

struct ThreadParam {
    s32 status;
    void *entry;
    void *stack;
    s32 stackSize;
    void *gpReg;
    s32 initPriority;
    s32 currentPriority;
    u32 attr;
    u32 option;
};

extern s32 CreateThread(struct ThreadParam *);
extern s32 AddIntcHandler(s32, void *, s32);
extern s32 AddDmacHandler(s32, void *, s32);
extern s32 EnableIntc_1170e8(s32);
extern s32 EnableDmac_1171b8(s32);
extern s32 StartThread_1176e0(s32, void *);
extern s32 AudioDecSetInputVolume_1d2b90(s32);
extern s32 MovieSetTargetTexByName_1d5650(void *, s32);
extern s32 D_0047DF30;
extern s32 D_00485170;
extern s32 D_004817E4;
extern u8 D_004B3210[0x400];
extern s32 D_004B32C0[0x10];
extern s32 D_004B32C4[0x10];
extern void MovieReadThread_1d4f50(void);
extern void VideoDecMain_1d5240(void);
extern void DefMain_1d52b0(void);
extern void MovieDmacHandler_1d4b10(void);
extern void MovieVblankHandler_1d4c90(void);

void MoviePlayerStart_1d5b50(u8 *arg0, s32 arg1)
{
    struct ThreadParam tp;
    s32 id;

    if (*(u8 *)(arg0 + 0x17900) == 0) {
        AudioDecSetInputVolume_1d2b90(0);
        MovieSetTargetTexByName_1d5650(arg0, arg1);
        tp.option = 0;
        tp.entry = (void *)DefMain_1d52b0;
        tp.stack = arg0 + 0x100;
        tp.stackSize = 0x800;
        tp.gpReg = &D_00485170;
        tp.initPriority = D_0047DF30;
        id = CreateThread(&tp);
        *(s32 *)(arg0 + 0x17908) = id;
        StartThread_1176e0(id, NULL);
        tp.option = 0;
        tp.entry = (void *)VideoDecMain_1d5240;
        tp.stack = arg0 + 0x900;
        tp.stackSize = 0x4000;
        tp.gpReg = &D_00485170;
        tp.initPriority = D_0047DF30;
        id = CreateThread(&tp);
        *(s32 *)(arg0 + 0x17904) = id;
        StartThread_1176e0(id, D_004B3210);
        D_004817E4 = 0;
        tp.entry = (void *)MovieReadThread_1d4f50;
        tp.option = 0;
        tp.stack = arg0 + 0x4900;
        tp.stackSize = 0x4000;
        tp.gpReg = &D_00485170;
        tp.initPriority = D_0047DF30;
        id = CreateThread(&tp);
        *(s32 *)(arg0 + 0x1790C) = id;
        StartThread_1176e0(id, NULL);
        D_004B32C4[0] = AddIntcHandler(2, (void *)MovieVblankHandler_1d4c90, 0);
        EnableIntc_1170e8(2);
        D_004B32C0[0] = AddDmacHandler(2, (void *)MovieDmacHandler_1d4b10, 0);
        EnableDmac_1171b8(2);
        *(u8 *)(arg0 + 0x17900) = 1;
    }
}
