/* rgp:protos */
#define RGP_SELF_EvCmdEventSoundFadeIn_2450e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ctx2450e0 {
    void *f0;
    u8 *f4;
} Ctx2450e0;

typedef struct E2450e0 {
    u8 b[8];
} E2450e0;

extern Ctx2450e0 *gEventContext;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdEventSoundFadeIn_2450e0(E2450e0 *q)
{
    Ctx2450e0 *ctx;
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
    EventSoundFadeIn_24a040(m4, r, b, c);
    return 1;
}
