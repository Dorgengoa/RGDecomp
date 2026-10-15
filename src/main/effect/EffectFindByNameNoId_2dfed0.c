#include "types.h"
extern void EffectFindByName_2dfe10(s32, s32, s16 *);
void EffectFindByNameNoId_2dfed0(s32 p0, s32 p1)
{
    s16 v;
    EffectFindByName_2dfe10(p0, p1, &v);
}
