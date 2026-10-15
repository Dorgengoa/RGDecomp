#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern s32 sceVu0InversMatrix(s32, void *);

s32 CameraBaseGetViewMatrix_15fa70(void *p4, s32 a5)
{
    return sceVu0InversMatrix(a5, (u8 *)p4 + 0x10);
}
