#include "types.h"

typedef struct Console {
    u8 pad00[0x8];
    void *unk08;
    void *out;
} Console;

typedef struct H {
    void *a;
    s32   i;
} H;

typedef struct Self {
    u8 pad00[0x228];
    u8 arr;
} Self;

extern Console *const volatile D_00449858;
extern const char D_004664A0[];
extern const char D_00466470[];
extern void Fprintf_12f9a0(void *out, const char *fmt);
extern void Abort_12de80(void);
extern s32  BitsetTestBit_3cdf20(void *arr, s32 i);
extern void BitsetAssignBit_3cded0(void *arr, s32 i, void *a);
extern void *D_004838C0;
extern void WorldOnStateFlag2Changed_3ed9a0(void *h, s32 i, void *a, u8 v);

s32 StateFlag2Set_3cc6d0(Self *self, s32 idx, void *arg)
{
    H h1;
    H h2;
    H *q1 = &h1;
    H *q2 = &h2;
    u8 v;

    if (idx < 0 || idx >= 0x800) {
        return 0;
    }
    h1.a = &self->arr;
    h1.i = idx;
    if (0x800 <= (u32)idx) {
        Fprintf_12f9a0(D_00449858->out, D_004664A0);
        Abort_12de80();
    }
    v = BitsetTestBit_3cdf20(q1->a, idx);
    h2.a = &self->arr;
    h2.i = idx;
    if (0x800 <= (u32)idx) {
        Fprintf_12f9a0(D_00449858->out, D_00466470);
        Abort_12de80();
    }
    BitsetAssignBit_3cded0(q2->a, idx, arg);
    if (D_004838C0 != NULL) {
        WorldOnStateFlag2Changed_3ed9a0(D_004838C0, idx, arg, v);
    }
    return 1;
}
