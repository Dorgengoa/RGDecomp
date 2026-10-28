/* rgp:protos */
#define RGP_SELF_ScriptVmResume_176ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Resume a script VM: run the interpreter from whatever it parked at +0x38,
   and do nothing at all if it parked at zero. */

typedef struct ScriptVm {
    u8 pad00[0x38];
    void *pc;      /* +0x38, 0 = not running */
} ScriptVm;

/*rgp*/

void ScriptVmResume_176ab0(ScriptVm *vm)
{
    if (vm->pc != NULL) {
        ScriptVmExec_173b00(vm, vm->pc);
    }
}
