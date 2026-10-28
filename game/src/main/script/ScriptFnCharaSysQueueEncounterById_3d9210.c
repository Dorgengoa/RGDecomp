/* rgp:protos */
#define RGP_SELF_ScriptFnCharaSysQueueEncounterById_3d9210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern void *D_00483960;
extern s32 D_00483964;

void ScriptFnCharaSysQueueEncounterById_3d9210(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0) {
        return;
    }
    if (arg3 == 0 || arg2 <= 0) {
        return;
    }
    VariantSetS32_36f040(arg0, CharaSysQueueEncounterById_3a5660(*(s32 *)((u8 *)D_00483960 + 0x20), (long long)((s16)((short)VariantGetS16_36fcc0(arg3))), -1, 0) & 0xFF, 1);
}
