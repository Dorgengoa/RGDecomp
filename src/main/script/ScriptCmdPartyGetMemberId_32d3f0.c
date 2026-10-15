#include "types.h"

extern void *GetGameData_1fede0(void);
extern s32 ScriptSlotGetInt_3348b0(s32);
extern s32 PartyGetMemberId_3c2490(s32, s32);
extern s32 ScriptSlotStoreIntRef_3347f0(s32, s32);

typedef struct Obj0032d3f0 {
    u8 pad000[0x18];
    s32 unk18;
} Obj0032d3f0;

s32 ScriptCmdPartyGetMemberId_32d3f0(s64 *p0)
{
    Obj0032d3f0 *r0;
    s32 t1;

    r0 = GetGameData_1fede0();
    t1 = ScriptSlotGetInt_3348b0((s32)p0++);
    ScriptSlotStoreIntRef_3347f0((s32)p0, PartyGetMemberId_3c2490(r0->unk18, t1));
    return 1;
}
