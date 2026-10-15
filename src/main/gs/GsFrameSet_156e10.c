#include "types.h"

typedef struct {
    u8 pad0[0x50];
    union {
        u64 all;
        struct {
            u64 lo : 32;
            u64 hi : 32;
        } b;
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
