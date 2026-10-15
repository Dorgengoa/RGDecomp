#include "types.h"

struct S402540 { u8 pad000[0x4]; void *f04; void *f08; u8 pad00C[0x4]; void *f10; };

extern void WorldSubsysLinkIds_404260(void *a, void *b);
extern void WorldSubsysLinkIds_402870(void *a, void *b);

s32 WorldSubsysLinkAll_402540(struct S402540 *p)
{
    if (p->f08 != 0) {
        WorldSubsysLinkIds_404260(p->f08, p->f04);
    }
    if (p->f10 != 0) {
        WorldSubsysLinkIds_402870(p->f10, p->f04);
    }
    return 1;
}
