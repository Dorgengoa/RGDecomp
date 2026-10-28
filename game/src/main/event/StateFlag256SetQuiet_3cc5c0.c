/* rgp:protos */
#define RGP_SELF_StateFlag256SetQuiet_3cc5c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Console { u8 pad00[0xC]; void *out; } Console;
typedef struct Self { u8 pad00[0x328]; u8 arr; } Self;

extern Console *const volatile D_00449858;
extern char D_00466410[];
extern void Fprintf_12f9a0(void *out, const char *fmt);
/*rgp*/
/*rgp*/

s32 StateFlag256SetQuiet_3cc5c0(Self *self, s32 idx, void *arg)
{
    volatile s32 pi;
    void *volatile pa;
    u32 n;

    if (idx < 0 || idx >= 0x100) {
        return 0;
    }
    n = (u32)idx;
    pa = &self->arr;
    pi = idx;
    if (n >= 0x100) {
        Fprintf_12f9a0(D_00449858->out, D_00466410);
        Abort_12de80();
    }
    BitsetAssignBit_3cde50(pa, n, arg);
    return 1;
}
