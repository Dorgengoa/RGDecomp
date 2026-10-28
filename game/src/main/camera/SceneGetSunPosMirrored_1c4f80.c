/* rgp:protos */
#define RGP_SELF_SceneGetSunPosMirrored_1c4f80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S1c4f80 { u8 pad000[0x4]; f32 m04; };

/*rgp*/

void SceneGetSunPosMirrored_1c4f80(void *a, struct S1c4f80 *b)
{
    SceneGetSunPos_1c4fc0(a, (void *)b);
    b->m04 = b->m04 * -1.0f;
}
