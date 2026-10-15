#include "types.h"

typedef struct { f32 m[4]; } M_002bcca0;

extern void CharaGetPos_2388a0(void *, M_002bcca0 *);
extern f32 AiGetKeepDistanceMaybe_2c0f90(void *);
extern void VecScale_1cbca0(void *, void *, f32);
extern void VecAdd_1cbdc0(void *, void *, M_002bcca0 *);

void AiPointFromChara_2bcca0(void *a, void *b, void *c, void *d)
{
    M_002bcca0 m;
    f32 f;

    if (c == 0) return;
    CharaGetPos_2388a0(c, &m);
    f = AiGetKeepDistanceMaybe_2c0f90(a);
    VecScale_1cbca0(b, d, f);
    VecAdd_1cbdc0(b, b, &m);
}
