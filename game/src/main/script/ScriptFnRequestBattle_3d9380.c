/* rgp:protos */
#define RGP_SELF_ScriptFnRequestBattle_3d9380 1
#include "port/game_protos.h"
#line 1
/* s41 agent10: MATCH (|| guard chain). */
#include "types.h"

typedef struct Obj3 {
    u8 pad0[0x7E];
    s8 unk7E;
} Obj3;

typedef struct Obj2 {
    u8 pad0[0x18];
    Obj3 *unk18;
} Obj2;

typedef struct Obj1 {
    u8 pad0[0x238];
    Obj2 *unk238;
} Obj1;

typedef struct Global {
    u8 pad0[0x20];
    Obj1 *unk20;
} Global;

/*rgp*/
/*rgp*/
extern Global *D_00483960;
extern s32 D_00483964;

void ScriptFnRequestBattle_3d9380(s32 arg0)
{
    Obj1 *temp_4;
    Obj2 *temp_2;
    Obj3 *var_2;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if ((D_00483960 == NULL) || (D_00483964 == 0)) {
        return;
    }
    temp_4 = D_00483960->unk20;
    temp_2 = temp_4->unk238;
    if (temp_2 != NULL) {
        var_2 = temp_2->unk18;
    } else {
        var_2 = NULL;
    }
    if (var_2 == NULL) {
        VariantSetS32_36f040(arg0, 1, 1);
        return;
    }
    if (((s64) ((s64) var_2->unk7E << 0x3F) >> 0x3F) == 0) {
        VariantSetS32_36f040(arg0, 1, 1);
        return;
    }
    VariantSetS32_36f040(arg0, CharaSysRequestBattle_3a5610() & 0xFF, 1);
}
