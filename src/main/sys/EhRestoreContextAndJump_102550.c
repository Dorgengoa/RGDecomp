#include "types.h"
#include "mwruntime.h"

/* MW C++ runtime TransferControl: restore the catch frame from the
   ThrowContext ($a0) and jump to the handler ($a2). MW-shipped asm with no C
   emitter (proof build/libdeasm/102550/NOTES.md); asm shell per user ruling
   2026-10-12 #2. */
asm void EhRestoreContextAndJump_102550(void)
{
    __TRANSFER_CONTROL()
}
