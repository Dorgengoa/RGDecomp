#include "types.h"
typedef struct { f32 w[4]; } SD4_0047FB40;
extern SD4_0047FB40 D_0047FB40 __attribute__((section(".sdata")));

extern void DrawRotatedQuad_383c70(void *, void *, void *, f32 *, f32, f32, f32, f32, f32);


void DrawRotatedQuadAlpha_383c20(void *unusedPtr0, void *unusedPtr1, void *unusedPtr2, f32 unused0, f32 unused1, f32 unused2, f32 unused3, f32 a, f32 b)
{
    f32 local[4];

    *(SD4_0047FB40 *)local = D_0047FB40;
    local[3] = 128.0f * a;
    DrawRotatedQuad_383c70(unusedPtr0, unusedPtr1, unusedPtr2, local, unused0, unused1, unused2, unused3, b);
}
