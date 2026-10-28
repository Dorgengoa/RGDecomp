/* rgp:protos */
#define RGP_SELF_RecordPayloadInitKind32_432180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern void memset(void *, s32, s32);

typedef struct Obj {
    s32 unk0;
    u8 f0 : 1;
    u8 f1 : 1;
    u8 fr : 6;
    u8 a5[4];
    u8 a9[7];
    u8 b10[0xE0];
    u8 bF0[0xE0];
    u8 c1D0[0x11E];
    s16 unk2EE;
    s16 unk2F0;
    u8 pad2F2[2];
    s32 unk2F4;
    u8 d2F8[20][0xE0];
} Obj;

void RecordPayloadInitKind32_432180(Obj *arg0)
{
    u8 *q;
    s32 i;
    u8 *p;
    arg0->unk0 = 0x1F6;
    arg0->f0 = 0;
    arg0->f1 = 0;
    p = arg0->a5;
    RecordStateSaveSlotInitMaybe_4324a0(p);
    RecordStateSaveSlotInitMaybe_4324a0(p + 4);
    p = arg0->b10;
    InsectTeamInit_4324d0(p);
    InsectTeamInit_4324d0(p + 0xE0);
    memset(arg0->c1D0, 0, 0x11E);
    arg0->unk2EE = 0;
    arg0->unk2F0 = 0;
    arg0->unk2F4 = 0;
    q = arg0->d2F8[0];
    for (i = 0; i < 20; i++) {
        InsectTeamInit_4324d0(q);
        q += 0xE0;
    }
}
