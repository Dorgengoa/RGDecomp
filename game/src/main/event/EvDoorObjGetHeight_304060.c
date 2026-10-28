/* rgp:protos */
#define RGP_SELF_EvDoorObjGetHeight_304060 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T304060 { u8 pad000[0x174]; f32 f174; u8 pad178[0x4]; f32 f17C; };

/*rgp*/

f32 EvDoorObjGetHeight_304060(struct T304060 *p)
{
    f32 v[4] __attribute__((aligned(16)));
    f32 a;

    a = p->f17C;
    if (a != 0.0f) return a;
    a = p->f174;
    if (a != 0.0f) return a;
    EventObjGetScale_2e7690((u8 *)p + 0x10, v);
    return v[1];
}
