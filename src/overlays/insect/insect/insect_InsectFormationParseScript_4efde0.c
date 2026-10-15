#include "types.h"
/* insect 0x004EFDE0 -- the THIRD member of the script-runner family
 * (0x00522CC0 / 0x00510B30 / here): same 0xED0-byte VM frame at $29+0x40 and
 * the same four calls, with its own command table (D_005249F0) and its own
 * context global (D_00484F58, at _gp-0x218 and so inside the gp window).
 * ⚠ The publish sits in func_15F3F0's delay slot as in 0x00510B30, and one call
 * EARLIER in 0x00522CC0.  Read the delay slot per member; the family shares
 * everything else. */
typedef struct ScriptVm { u8 raw[0xED0]; } ScriptVm;

extern void *D_00484F58;
extern const u8 D_005249F0[];
extern void func_15F140(ScriptVm *vm);
extern void func_15F270(ScriptVm *vm, const u8 *cmds);
extern void func_15F1B0(ScriptVm *vm, s32 b, s32 c);
extern void func_15F3F0(ScriptVm *vm);

void insect_InsectFormationParseScript_4efde0(void *ctx, s32 b, s32 c)
{
    ScriptVm sp40;

    func_15F140(&sp40);
    func_15F270(&sp40, D_005249F0);
    func_15F1B0(&sp40, b, c);
    D_00484F58 = ctx;
    func_15F3F0(&sp40);
    D_00484F58 = 0;
}
