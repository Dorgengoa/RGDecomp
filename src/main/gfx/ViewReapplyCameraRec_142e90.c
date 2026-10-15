#include "types.h"

typedef struct {
    u8 pad[0x14];
    f32 f14;
    u8 pad2[8];
    f32 f20, f24;
    u8 pad3[0x1C];
    f32 f44, f48, f4C;
} S_00142e90;

typedef struct { u8 pad[0xF20]; S_00142e90 *fF20; } T_00142e90;

extern void ViewSetProjection_143000(T_00142e90 *, f32, f32, f32, f32, f32, f32);
extern void CameraSetView_156200(void *, void *, void *);
extern void DrawListAddViewPacket_1482e0(T_00142e90 *);
extern void DrawListAddCameraMatrixPacket_1481b0(T_00142e90 *);

void ViewReapplyCameraRec_142e90(T_00142e90 *p)
{
    S_00142e90 *s;

    s = p->fF20;
    if (s == 0) return;
    ViewSetProjection_143000(p, s->f14, s->f20, s->f24, s->f44, s->f48, s->f4C);
    if (p->fF20 != 0) {
        CameraSetView_156200(p->fF20, (void *)((s32)s + 0xB0), (void *)((s32)s + 0x170));
    }
    DrawListAddViewPacket_1482e0(p);
    DrawListAddCameraMatrixPacket_1481b0(p);
}
