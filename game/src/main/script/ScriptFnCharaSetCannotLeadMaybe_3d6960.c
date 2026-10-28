/* rgp:protos */
#define RGP_SELF_ScriptFnCharaSetCannotLeadMaybe_3d6960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* s44g clone pair (ScriptFnCharaSetCannotLeadMaybe_3d6960 / ScriptFnCharaSetFlag234Related_3d83e0). MATCH.

   Guards a loaned object back in, using a `Var`-tagged pair of small
   values read out of arg3 (a "cmd" style struct: a Var at offset 0x0 --
   passed directly -- and a second Var at offset 0x38). D_00483960 is a
   global registry pointer whose ->unk14 field is a lookup table root
   also seen from EvCmdCharaResRelease_243dd0.cpp / EvCmdJasterGetAltFormFlagMaybe_25ac10.cpp as `g->f14`.

   Two levers found getting this byte-identical:
   1. The four early-return guards must be grouped into exactly two `||`
      pairs -- (D_00483960==0 || D_00483964==0) and (arg3==0 || count<2)
      -- not four flat sequential `if`s and not a single four-term `&&`.
      Each pair's SECOND term is what buys retail's expensive shape: the
      D_00483964 term compiles to an inverted branch + unconditional jump
      (4 words) instead of a direct branch (2 words), and the `count<2`
      term compiles to a branch-likely with the continuation's first
      instruction duplicated into its delay slot AND left behind as a
      dead orphan (retail's own object carries that orphan `daddu` at
      003D69CC, unreachable). Flat sequential ifs or one big `&&` both
      produce the cheap 2-word form for every guard and land 3 words
      short.
   2. VariantGetS8_36fe50 truly returns s8, but declaring it that way at THIS
      call site buys a spurious `dsll32/dsra32`-by-0x18 re-narrowing pair
      before the `!= 0` test that retail's object does not have --
      declare it s32 here instead (the real callee already sign-extends,
      so the raw 32-bit register value is safe to compare directly). */

union Val003d6960 {
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

typedef struct Var003d6960 {
    s32 tag;
    u8 pad004[0x4];
    union Val003d6960 u;
} Var003d6960;

typedef struct Reg003d6960 {
    u8 pad00[0x14];
    void *unk14;
} Reg003d6960;

extern Reg003d6960 *D_00483960;
extern s32 D_00483964;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void ScriptFnCharaSetCannotLeadMaybe_3d6960(s32 self, s32 unused, s32 count, Var003d6960 *arg3)
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
    flag = ((signed char)VariantGetS8_36fe50((Var003d6960 *)((u8 *)arg3 + 0x38))) != 0;
    obj = CharaMgrPoolFindByDataId_3a8a70(D_00483960->unk14, id, 1, 1, 0, 0, 0);
    if (obj != 0) {
        CharaSetCannotLeadMaybe_3ae330(obj, flag);
        VariantSetS32_36f040(self, 1, 1);
    }
}
