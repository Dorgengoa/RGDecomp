#include "types.h"
typedef struct O { u8 pad[0x234]; u8 f0 : 1; } O;
typedef struct G { u8 pad[0x14]; s32 x14; } G;
extern s32 VariantSetS32_36f040();
extern s16 VariantGetS16_36fcc0(u8 *);
extern s32 VariantGetS8_36fe50(u8 *);
extern O *CharaMgrPoolFindByDataId_3a8a70(s32, s16, s32, s32, s32, s32, s32);
extern G *D_00483960;
extern s32 D_00483964;

void ScriptFnCharaSetPartyLockedMaybe_3d82e0(s32 arg0, s32 arg1, s32 arg2, u8 *arg3)
{
    s16 id;
    s32 flag;
    O *p;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0) {
        return;
    }
    if (arg3 == NULL || arg2 < 2) {
        return;
    }
    id = VariantGetS16_36fcc0(arg3);
    flag = VariantGetS8_36fe50(arg3 + 0x38) != 0;
    p = CharaMgrPoolFindByDataId_3a8a70(D_00483960->x14, id, 1, 1, 0, 0, 0);
    if (p != NULL) {
        p->f0 = flag;
        VariantSetS32_36f040(arg0, 1, 1);
    }
}
