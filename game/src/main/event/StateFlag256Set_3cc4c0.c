/* rgp:protos */
#define RGP_SELF_StateFlag256Set_3cc4c0 1
#include "port/game_protos.h"
#line 1
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
    u8 pad00[0x328];
    u8 arr;
} Self;

extern Console *const volatile D_00449858;
extern char D_00466440[];
extern char D_00466410[];
extern void Fprintf_12f9a0(void *out, const char *fmt);
/*rgp*/
/*rgp*/
/*rgp*/
extern void *D_004838C0;
/*rgp*/

s32 StateFlag256Set_3cc4c0(Self *self, s32 idx, void *arg)
{
    H h1 __attribute__((aligned(16)));
    H h2 __attribute__((aligned(16)));
    H *q1 = &h1;
    H *q2 = &h2;
    u8 v;

    if (idx < 0 || idx >= 0x100) {
        return 0;
    }
    h1.a = &self->arr;
    h1.i = idx;
    if (0x100 <= (u32)idx) {
        Fprintf_12f9a0(D_00449858->out, D_00466440);
        Abort_12de80();
    }
    v = ((unsigned char)BitsetTestBit_3cdea0(q1->a, idx));
    h2.a = &self->arr;
    h2.i = idx;
    if (0x100 <= (u32)idx) {
        Fprintf_12f9a0(D_00449858->out, D_00466410);
        Abort_12de80();
    }
    BitsetAssignBit_3cde50(q2->a, idx, arg);
    if (D_004838C0 != NULL) {
        WorldOnStateFlag256Changed_3ed930(D_004838C0, idx, arg, v);
    }
    return 1;
}
