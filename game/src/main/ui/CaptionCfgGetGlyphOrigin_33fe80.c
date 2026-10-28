/* rgp:protos */
#define RGP_SELF_CaptionCfgGetGlyphOrigin_33fe80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct V4 {
    f32 v[4];
} V4;

typedef struct Self {
    u8 pad00[0x2c];
    V4 m;
} Self;

void CaptionCfgGetGlyphOrigin_33fe80(V4 *dst, Self *src)
{
    *dst = src->m;
}
