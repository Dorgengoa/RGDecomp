#include "types.h"

extern "C" void UskMemoryFree_42d8a0(s32, s32, s32);

struct H3 {
    s32 a;
    s32 b;
    s32 c;

};

extern "C" void HeapBlockRefFreeIfBlock_42e0e0(H3 *self, s32 arg1)
{
    bool ok;
    ok = false;
    if (self->a != 0 && self->b != 0) {
        ok = true;
    }
    if (ok) {
        if (arg1 == self->b) {
            UskMemoryFree_42d8a0(self->a, self->b, 0);
            self->a = 0;
            self->b = 0;
            self->c = 0;
        }
    }
}
