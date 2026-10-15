#include "types.h"

/* Script-command dispatcher.  TWIN of EvCmdMesWinSetParam_265f00, which is the same source
   with a different accessor family (ScriptGetInt_26a2a0 / TaggedGetFloat_26a280 /
   ScriptGetCodeAddr_26a200 / MesMgrGetSlotWin_266af0 for ScriptGetInt_2490f0 / TaggedGetFloat_2490d0 /
   ScriptGetCodeAddr_249050 / MesMgrGetSlotWin_24fcc0) and two extra cases.

   Levers used:
   - `addiu $17,$17,0x8` in a jal delay slot is the POST-INCREMENT ON A POINTER
     USED AS THE CALL ARGUMENT (EvCmdOptionsSet_240930's 12-arm measured null);
   - retail FALLS THROUGH the `bnel $16,$0` into `$2 = 0; b epilogue`, so the
     source guard is the positive `if (r == 0) return 0;`;
   - `dsll32 $5,$2,16 / dsra32 $5,$5,16` off a plain s32 is an s32 local with
     an EXPLICIT `(s16)` cast at the call (levers.d/normal-s16-cast-sign-ext);
   - case 2 ends `b <epilogue>` with `addiu $2,$0,1` in the delay slot instead
     of `b <the $2=1 block>`, which is `return 1;` written out, not `break`;
   - TaggedGetFloat_2490d0 returns a FLOAT (the arm has `cvt.w.s $f0,$f0 / mfc1`).

   jtbl_0045EA50 is 9 entries, identity permutation, every arm distinct; the
   out-of-range `beql` carries `daddu $2,$0,$0`, and the same `$2 = 0; goto
   epilogue` block is ALSO emitted (dead) after the last arm -- the explicit
   `default: return 0;`.

   SHIPPING THIS UNIT NEEDS A .rodata SLOT:
       config/crodata.txt:  EvCmdMesWinSetParam_242650  0045EA50  24   # jtbl_0045EA50, 9 cases */

extern s32 ScriptGetInt_2490f0(s32);
extern f32 TaggedGetFloat_2490d0(s32);
extern s32 ScriptGetCodeAddr_249050(s32);
extern void *MesMgrGetSlotWin_24fcc0(s32);
extern void *GetGameData_1fede0(void);
extern void *GroupGetRecordById_41c2a0(s32, s32, s32, s32);
extern void MesWinSetActive_2774e0(void *, s32);
extern void MesWinSetAllLineSpacing_2722f0(void *, s32);
extern void MesWinSetSeEnabled_272b50(void *, s32);
extern void MesWinSetNameShown_271390(void *, s32);
extern void MesWinSetName_271300(void *, s32);

struct Ent {
    u8 pad0000[0x1C3A];
    u8 m1C3A;
    u8 pad1C3B[0x1B2];
    u8 m1DED;
};

struct Hnd {
    u8 pad00[0x4];
    s32 m04;
};

struct Res {
    u8 pad00[0x6C];
    s32 m6C;
};

struct Sys {
    u8 pad00[0x8];
    struct Res *m08;
};

struct Cmd {
    s32 a;
    s32 b;
};

s32 EvCmdMesWinSetParam_242650(struct Cmd *p0)
{
    struct Ent *r;
    struct Sys *sys;
    struct Hnd *h;
    s32 v;

    r = MesMgrGetSlotWin_24fcc0(ScriptGetInt_2490f0((s32)p0++));
    if (r == 0) {
        return 0;
    }
    switch (ScriptGetInt_2490f0((s32)p0++)) {
    case 0:
        r->m1DED = ScriptGetInt_2490f0((s32)p0);
        break;
    case 1:
        r->m1C3A = ScriptGetInt_2490f0((s32)p0) != 0;
        break;
    case 2:
        TaggedGetFloat_2490d0((s32)p0);
        break;
    case 3:
        MesWinSetActive_2774e0(r, (s32)TaggedGetFloat_2490d0((s32)p0));
        break;
    case 4:
        TaggedGetFloat_2490d0((s32)p0++);
        TaggedGetFloat_2490d0((s32)p0);
        break;
    case 5:
        MesWinSetAllLineSpacing_2722f0(r, ScriptGetInt_2490f0((s32)p0));
        break;
    case 6:
        sys = GetGameData_1fede0();
        v = ScriptGetInt_2490f0((s32)p0);
        h = GroupGetRecordById_41c2a0(sys->m08->m6C, (s16)v, -1, 0);
        if (h != 0) {
            MesWinSetNameShown_271390(r, 1);
            MesWinSetName_271300(r, h->m04);
        }
        break;
    case 7:
        v = ScriptGetCodeAddr_249050((s32)p0);
        MesWinSetNameShown_271390(r, 1);
        MesWinSetName_271300(r, v);
        break;
    case 8:
        MesWinSetSeEnabled_272b50(r, ScriptGetInt_2490f0((s32)p0));
        break;
    default:
        return 0;
    }
    return 1;
}
