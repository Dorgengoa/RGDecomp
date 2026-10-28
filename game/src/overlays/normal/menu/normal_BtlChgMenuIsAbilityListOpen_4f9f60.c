/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuIsAbilityListOpen_4f9f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F9F60 -- the NULL-or-value select, in the polarity that gives
 * retail's `beql`: write `if (p != 0) { r = p->f456; } else { r = 0; }`.
 * The `== 0` spelling emits `bnel` (recorded on normal_MenuBattleEndOpen_4ec990).
 * One of the 55 unnamed functions. */
typedef struct Obj {
    u8 pad000[0x456];
    u8 f456;
} Obj;

extern Obj *D_00484454;

s32 normal_BtlChgMenuIsAbilityListOpen_4f9f60(void)
{
    Obj *p;
    s32 r;

    p = D_00484454;
    if (p != 0) {
        r = p->f456;
    } else {
        r = 0;
    }
    return r;
}
