#include "types.h"

struct T309440 { u8 pad000[0x268]; s32 f268; s8 f26C; };

extern void CameraApplyMode_309490(struct T309440 *p, s8 v);

void CameraModeSetTop_309440(struct T309440 *p, s8 v)
{
    s32 i;
    s8 f;

    if (p->f268 <= 0) {
        p->f268 = 1;
    }
    i = p->f268;
    *(s8 *)(i + (s32)p + 0x25F) = v;
    f = p->f26C;
    if (f == -1) {
        CameraApplyMode_309490(p, v);
    }
}
