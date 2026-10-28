/* rgp:protos */
#define RGP_SELF_ActionPacketInitBattleEnd_3e3550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 h0;
    u8 b2;
    u8 b3;
    u8 b4;
    u8 pad5[7];
    s32 wC;
    u8 pad10[0xC];
    s16 h1C;
    s16 h1E;
    s16 h20;
} Pkt;

/*rgp*/
/*rgp*/
/*rgp*/
extern void *D_00483990;

Pkt *ActionPacketInitBattleEnd_3e3550(Pkt *arg0, s32 arg1, s32 arg2)
{
    s32 id;
    s32 a;
    s32 b;
    s32 kind;
    void *p;
    void *q;

    ActionPacketClear_3e3e90((void *)arg0);
    if (D_00483990 == NULL) {
        return NULL;
    }
    p = *(void **)((u8 *)D_00483990 + 0x20);
    q = *(void **)((u8 *)p + 0x238);
    if (q != NULL) {
        id = *(s16 *)((u8 *)q + 0xC);
    } else {
        id = -1;
    }
    a = CharaSysGetEncounterEntryIdMaybe_3a36f0(p);
    b = CharaSysGetEncounterIdMaybe_3a36d0(*(void **)((u8 *)D_00483990 + 0x20));
    q = *(void **)((u8 *)(*(void **)((u8 *)D_00483990 + 0x20)) + 0x238);
    if (q != NULL) {
        kind = *(s16 *)((u8 *)q + 0x168);
    } else {
        kind = 0;
    }
    arg0->b2 = 5;
    arg0->h0 = 1;
    switch (kind) {
    case 1:
        arg0->b3 = 0x1A;
        arg0->b4 = arg2 ? 0x1B : 0x1C;
        arg0->h0 = 3;
        break;
    case 2:
        arg0->b3 = 0x1D;
        arg0->b4 = arg2 ? 0x1E : 0x1F;
        arg0->h0 = 3;
        break;
    case 3:
        arg0->b3 = 0x20;
        arg0->h0 = 2;
        break;
    case 4:
        arg0->b3 = 0x3D;
        arg0->h0 = 2;
        break;
    }
    arg0->wC = arg1;
    arg0->h1C = id;
    arg0->h1E = a;
    arg0->h20 = b;
    return arg0;
}
