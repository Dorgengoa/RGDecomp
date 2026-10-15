#include "types.h"
#include "eekernel.h"

extern void func_076160(s32);

void iSetAlarm(s32 id)
{
    func_076160(id & 0xFFFF);
    SyncLoad();
}
