#include "types.h"

/* Record-and-forward for three script command kinds.  The OUTER test is an
   if-chain (6, 8, 0xA in source order); the inner dispatch is a switch, so its
   compare chain 0xA, 8, 6 reads backwards and the bodies are laid out 6, 8,
   0xA -- which is the independent check.

   "slti $2, $4, 0x20" feeding a bnez lands in a GPR, so the branch-taken
   condition is a bare "<" and the source token is ">= 0x20" with the
   early return as the FALL-THROUGH -- memory/at-compare-class.md.

   EvTargetSetInitNamed_336ab0 takes THIRTEEN arguments: ten integers (eight in $4..$11, then
   two EIGHT-BYTE stack slots at caller_sp+0 and +8 -- MIPS EABI, see
   memory/levers.d/im-eabi-stack-arguments.md) and three f32 in $f12..$f14.
   The stack pair is stored with "sd", so both are 64-bit. */

struct Rec {
    u8 pad0[0x118];
};

extern struct Rec *D_00482888;
extern s32 D_0048288C;
extern u8  D_004E7000[];

extern s32 TargetRefGetId_2e7120(s32);
extern s32 EvObjGetTargetRef_2f9ca0(u8 *);
extern s64 ScriptArgGetAreaId_3019b0(s32);
extern s32 ScriptArgGetStr_301a00(s32);
extern f32 ScriptArgGetFloat_301a20(s32);
extern s64 EventStrDup_301aa0(s32);
extern void EvTargetSetInitNamed_336ab0(struct Rec *, s64, s32, s64, s32, s64, f32, s64,
                         f32, s64, f32, s64, s64);

s32 EvScriptCmdObjLiftTargetSetAddNamed_2fe4c0(s32 p, s32 kind)
{
    struct Rec *rec;
    s64 a;
    s32 b;
    s64 c;
    s32 d;
    s64 e;
    s64 g;
    f32 x;
    f32 y;
    f32 z;

    if (kind != 6 && kind != 8 && kind != 0xA) {
        return 0;
    }
    if (D_00482888 == NULL || D_0048288C >= 0x20) {
        return 1;
    }
    {
        rec = &D_00482888[D_0048288C];
        switch (kind) {
        case 6:
            a = ScriptArgGetAreaId_3019b0(p);
            b = TargetRefGetId_2e7120(EvObjGetTargetRef_2f9ca0(D_004E7000));
            c = EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 8));
            d = TargetRefGetId_2e7120(EvObjGetTargetRef_2f9ca0(D_004E7000));
            e = EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x10));
            y = ScriptArgGetFloat_301a20(p + 0x18);
            x = ScriptArgGetFloat_301a20(p + 0x20);
            EvTargetSetInitNamed_336ab0(rec, a, b, c, d, e, y, -1, x, 0,
                         ScriptArgGetFloat_301a20(p + 0x28), -1, 0);
            break;
        case 8:
            a = ScriptArgGetAreaId_3019b0(p);
            b = TargetRefGetId_2e7120(EvObjGetTargetRef_2f9ca0(D_004E7000));
            c = EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 8));
            d = TargetRefGetId_2e7120(EvObjGetTargetRef_2f9ca0(D_004E7000));
            e = EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x10));
            z = ScriptArgGetFloat_301a20(p + 0x18);
            y = ScriptArgGetFloat_301a20(p + 0x20);
            x = ScriptArgGetFloat_301a20(p + 0x28);
            g = ScriptArgGetAreaId_3019b0(p + 0x30);
            EvTargetSetInitNamed_336ab0(rec, a, b, c, d, e, z, g, y,
                         EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x38)), x, -1, 0);
            break;
        case 10:
            a = ScriptArgGetAreaId_3019b0(p);
            b = TargetRefGetId_2e7120(EvObjGetTargetRef_2f9ca0(D_004E7000));
            c = EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 8));
            d = TargetRefGetId_2e7120(EvObjGetTargetRef_2f9ca0(D_004E7000));
            e = EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x10));
            z = ScriptArgGetFloat_301a20(p + 0x18);
            y = ScriptArgGetFloat_301a20(p + 0x20);
            x = ScriptArgGetFloat_301a20(p + 0x28);
            g = ScriptArgGetAreaId_3019b0(p + 0x30);
            EvTargetSetInitNamed_336ab0(rec, a, b, c, d, e, z, g, y,
                         EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x38)), x,
                         ScriptArgGetAreaId_3019b0(p + 0x40),
                         EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x48)));
            break;
        }
        D_0048288C = D_0048288C + 1;
    }
    return 1;
}
