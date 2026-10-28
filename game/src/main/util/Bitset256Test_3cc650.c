/* rgp:protos */
#define RGP_SELF_Bitset256Test_3cc650 1
#include "port/game_protos.h"
#line 1
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
extern char D_00466440[];

extern void Fprintf_12f9a0(void *out, const char *fmt);
/*rgp*/
/*rgp*/

s32 Bitset256Test_3cc650(void *o, s32 i)
{
    Ref  r __attribute__((aligned(16)));
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
    return ((unsigned char)BitsetTestBit_3cdea0(rp->p, idx));
}
