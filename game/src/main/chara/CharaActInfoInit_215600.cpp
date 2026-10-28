#include "types.h"

typedef struct {
    u8 pad0[0x90];
    s32 unk90;
    u8 unk94;
    u8 pad95[0xB4 - 0x95];
    s32 unkB4;
} E00215600;

typedef struct {
    s32 unk0;
    E00215600 *unk4;
    s32 unk8;
} S00215600;

typedef struct {
    u8 pad0[0x7A];
    s16 unk7A;
} A00215600;

extern "C" {
extern E00215600 *ConstructNewArray_100710(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 MemStackNew_14e1b0(s32 arg0, s32 arg1);
extern void SwordTrailReset_2d7630(E00215600 *arg0);
extern void SwordTrailAlloc_2d7650(E00215600 *arg0, s32 arg1, s32 arg2);
extern void TargetRefClear_2e71d0(void *arg0);
extern void SwordTrailCtor_215760(void);
}

static inline bool setup00215600(E00215600 *e, s32 arg3)
{
    if (arg3 == 0) {
        return false;
    }
    SwordTrailAlloc_2d7650(e, arg3, 0x14);
    return true;
}

extern "C" s32 CharaActInfoInit_215600(S00215600 *arg0, s32 arg1, A00215600 *arg2, s32 arg3)
{
    s32 i;
    s32 n;
    E00215600 *e;

    arg0->unk0 = 0;
    arg0->unk4 = 0;
    arg0->unk8 = 0;
    if (arg1 == 0 || arg2 == NULL || arg3 == 0) {
        return 0;
    }
    n = arg2->unk7A;
    arg0->unk4 = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0xB8 + 0x10, arg3), (void *)SwordTrailCtor_215760, 0, 0xB8, n);
    if (arg0->unk4 != NULL && n > 0) {
        for (i = 0; i < n; i++) {
            e = (E00215600 *)((u8 *)arg0->unk4 + i * 0xB8);
            SwordTrailReset_2d7630(e);
            TargetRefClear_2e71d0((u8 *)e + 0x30);
            TargetRefClear_2e71d0((u8 *)e + 0x60);
            e->unk90 = -1;
            e->unk94 = 0;
            e->unkB4 = 0;
            if (!setup00215600(e, arg3)) {
                return 0;
            }
        }
        arg0->unk8 = n;
    }
    arg0->unk0 = arg1;
    return 1;
}
