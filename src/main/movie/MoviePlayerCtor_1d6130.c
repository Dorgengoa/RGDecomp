#include "types.h"

typedef struct Obj_FUN_001d6130 {
    u8 pad000[0x17910];
    s32 f17910;
    s32 f17914;
    f32 f17918;
    f32 f1791C;
    u8 pad17920[0x4];
} Obj_FUN_001d6130;

extern void ScreenFadeBlockInit_178490(void *p);

Obj_FUN_001d6130 *MoviePlayerCtor_1d6130(Obj_FUN_001d6130 *o)
{
    ScreenFadeBlockInit_178490((u8 *)o + 0x17920);
    o->f17910 = 0;
    o->f17914 = 0;
    o->f17918 = 1.0f;
    o->f1791C = 1.0f;
    return o;
}
