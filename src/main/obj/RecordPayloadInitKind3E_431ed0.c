#include "types.h"

extern void RecordStateSaveSlotInitMaybe_4324a0(void *);
extern void InsectTeamInit_4324d0(void *);

struct Obj0 {
    s32 m00;
    u8 m04_b0 : 1;
    u8 m04_b1 : 1;
    u8 m04_b2 : 6;
    u8 pad005[7];
    s32 m0C;
};

void RecordPayloadInitKind3E_431ed0(struct Obj0 *p0)
{
    struct Obj0 *l2;
    s32 l1;

    p0->m00 = 0x26E;
    p0->m04_b0 = 0;
    p0->m04_b1 = 0;
    RecordStateSaveSlotInitMaybe_4324a0((u8 *)p0 + 5);
    p0->m0C = 0;
    l2 = (struct Obj0 *)((u8 *)p0 + 0x10);
    l1 = 0;
    do {
        InsectTeamInit_4324d0(l2);
        l1 = (l1 + 1);
        l2 = (struct Obj0 *)((u8 *)l2 + 0xE0);
    } while (l1 < 0x14);
}
