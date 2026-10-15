#include "types.h"

extern s32 TargetRefIsValid_2e6e40(s32);
extern s32 EvTargetSetIsEnabled_3368c0(s32);

typedef struct {
    u8 pad0[0xe4];
    s32 unkE4;
    u8 padE8[0x2];
    s16 unkEA;
    s32 unkEC;
    s32 unkF0;
} T;

s32 EvObjLiftIsTargetActive_335730(T *arg0)
{
    s32 i;

    if (TargetRefIsValid_2e6e40((s32)((u8 *)arg0 + 0xA0)) == 0) {
        return 0;
    }
    if (arg0->unkEC == 0) {
        return 0;
    }
    if (arg0->unkF0 == 0) {
        return 0;
    }
    if (arg0->unkE4 == 0) {
        return 0;
    }
    for (i = 0; i < arg0->unkEA; i++) {
        if (EvTargetSetIsEnabled_3368c0(arg0->unkE4 + i * 0x118) == 0) {
            return 0;
        }
    }
    return 1;
}
