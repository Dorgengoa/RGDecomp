#include "types.h"

typedef struct Ctx245030 {
    void *f0;
    u8 *f4;
} Ctx245030;

typedef struct E245030 {
    u8 b[8];
} E245030;

extern Ctx245030 *gEventContext;
extern void *ScriptGetInt_2490f0(E245030 *q);
extern void *GameSceneSoundSlot6GetHandle_1d0780(void *a);
extern void *EventSoundBankHandleGet_24fc80(void *a);
extern void EventSoundFadeOut_24a030(void *a, void *b, void *c, void *d);

s32 EvCmdEventSoundFadeOut_245030(E245030 *q)
{
    Ctx245030 *ctx;
    void *m0;
    void *a;
    void *b;
    u8 *m4;
    void *c;
    void *r;

    ctx = gEventContext;
    m0 = ctx->f0;
    m4 = ctx->f4 + 0x4A0;
    a = ScriptGetInt_2490f0(q++);
    b = ScriptGetInt_2490f0(q++);
    c = ScriptGetInt_2490f0(q);
    if (a == 0) {
        r = GameSceneSoundSlot6GetHandle_1d0780(m0);
    } else {
        r = EventSoundBankHandleGet_24fc80(a);
    }
    EventSoundFadeOut_24a030(m4, r, b, c);
    return 1;
}
