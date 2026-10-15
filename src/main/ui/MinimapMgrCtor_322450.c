#include "types.h"

extern void MinimapSlotCtor_322610(void);
extern void MinimapSlotDtor_3225c0(void);
extern void ConstructArray_100620(void *a, void *b, void *c, s32 d, s32 e);

void *MinimapMgrCtor_322450(void *p)
{
    ConstructArray_100620(p, (void *)MinimapSlotCtor_322610, (void *)MinimapSlotDtor_3225c0, 0x1B0, 3);
    return p;
}
