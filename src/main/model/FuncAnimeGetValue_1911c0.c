#include "types.h"
#include "vec.h"
#pragma opt_dead_assignments off

extern const f32 D_0047D1FC __attribute__((section(".sdata")));

void FuncAnimeGetValue_1911c0(void *arg0, void *arg1) {
    void *temp_7;
    s8 temp_4;
    s8 *sub;

    temp_7 = *(void **)((u8 *)arg0 + 0x0);
    *(u128 *)((u8 *)arg1 + 0) = *(u128 *)((u8 *)arg0 + 0x20);
    sub = (s8 *)temp_7 + 0x60;
    temp_4 = *(s8 *)((u8 *)temp_7 + 0x6C);
    switch (temp_4) {
    case 1:
        break;
    case 2:
        *(f32 *)((u8 *)arg1 + 0) = (180.0f * *(f32 *)((u8 *)arg1 + 0)) / D_0047D1FC;
        *(f32 *)((u8 *)arg1 + 4) = (180.0f * *(f32 *)((u8 *)arg1 + 4)) / D_0047D1FC;
        *(f32 *)((u8 *)arg1 + 8) = (180.0f * *(f32 *)((u8 *)arg1 + 8)) / D_0047D1FC;
        *(f32 *)((u8 *)arg1 + 0xC) = 0.0f;
        break;
    case 3:
        break;
    case 4:
        break;
    }
    if (sub[0xE] != 0) {
        *(f32 *)((u8 *)arg1 + 4) = *(f32 *)((u8 *)arg1 + 0);
        *(f32 *)((u8 *)arg1 + 8) = *(f32 *)((u8 *)arg1 + 0);
    }
}
