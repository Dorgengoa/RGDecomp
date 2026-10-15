#include "types.h"

struct T309390 { u8 pad000[0x268]; s32 f268; };

extern void CameraModeSetTop_309440(struct T309390 *p, s8 v);

void CameraModePop_309390(struct T309390 *p, s32 flag)
{
    s32 n;
    s32 i;

    n = p->f268;
    if (n == 0) return;
    if (n <= 0) return;
    p->f268 = n - 1;
    if (flag == 0) return;
    i = p->f268;
    CameraModeSetTop_309440(p, *(s8 *)(i + (s32)p + 0x25F));
}
