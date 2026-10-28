/* rgp:protos */
#define RGP_SELF_EvCmdSceneInfoGetRelated_25d500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pushes one of fifteen debug/telemetry rows into a formatter: the switch
   operand is ScriptGetInt_26a2a0()'s return value, and each arm feeds one or more
   fields of the block at *D_00481F78 + 0x5D00 to ScriptSetRefInt_26a1e0 (integer) or
   ScriptSetRefFloat_26a1c0 (float).

   jtbl_0045EFB0 is 15 entries and IS the identity permutation, so physical
   block order is source order, cases 0..14 as written.  The out-of-range
   `beql` returns 0 with the value in the delay slot; the `default: return 0;`
   block at 0x0025D754 is emitted after case 14 and is unreachable, which is
   how you know the source spells it LAST.

   MEASURED, and it re-confirms EvCmdOptionsSet_240930's 12-arm sweep: every call but
   the last of a group is followed by its OWN `addiu $18,$18,0x8`, and the only
   spelling that keeps that word is a POST-INCREMENT ON A POINTER USED AS THE
   CALL ARGUMENT -- `p0` is a `struct Row *` (8 bytes) and the argument is
   `(s32)p0++`.  Spelling it `p = p0 + 8` with `p += 8` statements folds every
   increment into the argument as `addiu $4,$17,0x8` and lands the unit EXACTLY
   NINE WORDS SHORT (3 in case 8, 2 each in cases 10 and 12 and the p1 == 4
   sub-arm).  Group sizes: case 8 has three increments over four calls, cases
   10 and 12 and the p1 == 4 sub-arm two over three, the p1 == 2 sub-arm none.

   MEASURED, 15 arms over two round trips, on where the cursor bump goes.
   Retail spends TWO words on it -- `daddu $18,$4,$0` in the prologue (before
   the null-check branch) and `addiu $18,$18,0x8` after it -- and the ONLY
   spellings that produce both are `p0++;` and `p0 = p0 + 1;` on the PARAMETER,
   placed AFTER the `m == 0` early return and BEFORE the ScriptGetInt_26a2a0() call
   (identical objects).  Everything else is measured:
     * the bump ABOVE the `m` load or between it and the branch -> 160 words
       (the prologue move is no longer needed, but a second one appears);
     * `p = p0 + 1;` or `p = p0;` + `p++;` in a NEW local -> 158, one short:
       mwcc folds the copy and the add into one `addiu $18,$4,0x8`;
     * ANY bump placed AFTER the ScriptGetInt_26a2a0() call -> 143, SIXTEEN short:
       mwcc then hoists `addiu $4,$18,0x8` above the `jr` and shares that one
       argument across all sixteen cursor uses, so every `daddu $4,$18,$0`
       disappears too.
   Declaring the callee to take `struct Row *` instead of `s32` + a cast is
   INERT (identical object sha1) -- a measured null on the argument-type axis.

   The nested dispatch on p1 is `beql` INTO each arm, i.e. a SWITCH, and its
   compare chain (4 then 2) is the source case order REVERSED -- `case 2:`
   first, which is also the physical block order (0x0025D6B8 before
   0x0025D6C8).

   SHIPPING THIS UNIT NEEDS A .rodata SLOT:
       config/crodata.txt:  EvCmdSceneInfoGetRelated_25d500  0045EFB0  3C   # jtbl_0045EFB0, 15 cases */

extern u8 *D_00481F78;

struct Row {
    s32 a;
    s32 b;
};

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Blk {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    u8 pad018[0x18];
    f32 m30;
    f32 m34;
    f32 m38;
    u8 pad03C[0x4];
    f32 m40;
    f32 m44;
    f32 m48;
    u8 pad04C[0x4];
    f32 m50;
    f32 m54;
    f32 m58;
    u8 pad05C[0x4];
    s32 m60;
    s32 m64;
    u8 pad068[0x28];
    f32 m90;
    u8 pad094[0x4];
    f32 m98;
    u8 pad09C[0x4];
    f32 mA0;
    f32 mA4;
    f32 mA8;
    u8 pad0AC[0x4];
    s32 mB0;
    u8 pad0B4[0xC];
    s32 mC0;
    s32 mC4;
};

s32 EvCmdSceneInfoGetRelated_25d500(struct Row *p0, s32 p1)
{ __typeof__(p0) rgp_entry_p0 = p0;
    struct Blk *m;
    u32 v;

    m = (struct Blk *)(D_00481F78 + 0x5D00);
    if (m == 0) {
        return 0;
    }
    p0++;
    v = ScriptGetInt_26a2a0((void *)rgp_entry_p0);
    switch (v) {
    case 0:
        ScriptSetRefInt_26a1e0((s32)p0, m->m00);
        break;
    case 1:
        ScriptSetRefInt_26a1e0((s32)p0, m->m04);
        break;
    case 2:
        ScriptSetRefInt_26a1e0((s32)p0, m->m08);
        break;
    case 3:
        ScriptSetRefInt_26a1e0((s32)p0, m->m0C);
        break;
    case 4:
        ScriptSetRefInt_26a1e0((s32)p0, m->m10);
        break;
    case 5:
        ScriptSetRefInt_26a1e0((s32)p0, m->m14);
        break;
    case 6:
        ScriptSetRefInt_26a1e0((s32)p0, m->m60);
        break;
    case 7:
        ScriptSetRefInt_26a1e0((s32)p0, m->m64);
        break;
    case 8:
        ScriptSetRefFloat_26a1c0((s32)p0++, m->mA0);
        ScriptSetRefFloat_26a1c0((s32)p0++, m->mA4);
        ScriptSetRefFloat_26a1c0((s32)p0++, m->mA8);
        ScriptSetRefFloat_26a1c0((s32)p0, Atan2f_1291a8(m->m90, m->m98));
        break;
    case 9:
        ScriptSetRefInt_26a1e0((s32)p0, m->mB0);
        break;
    case 10:
        ScriptSetRefFloat_26a1c0((s32)p0++, m->m30);
        ScriptSetRefFloat_26a1c0((s32)p0++, m->m34);
        ScriptSetRefFloat_26a1c0((s32)p0, m->m38);
        break;
    case 11:
        switch (p1) {
        case 2:
            ScriptSetRefFloat_26a1c0((s32)p0, m->m44);
            break;
        case 4:
            ScriptSetRefFloat_26a1c0((s32)p0++, m->m40);
            ScriptSetRefFloat_26a1c0((s32)p0++, m->m44);
            ScriptSetRefFloat_26a1c0((s32)p0, m->m48);
            break;
        }
        break;
    case 12:
        ScriptSetRefFloat_26a1c0((s32)p0++, m->m50);
        ScriptSetRefFloat_26a1c0((s32)p0++, m->m54);
        ScriptSetRefFloat_26a1c0((s32)p0, m->m58);
        break;
    case 13:
        ScriptSetRefInt_26a1e0((s32)p0, m->mC4);
        break;
    case 14:
        ScriptSetRefInt_26a1e0((s32)p0, m->mC0);
        break;
    default:
        return 0;
    }
    return 1;
}
