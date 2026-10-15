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
extern const char D_00466440[];

extern void Fprintf_12f9a0(void *out, const char *fmt);
extern void Abort_12de80(void);
extern s32  BitsetTestBit_3cdea0(void *p, s32 i);

s32 Bitset256Test_3cc650(void *o, s32 i)
{
    Ref  r;
    Ref *rp;
    s32  idx;

    if (i < 0 || i >= 0x100) return 0;
    rp = &r;
    rp->p = (u8 *)o + 0x328;
    rp->i = i;
    idx = rp->i;
    if ((u32)idx >= 0x100) {
        Fprintf_12f9a0(D_00449858->out, D_00466440);
        Abort_12de80();
    }
    return BitsetTestBit_3cdea0(rp->p, idx);
}
