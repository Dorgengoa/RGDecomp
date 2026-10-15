#include "types.h"

typedef struct V4 {
    f32 v[4];
} V4;

typedef struct Self {
    u8 pad00[0x1c];
    V4 m;
} Self;

void CaptionCfgGetFrameRect_33ff80(V4 *dst, Self *src)
{
    *dst = src->m;
}
