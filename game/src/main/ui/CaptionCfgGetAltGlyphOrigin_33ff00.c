/* rgp:protos */
#define RGP_SELF_CaptionCfgGetAltGlyphOrigin_33ff00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct V4 {
    f32 v[4];
} V4;

typedef struct Self {
    u8 pad00[0x3c];
    V4 m;
} Self;

void CaptionCfgGetAltGlyphOrigin_33ff00(V4 *dst, Self *src)
{
    *dst = src->m;
}
