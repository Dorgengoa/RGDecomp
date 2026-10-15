#include "types.h"
typedef void (*VoidFn)(void);
extern void EhRegisterFragmentStubMaybe_1026b0(s32, s32);
void RunStaticCtors_100df0(VoidFn *start, VoidFn *end, s32 a, s32 b)
{
    VoidFn *p;
    for (p = start; p < end; p++) {
        (*p)();
    }
    EhRegisterFragmentStubMaybe_1026b0(a, b);
}
