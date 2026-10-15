#include "types.h"

struct S8 { s32 a; s32 b; };
struct T { u8 pad000[0xB8]; s32 mB8; };

extern s32 ScriptSlotGetInt_2cc9c0(struct S8 *);
extern struct T *CharaGetAiById_2cedd0(s32);
extern void ScriptSlotStoreIntRef_2cc900(struct S8 *, s32);

s32 AiCmdRouteTestFlags_2c4440(struct S8 *p0)
{
    s32 r1;
    s32 r2;
    struct T *r3;
    s32 m;

    r1 = ScriptSlotGetInt_2cc9c0(p0++);
    r2 = ScriptSlotGetInt_2cc9c0(p0++);
    r3 = CharaGetAiById_2cedd0(r1);
    if (r3 != 0) {
        m = r3->mB8 & r2;
        if (m != 0) {
            ScriptSlotStoreIntRef_2cc900(p0, 1);
        } else {
            ScriptSlotStoreIntRef_2cc900(p0, 0);
        }
    }
    return 1;
}
