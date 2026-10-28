/* rgp:protos */
#define RGP_SELF_StateFlag2SetQuiet_3cc7d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Console { u8 pad00[0xC]; void *out; } Console;
typedef struct Self { u8 pad00[0x228]; u8 arr; } Self;

extern Console *const volatile D_00449858;
extern char D_00466470[];
extern void Fprintf_12f9a0(void *out, const char *fmt);
/*rgp*/
/*rgp*/

s32 StateFlag2SetQuiet_3cc7d0(Self *self, s32 idx, void *arg)
{
    volatile s32 pi;
    void *volatile pa;
    u32 n;

    if (idx < 0 || idx >= 0x800) {
        return 0;
    }
    n = (u32)idx;
    pa = &self->arr;
    pi = idx;
    if (n >= 0x800) {
        Fprintf_12f9a0(D_00449858->out, D_00466470);
        Abort_12de80();
    }
    BitsetAssignBit_3cded0(pa, n, arg);
    return 1;
}
