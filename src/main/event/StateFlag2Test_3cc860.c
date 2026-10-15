#include "types.h"

typedef struct Console {
    u8    pad00[0xC];
    void *out;         /* +0x0C */
} Console;

typedef struct Ref {
    void *p;
    s32   i;
} Ref;

extern Console *const volatile D_00449858;
extern const char D_004664A0[];

extern void Fprintf_12f9a0(void *out, const char *fmt);
extern void Abort_12de80(void);
extern s32  BitsetTestBit_3cdf20(void *p, s32 i);

s32 StateFlag2Test_3cc860(void *o, s32 i)
{
    Ref  r;
    Ref *rp;
    s32  idx;

    if (i < 0 || i >= 0x800) return 0;
    rp = &r;
    rp->p = (u8 *)o + 0x228;
    rp->i = i;
    idx = rp->i;
    if ((u32)idx >= 0x800) {
        Fprintf_12f9a0(D_00449858->out, D_004664A0);
        Abort_12de80();
    }
    return BitsetTestBit_3cdf20(rp->p, idx);
}
