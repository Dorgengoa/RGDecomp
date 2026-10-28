#include "types.h"

extern s32 iSignalSema(s32 sema_id);

/* Interrupt-context wrapper around iSignalSema: forwards its own 4th
   argument register ($7) to iSignalSema, syncs, re-enables interrupts,
   returns 0. Contains a `jal` so mwcc supplies its own prologue/epilogue
   (saving $31) -- do not hand-write the addiu/sd $31 pair retail shows,
   mwcc doubles it up if we do. */

s32 DelayThreadAlarmHandler_117858(void)
{
    asm volatile {
        .set noreorder
        jal   iSignalSema
        daddu $4, $7, $0
        sync
        ei
    }
    return 0;
}
