#include "types.h"

/* Resume a script VM: run the interpreter from whatever it parked at +0x38,
   and do nothing at all if it parked at zero. */

typedef struct ScriptVm {
    u8 pad00[0x38];
    void *pc;      /* +0x38, 0 = not running */
} ScriptVm;

extern void ScriptVmExec_173b00(ScriptVm *vm, void *pc);

void ScriptVmResume_176ab0(ScriptVm *vm)
{
    if (vm->pc != NULL) {
        ScriptVmExec_173b00(vm, vm->pc);
    }
}
