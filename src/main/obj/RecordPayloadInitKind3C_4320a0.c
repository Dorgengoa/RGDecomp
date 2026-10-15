#include "types.h"

typedef struct S4320a0 {
    s32 unk0;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
} S4320a0;

extern void RecordStateSaveSlotInitMaybe_4324a0(void *arg0);
extern void InsectTeamInit_4324d0(void *arg0);
extern void memset(void *arg0, s32 arg1, s32 arg2);

void RecordPayloadInitKind3C_4320a0(S4320a0 *arg0)
{
    void *var_17;
    s32 var_16;

    arg0->unk0 = 0x25A;
    arg0->b0 = 0;
    arg0->b1 = 0;
    arg0->b2 = 0;
    arg0->b3 = 0;
    RecordStateSaveSlotInitMaybe_4324a0((u8 *)arg0 + 5);
    InsectTeamInit_4324d0((u8 *)arg0 + 0xC);
    memset((u8 *)arg0 + 0xEC, 0, 0x8F);
    *(s32 *)((u8 *)arg0 + 0x17C) = 0;
    var_17 = (u8 *)arg0 + 0x180;
    var_16 = 0;
    do {
        InsectTeamInit_4324d0(var_17);
        var_16 += 1;
        var_17 = (u8 *)var_17 + 0xE0;
    } while (var_16 < 0x14);
}
