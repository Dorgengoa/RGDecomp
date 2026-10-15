#include "types.h"

extern void VecSub_1cbd00(void *, void *, void *);
extern void VecNormalizeXZ_1cbb50(void *, void *);
extern f32 AiGetKeepDistanceMaybe_2c0f90(void *);
extern void VecScale_1cbca0(void *, void *, f32);
extern void VecAdd_1cbdc0(void *, void *, void *);

void AiPointFromDir_2bcc10(void *a, void *b, void *c, void *d, void *e)
{
    f32 f;

    VecSub_1cbd00(c, e, d);
    VecNormalizeXZ_1cbb50(c, c);
    f = AiGetKeepDistanceMaybe_2c0f90(a);
    VecScale_1cbca0(b, c, f);
    VecAdd_1cbdc0(b, b, e);
}
