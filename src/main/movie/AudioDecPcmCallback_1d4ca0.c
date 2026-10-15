#include "types.h"

typedef struct T1d2550 {
    s32 unk0;
    u8 buf[0x28];
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} T1d2550;

static void AudioDecBeginPut_1d2550(T1d2550 *a, void **p1, s32 *n1, s32 *p2, s32 *n2)
{
    s32 end;
    s32 t2;
    s32 t1;

    if (a->unk0 == 0) {
        *p1 = (u8 *)(a->unk2C + (s32)a + 4);
        *n1 = 0x28 - a->unk2C;
        *p2 = a->unk30;
        *n2 = a->unk3C;
        return;
    }
    end = a->unk3C;
    t2 = end - a->unk38;
    t1 = a->unk34;
    if (end - t1 >= t2) {
        *p1 = (void *)(a->unk30 + t1);
        *n1 = t2;
        *p2 = 0;
        *n2 = 0;
    } else {
        *p1 = (void *)(a->unk30 + t1);
        *n1 = a->unk3C - a->unk34;
        *p2 = a->unk30;
        *n2 = t2 - (a->unk3C - a->unk34);
    }
}


typedef struct Arg1_001d4ca0 {
    u8 pad0[0x8];
    u32 unk8;
    u32 unkC;
} Arg1_001d4ca0;

typedef struct Arg2_001d4ca0 {
    u8 pad0[0x14008];
    s32 unk14008;
} Arg2_001d4ca0;

extern s32 Copy2Area_1d2610(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u32 arg4, s32 arg5, void *arg6, s32 arg7);
extern s32 AudioDecEndPut_1d24c0(void *arg0, s32 arg1);
extern u8 D_004B32D0[];

s32 AudioDecPcmCallback_1d4ca0(void *unused0, Arg1_001d4ca0 *arg1, Arg2_001d4ca0 *arg2)
{
    void *p1;
    s32 p2;
    s32 n1;
    s32 n2;
    s32 cap;
    u32 bufEnd;
    u32 writePos;
    s32 limit;
    s32 amt;

    writePos = arg1->unk8 + 4;
    cap = arg2->unk14008;
    bufEnd = (u32)((u8 *)arg2 + cap);
    if (writePos >= bufEnd) {
        writePos -= cap;
    }
    limit = (s32)arg1->unkC - 4;
    amt = limit < (s32)(bufEnd - writePos) ? limit : (s32)(bufEnd - writePos);
    AudioDecBeginPut_1d2550((T1d2550 *)D_004B32D0, &p1, &n1, &p2, &n2);
    return AudioDecEndPut_1d24c0(D_004B32D0,
        Copy2Area_1d2610((s32)p1, n1, p2, n2, writePos, amt, arg2, limit - amt)) > 0;
}
