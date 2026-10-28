/* rgp:protos */
#define RGP_SELF_MenuPartySlotLayoutMaybe_29c970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 x;
    s16 y;
} P0029C970;

typedef struct {
    P0029C970 r[3][10];
} T0029C970;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0x20 - 6];
} Q0029C970;

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
} G0029C970;

typedef struct {
    u8 pad0[0x4C4];
    s32 unk4C4;
} A0029C970;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern T0029C970 D_00450B10;

s32 MenuPartySlotLayoutMaybe_29c970(A0029C970 *arg0, s32 arg1) {
    T0029C970 t __attribute__((aligned(16)));
    Q0029C970 *out;
    G0029C970 *g;
    P0029C970 *p;
    Q0029C970 *q;
    u32 n1;
    u32 n2;
    s32 start;
    u32 i;

    out = ((Q0029C970 *)UiGetWidgetSprite_28fe10(arg0->unk4C4, arg1, 0));
    if (out == NULL) {
        return 2;
    }
    g = ((G0029C970 *)GetGameData_1fede0());
    n1 = PartyCountMembers_3c2010(g->unk18, 1, 1);
    n2 = PartyCountReserve_3c1c20(g->unk18, 1, 1);
    t = *(T0029C970 *)&D_00450B10;
    start = n2 - 5;
    if (start <= 0) {
        start = 0;
    }
    p = t.r[start];
    for (i = 0; (s32)i < (s32)n1; i++) {
        out[i].x = p[i].x;
        out[i].y = p[i].y;
        out[i].z = 0x36;
    }
    q = &out[n1];
    for (i = 0; (s32)i < (s32)n2; i++) {
        q[i].x = p[i + 3].x;
        q[i].y = p[i + 3].y;
        if (start == 2) {
            q[i].z = 0x2E;
        } else {
            q[i].z = 0x36;
        }
    }
    out[n1 + n2].x = -1;
    return 0;
}
