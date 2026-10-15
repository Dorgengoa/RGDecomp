#include "types.h"

extern void Vec3Set_32b0b0(void *, f32, f32, f32);
extern void EntryPosRecSetEntry_32b0a0(void *, s32);

void EntryPosRecClear_32b0c0(void *p)
{
    Vec3Set_32b0b0(p, 0.0f, 0.0f, 0.0f);
    EntryPosRecSetEntry_32b0a0(p, 0);
}
