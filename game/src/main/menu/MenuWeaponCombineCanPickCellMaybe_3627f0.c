/* rgp:protos */
#define RGP_SELF_MenuWeaponCombineCanPickCellMaybe_3627f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u8 pad0[0x14]; s16 x14; s16 x16; } E;
typedef struct { u8 pad0[0x11]; s8 x11; u8 pad12[0x1A]; s32 x2C; s32 x30; } G;
typedef struct { u8 pad0[0x10]; s8 *x10; } R;
typedef struct { u8 pad0[0x88]; s32 x88; u8 pad8C[9]; u8 x95; } O;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern G *D_00482374;

#pragma opt_branchlessexpensivethandiv off
s32 MenuWeaponCombineCanPickCellMaybe_3627f0(O *o)
{
    u8 *w;
    E *e;
    R *r;
    s32 t;
    s32 k; s32 extra;

    if (o->x95 != 1 && o->x95 != 2) {
        return 0;
    }
    w = ((u8 *)GetGameData_1fede0());
    e = ((E *)UiEntryListFindByTag_28ea40(o->x88, 3));
    r = ((R *)InvFindByCategoryIndex_3c86e0(*(s32 *)(w + 0x18), 0, D_00482374->x11, e->x14, e->x16, 0));
    if (r == NULL) {
        return 0;
    }
    t = o->x95;
    k = r->x10[2];
    if (t == 1) {
        if (((unsigned char)ItemRecKindIs6_3d4510(r)) != 0 || k == 7) return 0;
        return 1;
    }
    if (t == 2) {
        if (((unsigned char)ItemRecKindIs6_3d4510(r)) != 0 || ((k = D_00482374->x2C, D_00482374->x11 == k) && (t = (k = e->x16, e->x14 + k * 8), extra = *(volatile s32 *)&D_00482374->x30, t == extra))) return 0;
        return 1;
    }
    return 1;
}
