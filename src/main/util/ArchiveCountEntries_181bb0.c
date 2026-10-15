#include "types.h"

struct Obj0 {
    s8 m00;
    u8 pad001[0x47];
    s32 m48;
};

s32 ArchiveCountEntries_181bb0(s32 p0)
{
    s32 l0;
    struct Obj0 *l1;

    l0 = 0;
    l1 = (struct Obj0 *)p0;
    while ((l1->m00 ? 1 : 0) != 0) {
        l1 = (struct Obj0 *)((u8 *)l1 + l1->m48);
        l0 = l0 + 1;
    }
    return l0;
}
