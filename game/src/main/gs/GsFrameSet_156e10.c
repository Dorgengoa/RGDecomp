/* rgp:protos */
#define RGP_SELF_GsFrameSet_156e10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x50];
    union {
        u64 all;
        struct {
            __extension__ unsigned int lo : 32;
            unsigned int  : 0, hi : 32;
        } __attribute__((aligned(8))) b;
    } unk50;
    u8 pad58[0x5C - 0x58];
    s32 unk5C;
} Obj00156e10;

void GsFrameSet_156e10(Obj00156e10 *arg0, u64 *arg1)
{
    int old;

    if (arg0->unk5C == -1) {
        arg0->unk50.all = *arg1;
    } else {
        old = arg0->unk50.b.hi;
        arg0->unk50.all = *arg1;
        arg0->unk50.b.hi = old;
    }
}
