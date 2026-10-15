#include "types.h"

/* factory.bin overlay, 0x004EA120 -- reset the module held in D_00484A60.
 *
 * The jump target is the THUNK at 0x004F6DC0, not factory_FactoryMarkerClearAllSlots_4f6dd0 itself,
 * so the source names the thunk.  `lw $4, -0x710($28)` in the delay slot is the
 * gp global read as the only argument (_gp = 0x00485170).
 */

extern void *D_00484A60;
extern void  factory_FactoryMarkerClearAllSlotsThunk_4f6dd0(void *o);

void factory_FactoryMarkerClearAll_4ea120(void)
{
    factory_FactoryMarkerClearAllSlotsThunk_4f6dd0(D_00484A60);
}
