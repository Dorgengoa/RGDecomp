#include "types.h"
struct S228660 { s32 m00; s32 m04; };

void ActReferenceInit_228660(struct S228660 *p, s32 a, s32 b)
{
    p->m00 = 0;
    p->m04 = 0;
    if (a != 0) {
        if (b != 0) {
            goto ok;
        }
        return;
    }
    return;
ok:
    p->m00 = a;
    p->m04 = b;
}
