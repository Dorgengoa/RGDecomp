#include "types.h"

extern s32 ObjInstListIndexValid_18e270(u8 *p);

u8 *ObjInstListGet_18e220(u8 *p, s32 i)
{
    if (ObjInstListIndexValid_18e270(p) != 0) {
        return p + i * 12 + 0x4B0;
    }
    return 0;
}
