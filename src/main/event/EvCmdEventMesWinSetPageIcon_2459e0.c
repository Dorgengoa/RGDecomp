#include "types.h"

struct Q2459E0 { u8 pad000[0x1DEE]; u8 f1DEE; };
struct E2459E0 { u8 pad000[0x42C]; struct Q2459E0 *f42C; };
struct C2459E0 { u8 pad000[0x4]; struct E2459E0 *f04; };

extern struct C2459E0 *gEventContext;
extern u8 ScriptGetInt_2490f0(void);

s32 EvCmdEventMesWinSetPageIcon_2459e0(void)
{
    struct Q2459E0 *q;

    q = gEventContext->f04->f42C;
    if (q == 0) return 0;
    q->f1DEE = ScriptGetInt_2490f0();
    return 1;
}
