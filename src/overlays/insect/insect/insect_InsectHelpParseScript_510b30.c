#include "types.h"
/* insect 0x00510B30 -- the sibling of 0x00522CC0: same VM frame, same four
 * calls, a different command table (D_00525150) and a different context global
 * (D_00484FD0, the one 0x005109F0 reads as `lw $2,-0x1A0($28)`).
 * ⚠ The context publish is one call LATER here -- `sw $18, -0x1A0($28)` sits in
 * func_15F3F0's delay slot, not func_15F270's -- so the two siblings differ by
 * where that statement goes.  Read the delay slot, do not copy the sibling. */
typedef struct ScriptVm { u8 raw[0xED0]; } ScriptVm;

extern void *D_00484FD0;
extern const u8 D_00525150[];
extern void func_15F140(ScriptVm *vm);
extern void func_15F270(ScriptVm *vm, const u8 *cmds);
extern void func_15F1B0(ScriptVm *vm, s32 b, s32 c);
extern void func_15F3F0(ScriptVm *vm);

void insect_InsectHelpParseScript_510b30(void *ctx, s32 b, s32 c)
{
    ScriptVm sp40;

    func_15F140(&sp40);
    func_15F270(&sp40, D_00525150);
    func_15F1B0(&sp40, b, c);
    D_00484FD0 = ctx;
    func_15F3F0(&sp40);
    D_00484FD0 = 0;
}
