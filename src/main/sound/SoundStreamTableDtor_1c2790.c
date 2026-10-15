#include "types.h"

extern void DestroyArray_1005b0(void *, void *, s32, s32);
extern void *SoundStreamDtor_1bfc30(void *, s16);
extern void OperatorDelete_100840(void *);

void *SoundStreamTableDtor_1c2790(void *o, s16 flag)
{
    if (o != 0) {
        DestroyArray_1005b0((u8 *)o + 0x4, (void *)SoundStreamDtor_1bfc30, 0x84, 8);
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
