#include "types.h"

typedef struct { u8 pad[0x510]; s32 f510; } T;

extern s32 MinimapMgrFindSlotByName_322340(T *);
extern void MinimapFadeIn_329ef0(s32, f32);

void MinimapMgrSelectActive_321f60(T *p)
{
    p->f510 = MinimapMgrFindSlotByName_322340(p);
    if (p->f510 != 0) {
        MinimapFadeIn_329ef0(p->f510, 10.0f);
    }
}
