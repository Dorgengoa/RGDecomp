#include "types.h"

typedef struct {
    s32 status;
    void *func;
    void *stack;
    s32 stack_size;
    void *gp_reg;
    s32 initial_priority;
    s32 current_priority;
    u32 attr;
    u32 option;
} ThreadParam00182AF0;

typedef struct {
    s32 count;
    s32 max_count;
    s32 init_count;
    s32 wait_threads;
    u32 attr;
    u32 option;
} SemaParam00182AF0;

typedef struct {
    u8 pad0[0x120];
    s32 unk120;
    u8 pad124[4];
} Slot00182AF0;

extern s32 CreateSema(SemaParam00182AF0 *arg0);
extern s32 CreateThread(ThreadParam00182AF0 *arg0);
extern s32 DeleteSema(s32 arg0);
extern void StartThread_1176e0(s32 arg0, s32 *arg1);
extern void FileReqThread_182c30(void);
extern s32 D_0047E01C;
extern s32 D_0047E020;
extern s32 D_0047E024;
extern s32 D_004811E8;
extern s32 D_004811EC;
extern s32 D_004811F0;
extern s32 D_004811F4;
extern s32 D_004811F8;
extern s32 D_004811FC;
extern s32 D_00481200;
extern s32 D_00481204;
extern u8 D_00485170;
extern Slot00182AF0 D_00495FD0[0x20];
extern u8 D_00498500[0x400];

s32 FileReqThreadInit_182af0(s32 arg0)
{
    SemaParam00182AF0 sp;
    ThreadParam00182AF0 tp;
    s32 i;

    if (D_004811F4 != 0) {
        return 0;
    }
    for (i = 0; i < 0x20; i++) {
        D_00495FD0[i].unk120 = 0;
    }
    D_004811EC = -1;
    D_004811F0 = 0;
    sp.max_count = 1;
    D_004811E8 = 0;
    sp.init_count = 0;
    sp.option = 0;
    D_0047E020 = CreateSema(&sp);
    if (D_0047E020 < 0) {
        return 0;
    }
    D_0047E024 = CreateSema(&sp);
    if (D_0047E024 < 0) {
        DeleteSema(D_0047E020);
        return 0;
    }
    tp.stack_size = 0x2000;
    tp.initial_priority = arg0;
    tp.gp_reg = &D_00485170;
    tp.func = FileReqThread_182c30;
    tp.stack = D_00498500;
    D_00481200 = arg0;
    D_0047E01C = CreateThread(&tp);
    if (D_0047E01C < 0) {
        DeleteSema(D_0047E020);
        return 0;
    }
    D_00481204 = 0;
    D_004811F4 = 1;
    D_004811F8 = 1;
    D_004811FC = 0;
    D_004811E8 = 0;
    StartThread_1176e0(D_0047E01C, &D_0047E020);
    return 1;
}
