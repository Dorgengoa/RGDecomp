#include "types.h"

extern void MemStackAlign64_14d8e0(s32 arg0);
extern s32 MemStackAllocQw_14d950(s32 arg0, s32 arg1);
extern s32 MemStackNew_14e1b0(s32 arg0, s32 arg1);
extern void SaveDirListClear_373330(void *arg0);
extern void SaveSlotEntriesClear_373590(void *arg0);
extern void SaveResultClear_3761b0(void *arg0);
extern void McCardInfoClear_3761d0(void *arg0);
extern void SaveSysResultCbMaybe_373e10(void);
extern const s32 D_004658F8;
extern void (*D_0047FAA4)(void);
extern s32 D_00483188;
extern s32 D_0048318C;

void SaveSysInit_375ef0(void *arg0, s32 arg1) {
    s32 var_16;

    *(u16 *)((u8 *)arg0 + 0xDC) = 0;
    var_16 = 0;
    do {
        McCardInfoClear_3761d0((u8 *)arg0 + (var_16 * 0x1C) + 0x4A4);
        var_16 += 1;
    } while (var_16 < 2);
    SaveSlotEntriesClear_373590(arg0);
    *(s32 *)((u8 *)arg0 + 0x4DC) = 1;
    *(s32 *)((u8 *)arg0 + 0x4E4) = 0x3D;
    *(s32 *)((u8 *)arg0 + 0x4E0) = 0;
    *(s32 *)((u8 *)arg0 + 0x4E8) = -1;
    *(u16 *)((u8 *)arg0 + 0x4EC) = 0;
    *(u16 *)((u8 *)arg0 + 0x4EE) = 0;
    *(u16 *)((u8 *)arg0 + 0x4FC) = 0;
    *(s32 *)((u8 *)arg0 + 0x510) = D_004658F8;
    SaveResultClear_3761b0((u8 *)arg0 + 0x4F0);
    MemStackAlign64_14d8e0(arg1);
    *(s32 *)((u8 *)arg0 + 0x50C) = MemStackAllocQw_14d950(arg1, 0x2000);
    MemStackAlign64_14d8e0(arg1);
    *(s32 *)((u8 *)arg0 + 0x500) = MemStackNew_14e1b0(0xC80, arg1);
    SaveDirListClear_373330(arg0);
    MemStackAlign64_14d8e0(arg1);
    *(s32 *)((u8 *)arg0 + 0x504) = MemStackNew_14e1b0(0x180, arg1);
    MemStackAlign64_14d8e0(arg1);
    *(s32 *)((u8 *)arg0 + 0x508) = MemStackNew_14e1b0(0x240, arg1);
    D_00483188 = 0;
    D_0047FAA4 = SaveSysResultCbMaybe_373e10;
    D_0048318C = 0;
}
