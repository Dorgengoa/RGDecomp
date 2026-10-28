/* rgp:protos */
#define RGP_SELF_ItemGetWeaponUseEffectMaybe_3d4e80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent { u8 pad000[0x28]; s32 m28; } Ent;
typedef struct Hdr { u8 pad000[0x10]; void *m10; } Hdr;

/*rgp*/

s32 ItemGetWeaponUseEffectMaybe_3d4e80(Hdr *o)
{
    void *p;
    Ent *e;

    p = o->m10;
    if (p == 0) {
        return 0;
    }
    e = ((Ent *)ItemDefGetWeaponData_40e110(p));
    if (e != 0) {
        return e->m28;
    }
    return 0;
}
