#include "types.h"

extern s32 S16ArrayGetCount_1ce1b0(void *param_1);
extern s32 S16ArrayGetChecked_1ce170(void *param_1, s32 param_2);

s32 LoaderIsIdle_1cd5b0(void *arg0) {
    u8 *base = (u8 *)arg0;

    if (S16ArrayGetCount_1ce1b0(base + 0x28) > 0) {
        return 0;
    }
    if (S16ArrayGetCount_1ce1b0(base + 0x20) > 0) {
        return (s16)S16ArrayGetChecked_1ce170(base + 0x20, 0) == 0x3FFF;
    }
    return 1;
}
