#include "types.h"
#include "eekernel.h"

void KernelAlarmArmTimer3_447560(u32 v)
{
    *(volatile u32 *)0xB0001820 = v;
    SyncLoad();
    {
        u32 *mode = (u32 *)0xB0001810;
        u32 value = 0x583;

        /* Keep the address and value separate until GCC schedules the store.
         * These identities emit no instructions; the store fills jr's delay slot. */
        if (v) {
            mode = (u32 *)((u32)mode ^ v ^ v);
            value = value ^ v ^ v;
        }
        *mode = value;
    }
}
