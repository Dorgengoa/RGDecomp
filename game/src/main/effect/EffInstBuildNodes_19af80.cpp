/* rgp:protos */
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x94];
    s32 unk94;
    s32 unk98;
} A0;

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
} E;

typedef struct {
    u8 pad0[0xC0];
    s32 unkC0;
    u8 *unkC4;
} A2;

extern "C" u8 *ConstructNewArray_100710(s32, void *, s32, s32, s32);
extern "C" s32 MemStackNew_14e1b0(s32, s32);
extern "C" E *TreeIterNext_19ad60(A0 *);
extern "C" bool EffInstNodeBuildEmitterRecs_19b620(s32, s32, u8 *);
extern "C" void EffObjAllocWorkSlots_1a9e40(void *, void *, void *);
extern "C" void EffInstNodeCtor_19b0c0(void);

extern "C" bool EffInstBuildNodes_19af80(A0 *o, s32 arg1, A2 *arg2)
{
    s32 n;
    s32 i;
    bool ok;
    u8 *r;
    E *e;

    EffObjAllocWorkSlots_1a9e40((void *)o, (void *)arg1, (void *)arg2);
    n = 0;
    o->unk98 = o->unk94;
    while (TreeIterNext_19ad60(o) != 0) {
        n++;
    }
    o->unk98 = 0;
    if (n == 0) {
        return 0;
    }
    r = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x120 + 0x10, arg1), (void *)EffInstNodeCtor_19b0c0, 0, 0x120, n);
    arg2->unkC4 = r;
    if (r == 0) {
        return 0;
    }
    arg2->unkC0 = n;
    i = 0;
    ok = 1;
    o->unk98 = o->unk94;
    while ((e = TreeIterNext_19ad60(o)) != 0) {
        if (e->unkC != 0) {
            ok &= EffInstNodeBuildEmitterRecs_19b620(e->unkC, arg1, arg2->unkC4 + i * 0x120);
        }
        i++;
    }
    o->unk98 = 0;
    return ok;
}
