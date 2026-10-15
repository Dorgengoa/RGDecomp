#include "types.h"

void WaitSema(s32);
void SignalSema(s32);
struct Lock {
    volatile s32 *s;
};

typedef struct E { u8 pad[0xC]; s32 sema; u8 pad10[0x64]; f32 x74; f32 x78; u8 pad7c[0xAC]; } E;
extern E D_004A25F0[4];
extern s32 D_004814F0[4] __attribute__((section(".sdata")));

void SoundStreamSlotSetVolume_1bca60(s32 arg0, f32 fparg0)
{
    E *p;
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk;

    if (arg0 < 0 || arg0 >= 4) {
        p = 0;
    } else {
        p = &D_004A25F0[arg0];
    }
    if (p == 0 || D_004814F0[arg0] == 0) {
        p = 0;
    }
    if (p != 0) {
        t = &p->sema;
        v = *t;
        lk.s = t;
        if (v > 0) {
            WaitSema(*t);
        }
        p->x78 = fparg0;
        p->x74 = fparg0;
        t = lk.s;
        if (*t > 0) {
            SignalSema(*t);
        }
    }
}
