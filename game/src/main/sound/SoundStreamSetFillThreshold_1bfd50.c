/* rgp:protos */
#define RGP_SELF_SoundStreamSetFillThreshold_1bfd50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void WaitSema(s32);
void SignalSema(s32);
struct Lock {
    volatile s32 *s;
};

struct Obj { u8 pad[0x40]; s32 sema; u8 pad44[0x2C]; f32 v; };

void SoundStreamSetFillThreshold_1bfd50(struct Obj *arg0, f32 fparg0) {
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk __attribute__((aligned(16)));

    t = &arg0->sema;
    v = *t;
    lk.s = t;
    if (v > 0) {
        WaitSema(*t);
    }
    arg0->v = fparg0;
    if (fparg0 < 0.0f) {
        arg0->v = 0.0f;
    }
    if (arg0->v > 1.0f) {
        arg0->v = 1.0f;
    }
    t = lk.s;
    if (*t > 0) {
        SignalSema(*t);
    }
}
