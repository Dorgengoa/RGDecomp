#include "types.h"

struct S1c4f80 { u8 pad000[0x4]; f32 m04; };

extern void SceneGetSunPos_1c4fc0(void *);

void SceneGetSunPosMirrored_1c4f80(void *a, struct S1c4f80 *b)
{
    SceneGetSunPos_1c4fc0(a);
    b->m04 = b->m04 * -1.0f;
}
