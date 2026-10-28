/* rgp:protos */
#define RGP_SELF_normal_FieldHudPartyPanelShakeStart_4f4b30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F4B30 -- fills one 20-byte slot of the p->f300 table, indexed by
 * whatever func_3C3070 resolves.  The `div`/`mfhi` pair is a runtime `% 10`,
 * so the divisor is NOT a folded constant. */
typedef struct A {
    u8    pad000[0x18];
    void *f18;
} A;

typedef struct Slot {
    void *f00;
    s32   f04;
    s32   f08;
    s16   f0C;
    s16   f0E;
    f32   f10;
} Slot;

typedef struct N {
    u8   pad000[0x300];
    Slot f300[4];
} N;

/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudPartyPanelShakeStart_4f4b30(N *p, void *q)
{
    A    *a;
    s32   i;
    Slot *s;

    a = ((A *)GetGameData_1fede0());
    if (a == NULL) {
        return;
    }
    i = PartyFindSlotOfId_3c3070(a->f18, q);
    if (i < 0 || i > 3) {
        return;
    }
    {
        s = &p->f300[i];
        s->f00 = q;
        s->f04 = i * 125 + 10;
        s->f08 = 0x17C;
        s->f10 = 10.5f + (f32)(Rand_133710() % 10) / 5.0f;
        s->f0E = 3;
        s->f0C = 0;
    }
}
