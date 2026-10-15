#include "types.h"

/* factory.bin overlay, 0x004F6DC0 -- tail-call thunk for factory_FactoryMarkerClearAllSlots_4f6dd0.
 *
 * `j factory_FactoryMarkerClearAllSlots_4f6dd0` with a NOP delay slot: nothing is marshalled, so the
 * parameter passes straight through and mwcc turns the tail call into the jump.
 */

extern void factory_FactoryMarkerClearAllSlots_4f6dd0(void *o);

void factory_FactoryMarkerClearAllSlotsThunk_4f6dd0(void *o)
{
    factory_FactoryMarkerClearAllSlots_4f6dd0(o);
}
