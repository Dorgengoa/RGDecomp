#include "types.h"

/* Clear the flag, then release the semaphore if nothing else holds it.
   PollSema returns negative when the count is already zero, and only then is
   the Signal needed -- so a failed poll is the normal path, not an error.
   The flag store sits in the jal's delay slot, i.e. before the call. */

extern s32 D_0047E020;    /* the semaphore id */
extern s32 D_00481204;

extern s32 PollSema(s32 sema);
extern s32 SignalSema(s32 sema);

void FileReqThreadResume_182670(void)
{
    D_00481204 = 0;
    if (PollSema(D_0047E020) < 0) {
        SignalSema(D_0047E020);
    }
}
