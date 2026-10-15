#include "types.h"
#include "vm_slot.h"
/* insect 0x0051CEA0 -- 60 bytes.  Script native of the D_00485170 family (see
 * insect_InsectAbilityTableCmdResistType_51cac0); the guard is written `if (g == 0) return 0;`, which is
 * the spelling that makes mwcc invert the test into `bnez` over a
 * `b <epilogue>` / `daddu $2,$0,$0` pair at the TOP. */

typedef struct Ctx {
    u8  pad00[0x5C];
    s32 m5C;                        /* +0x5C */
} Ctx;

extern Ctx *D_00485170;
extern s32  func_15F780(Slot *v);

s32 insect_InsectAbilityTableCmdHeaderRelated_51cea0(Slot *v)
{
    if (D_00485170 == 0) {
        return 0;
    }
    D_00485170->m5C = func_15F780(v);
    return 1;
}
