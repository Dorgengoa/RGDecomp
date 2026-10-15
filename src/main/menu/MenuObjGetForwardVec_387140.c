#include "types.h"

typedef struct V387140 { f32 x; f32 y; f32 z; f32 w; } __attribute__((aligned(16))) V387140;
struct T387140 { u8 pad000[0x190]; V387140 f190; };

extern void VecFromYawLen_387e50(void *, f32, f32);

void MenuObjGetForwardVec_387140(struct T387140 *a, void *b, f32 x)
{
    V387140 v;

    v = a->f190;
    VecFromYawLen_387e50(b, v.y, x);
}
