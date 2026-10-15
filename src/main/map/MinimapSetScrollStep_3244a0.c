#include "types.h"

s32 MinimapSetScrollStep_3244a0(void *self, s32 arg1, s32 arg2)
{
    f32 div;

    switch (arg2) {
    case 1:
    case 0:
        div = (f32)arg1;
        *(f32 *)((u8 *)self + 0x60) =
            (*(f32 *)((u8 *)self + 0x50) -
             (*(f32 *)((u8 *)self + 0x30) + *(f32 *)((u8 *)self + 0x40))) / div;
        *(f32 *)((u8 *)self + 0x64) =
            (*(f32 *)((u8 *)self + 0x54) -
             (*(f32 *)((u8 *)self + 0x34) + *(f32 *)((u8 *)self + 0x44))) / div;
        *(f32 *)((u8 *)self + 0x68) =
            (*(f32 *)((u8 *)self + 0x58) -
             (*(f32 *)((u8 *)self + 0x38) + *(f32 *)((u8 *)self + 0x48))) / div;
        break;
    }
    return 1;
}
