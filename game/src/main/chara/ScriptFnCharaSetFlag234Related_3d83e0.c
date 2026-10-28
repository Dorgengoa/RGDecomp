/* rgp:protos */
#define RGP_SELF_ScriptFnCharaSetFlag234Related_3d83e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* s44g clone pair (ScriptFnCharaSetCannotLeadMaybe_3d6960 / ScriptFnCharaSetFlag234Related_3d83e0). MATCH.

   Identical shape to ScriptFnCharaSetCannotLeadMaybe_3d6960.c -- see that file's header for the
   two levers (the `||`-pair guard grouping and the s32-declared
   VariantGetS8_36fe50 return). The only difference between the pair is the
   callee at the tail: CharaSetFlag234Bit2Related_3ae370 here vs CharaSetCannotLeadMaybe_3ae330 there. */

union Val003d83e0 {
    s8 vs8;
    u8 vu8;
    s16 vs16;
    u16 vu16;
    s32 vs32;
    u32 vu32;
    s64 vs64;
    u64 vu64;
    f32 vf32;
};

typedef struct Var003d83e0 {
    s32 tag;
    u8 pad004[0x4];
    union Val003d83e0 u;
} Var003d83e0;

typedef struct Reg003d83e0 {
    u8 pad00[0x14];
    void *unk14;
} Reg003d83e0;

extern Reg003d83e0 *D_00483960;
extern s32 D_00483964;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void ScriptFnCharaSetFlag234Related_3d83e0(s32 self, s32 unused, s32 count, Var003d83e0 *arg3)
{
    s32 id;
    s32 flag;
    void *obj;

    if (self == 0) {
        return;
    }
    VariantSetS32_36f040(self, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0) {
        return;
    }
    if (arg3 == 0 || count < 2) {
        return;
    }
    id = VariantGetS16_36fcc0(arg3);
    flag = ((signed char)VariantGetS8_36fe50((Var003d83e0 *)((u8 *)arg3 + 0x38))) != 0;
    obj = CharaMgrPoolFindByDataId_3a8a70(D_00483960->unk14, id, 1, 1, 0, 0, 0);
    if (obj != 0) {
        CharaSetFlag234Bit2Related_3ae370(obj, flag);
        VariantSetS32_36f040(self, 1, 1);
    }
}
