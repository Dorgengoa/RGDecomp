#include "types.h"

typedef struct {
    u8 pad0[4];
    u8 f0 : 1;
    u8 f1 : 1;
    u8 f2 : 1;
    u8 pad5[0x1B];
    f64 d;
} Obj;

s32 DoubleLessEqual_100280(f64, f64);
s32 DoubleLess_1002b0(f64, f64);
s32 DoubleEqual_1002f0(f64, f64);
s32 GetGameMode_1f59c0(void);
void CharaSysQueueEncounter_3a5730(Obj *, s32);
s32 PartyGetEncounterRec_3cb040(s32);
extern u8 *D_004837C0;

f64 CharaSysEncounterDistTick_3a5890(Obj *arg0, f32 x) {
    f64 d;

    if (D_004837C0 == NULL) {
        return 0.0;
    }
    if (*(*(u8 **)(D_004837C0 + 0x20) + 0x24C) & 1) {
        return 0.0;
    }
    if (!arg0->f0) {
        return 0.0;
    }
    if (!arg0->f2) {
        return 0.0;
    }
    if (GetGameMode_1f59c0() != 6) {
        return arg0->d;
    }
    d = arg0->d;
    if (DoubleLess_1002b0(d, 0.0) != 0) {
        return -1.0;
    }
    if (DoubleEqual_1002f0(0.0, d) != 0) {
        return 0.0;
    }
    if (PartyGetEncounterRec_3cb040(*(s32 *)(D_004837C0 + 0x18)) == 0) {
        return arg0->d;
    }
    d = arg0->d;
    arg0->d = d - x;
    if (DoubleLessEqual_100280(arg0->d, 0.0) != 0) {
        arg0->d = 0.0;
        CharaSysQueueEncounter_3a5730(arg0, -1);
    }
    return arg0->d;
}
