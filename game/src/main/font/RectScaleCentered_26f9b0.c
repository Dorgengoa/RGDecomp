/* rgp:protos */
#define RGP_SELF_RectScaleCentered_26f9b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Vec4i;

void RectScaleCentered_26f9b0(Vec4i *arg0, f32 fparg0)
{
    f32 old8 = (f32) arg0->unk8;
    f32 oldC = (f32) arg0->unkC;
    f32 omt = 1.0f - fparg0;

    f32 t0 = (f32) arg0->unk0 + 0.5f * (old8 * omt);
    f32 t4 = (f32) arg0->unk4 + 0.5f * (oldC * omt);
    arg0->unk0 = (s32) t0;
    arg0->unk4 = (s32) t4;
    arg0->unk8 = (s32) (old8 * fparg0);
    arg0->unkC = (s32) (oldC * fparg0);
}
