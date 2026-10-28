/* rgp:protos */
#define RGP_SELF_ScriptFnMapMarkerSetAddMaybe_3d7870 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
} Obj00483960;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern Obj00483960 *D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

void ScriptFnMapMarkerSetAddMaybe_3d7870(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    if (arg3 == 0 || arg2 <= 0) {
        return;
    }
    StateBlockMapMarkerSetAddMaybe_3cc170(D_00483960->unk10, (s32)VariantGetFloat_36f7a0(arg3), 0, 0);
        VariantSetS32_36f040(arg0, 1, 1);
}
