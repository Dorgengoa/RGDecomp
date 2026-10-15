#include "types.h"
/* insect 0x00522CC0 -- run a script through the SB2 VM the overlay keeps in its
 * own frame (0xED0 bytes at $29+0x40), against the command table D_00524590.
 * Three arguments, all marshalled by the caller at 0x004F9820 ($4/$5/$6).
 *
 * D_004851B8 is inside the gp window (_gp = 0x00485170, window
 * 0x47D170..0x48D170), so it stays a PLAIN extern and takes %gp_rel; the table
 * at 0x00524590 is overlay data, outside the window, so it must be `const` or
 * mwcc gives it a %gp_rel relocation that cannot be resolved at link time.
 *
 * `sw $18, 0x48($28)` sits in func_15F270's delay slot, which is the recorded
 * "a store written before a call fills that call's delay slot" shape -- the
 * context publish is written immediately ahead of that call.  ⚠ The sibling
 * 0x00510B30 is the same function with the publish one call LATER, so read the
 * slot rather than copying this one's order. */
typedef struct ScriptVm { u8 raw[0xED0]; } ScriptVm;

extern void *D_004851B8;
extern const u8 D_00524590[];
extern void func_15F140(ScriptVm *vm);
extern void func_15F270(ScriptVm *vm, const u8 *cmds);
extern void func_15F1B0(ScriptVm *vm, s32 b, s32 c);
extern void func_15F3F0(ScriptVm *vm);

void insect_InsectAiCfgParseScript_522cc0(void *ctx, s32 b, s32 c)
{
    ScriptVm sp40;

    func_15F140(&sp40);
    D_004851B8 = ctx;
    func_15F270(&sp40, D_00524590);
    func_15F1B0(&sp40, b, c);
    func_15F3F0(&sp40);
    D_004851B8 = 0;
}
