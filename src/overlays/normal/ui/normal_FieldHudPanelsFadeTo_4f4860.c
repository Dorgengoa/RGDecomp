#include "types.h"
/* normal 0x004F4860 -- leaf: remembers the target, then stores the per-step
 * delta (target - current) / steps. */

typedef struct Obj { u8 pad000[0x364]; f32 f364; f32 f368; f32 f36C; } Obj;

extern void normal_FieldHudPanelsFadeTo_4f4860(Obj *p, f32 target, f32 steps);

void normal_FieldHudPanelsFadeTo_4f4860(Obj *p, f32 target, f32 steps)
{
    p->f368 = target;
    p->f364 = (target - p->f36C) / steps;
}
