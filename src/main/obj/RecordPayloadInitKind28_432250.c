#include "types.h"

extern void RecordStateSaveSlotInitMaybe_4324a0(void *arg0);
extern void InsectTeamInit_4324d0(void *arg0);
extern void InsectTeamMemberInit_4325b0(void *arg0);
extern void memset(void *arg0, s32 arg1, s32 arg2);

typedef struct S {
    s32 x0;
    u8 b0 : 1;
    u8 b1 : 1;
} S;

void RecordPayloadInitKind28_432250(void *arg0)
{
    u8 *p;
    s32 i;
    s8 *q;

    ((S *)arg0)->x0 = 0x192;
    ((S *)arg0)->b0 = 0;
    ((S *)arg0)->b1 = 0;
    RecordStateSaveSlotInitMaybe_4324a0((u8 *)arg0 + 5);
    RecordStateSaveSlotInitMaybe_4324a0((u8 *)arg0 + 9);
    *(s32 *)((u8 *)arg0 + 0x10) = 0;
    p = (u8 *)arg0 + 0x14;
    i = 0;
    do {
        InsectTeamMemberInit_4325b0(p);
        i += 1;
        p += 0x28;
    } while (i < 0xF);
    q = (s8 *)arg0 + 0x26C;
    i = 0;
    do {
        i += 1;
        *q = -1;
        q += 1;
    } while (i < 3);
    *(u8 *)((u8 *)arg0 + 0x26F) = 0;
    InsectTeamInit_4324d0((u8 *)arg0 + 0x270);
    memset((u8 *)arg0 + 0x350, 0, 0x8F);
    *(s16 *)((u8 *)arg0 + 0x3E0) = 0;
    p = (u8 *)arg0 + 0x3E8;
    *(s16 *)((u8 *)arg0 + 0x3E2) = 0;
    i = 0;
    *(s32 *)((u8 *)arg0 + 0x3E4) = 0;
    do {
        InsectTeamInit_4324d0(p);
        i += 1;
        p += 0xE0;
    } while (i < 0x14);
}
