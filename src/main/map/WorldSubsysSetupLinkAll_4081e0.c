#include "types.h"

struct S4081e0 { u8 pad000[0x8]; void *f08; void *f0C; void *f10; };

extern void WorldSubsysLinkIds_408c00(void *a, void *b);
extern void RevelationBoardsLinkAllCells_408510(void *a, void *b);

s32 WorldSubsysSetupLinkAll_4081e0(struct S4081e0 *p)
{
    if (p->f0C != 0) {
        WorldSubsysLinkIds_408c00(p->f0C, p->f08);
    }
    if (p->f10 != 0) {
        RevelationBoardsLinkAllCells_408510(p->f10, p->f08);
    }
    return 1;
}
