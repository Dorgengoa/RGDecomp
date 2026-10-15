#include "types.h"

/* Known-positive sibling shape of EvCmdPartyGetLeaderId_267910 (byte-identical, in cunits). */

extern void * GetGameData_1fede0(void);
extern s32 ScriptSlotStoreIntRef_2cc900(s32, s32);

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0xC];
    struct Obj1 *mC;
};

struct Obj1 {
    u8 pad000[0x24];
    s16 m24;
};

s32 AiCmdOptionsGetTacticsMode_2c5880(s32 p0)
{
    struct Obj0 *r0;
    s16 t1;
    s32 r1;

    r0 = GetGameData_1fede0();
    t1 = r0->mC->m24;
    r1 = ScriptSlotStoreIntRef_2cc900(p0, t1);
    return 1;
}
