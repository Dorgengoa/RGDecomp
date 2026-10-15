#include "types.h"
/* `sq $0` is a u128 member set to 0 (see src/wf/main/SlotRecordReset_3eeca0.c); the
   1.0f then overwrites its last word. */
typedef unsigned __int128 u128;
typedef struct P3869F0 { u128 m00; s32 m10; s32 m14; } P3869F0;
void PlacePointInit_3869f0(P3869F0 *p)
{
    p->m00 = 0;
    *(f32 *)((u8 *)p + 0xC) = 1.0f;
    p->m10 = 0;
    p->m14 = 0;
}
