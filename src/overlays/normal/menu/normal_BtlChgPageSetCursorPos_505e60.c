#include "types.h"
/* normal 0x00505E60 -- stores the row's two callback words, returns 1. */
typedef struct Obj { u8 pad00[0x60]; s32 f60; s32 f64; } Obj;
extern s32 normal_BtlChgPageSetCursorPos_505e60(Obj *p, s32 a, s32 b);
s32 normal_BtlChgPageSetCursorPos_505e60(Obj *p, s32 a, s32 b)
{
    p->f60 = a;
    p->f64 = b;
    return 1;
}
