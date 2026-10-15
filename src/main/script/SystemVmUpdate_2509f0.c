#include "types.h"

/* The per-frame step. Run the system VM; if it has gone quiet, give the event
   player a turn; if it is still quiet after that, report nothing to do. */

typedef struct ScriptVm {
    u8 pad00[0x3C];
    s32 busy;      /* +0x3C */
} ScriptVm;

/* Named in config/main.symbols.txt WITH A SIZE. Without one spimdisasm splits
   the +0x3C reference off as a second, unrelated symbol and no compiled object
   can ever name it the same way. */
extern ScriptVm gSystemVm;

extern void ScriptVmResume_176ab0(ScriptVm *vm);
extern void EventSysUpdate_26ac10(void);
extern void EventSceneSysResetMaybe_26b080(void);

s32 SystemVmUpdate_2509f0(void)
{
    ScriptVmResume_176ab0(&gSystemVm);
    if (gSystemVm.busy == 0) {
        EventSysUpdate_26ac10();
    }
    if (gSystemVm.busy != 0) {
        EventSceneSysResetMaybe_26b080();
        return 1;
    }
    return 0;
}
