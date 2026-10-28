/* rgp:protos */
#define RGP_SELF_ActCfgTableResolveActionAlias_223730 1
#define RGP_SELF_Find 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad[0xC];
} Entry;

typedef struct {
    u8 pad0[0x48];
    Entry *entries;
    u8 pad4C[0x24];
    s16 count;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline Entry *Find(Obj *o, s32 id, s32 kind)
{
    Entry *e;
    s32 i;

    if (id < 0) {
        return 0;
    }
    e = o->entries;
    if (e == 0) {
        return 0;
    }
    for (i = 0; i < o->count; i++, e++) {
        if (((short)ActInfoWepActGetSlot_22ef10(e)) == kind && id == ((short)ActInfoWepActGetId_22ef00(e))) {
            return e;
        }
    }
    return 0;
}

int ActCfgTableResolveActionAlias_223730(Obj *o, s32 a, s32 b, s32 c, s32 d)
{
    Entry *e;

    e = Find(o, a, 0);
    if (e != 0) {
        d = ((s32)ActInfoWepActResolveAlias_22ee40(e, d));
    }
    e = Find(o, b, 1);
    if (e != 0) {
        d = ((s32)ActInfoWepActResolveAlias_22ee40(e, d));
    }
    return ActCfgTableResolveAbltAlias_2238a0(o, c, d);
}
