#include "types.h"

extern f32 D_0047F1D0;
extern f32 D_0047F1D4;
extern f32 D_0047F1D8;
extern f32 D_0047F1DC;

void CameraDbgDrawTargetSphere_305b70(void *self, f32 *buf, f32 value);

struct V {f32 a,b,c,d;};
void CameraModeDbgDrawSphere_3061b0(void *self)
{
    struct V v;
    f32 *buf=(f32*)&v;

    buf[0] = D_0047F1D0;
    buf[1] = D_0047F1D4;
    buf[2] = D_0047F1D8;
    buf[3] = D_0047F1DC;
    CameraDbgDrawTargetSphere_305b70(self, buf, 5.0f);
}
