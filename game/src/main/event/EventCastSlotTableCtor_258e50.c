/* rgp:protos */
#define RGP_SELF_EventCastSlotTableCtor_258e50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

struct Ent {
    s32 m0;
    s32 m4;
    s32 m8;
    s32 mC;
};

struct Obj0 {
    struct Ent m000[0x20];
};

/* The first loop walks a POINTER (sltu); the second indexes (slti).
   The 0xC member is stored five times over - retail keeps all five. */
struct Obj0 *EventCastSlotTableCtor_258e50(struct Obj0 *p0)
{
    u8 *q;
    s32 i;

    q = (u8 *)p0;
    do {
        EventCastSlotCtor_258f10(q);
        q += 0x10;
    } while (q < (u8 *)p0 + 0x200);
    for (i = 0; i < 0x20; i++) {
        p0->m000[i].m0 = -1;
        p0->m000[i].m4 = -1;
        p0->m000[i].m8 = 1;
        p0->m000[i].mC = 0;
        p0->m000[i].mC = 0;
        p0->m000[i].mC = 0;
        p0->m000[i].mC = 0;
        p0->m000[i].mC = 0;
    }
    return p0;
}
