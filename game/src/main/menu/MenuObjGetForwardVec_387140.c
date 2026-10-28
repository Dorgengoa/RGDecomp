/* rgp:protos */
#define RGP_SELF_MenuObjGetForwardVec_387140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct V387140 { f32 x; f32 y; f32 z; f32 w; } __attribute__((aligned(16))) V387140;
struct T387140 { u8 pad000[0x190]; V387140 f190; };

/*rgp*/

void MenuObjGetForwardVec_387140(struct T387140 *a, void *b, f32 x)
{
    V387140 v __attribute__((aligned(16)));

    v = a->f190;
    VecFromYawLen_387e50(b, v.y, x);
}
