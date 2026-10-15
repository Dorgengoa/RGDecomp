#include "types.h"

/* clone group cg06-002: script-command handler.  Two accepted arg counts
   (2 or 3), a walking cursor with stride 8, a C++ virtual on the global
   manager (vptr at +0x190, vtable slot 0x60), then a run of `count` table
   entries of stride 0xC0 gets one float written at +0x48.
   The only thing that differs across the three members is that offset. */

typedef struct Pair {
    s32 a;
    s32 b;
} Pair;

typedef struct Entry {
    u8 pad00[0x48];
    f32 val;
    u8 padXX[0xC0 - 0x48 - 4];
} Entry;

class Mgr {
    u8 pad000[0x190];
public:
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual Entry *slot60();
};

extern Mgr *D_004826E0;
extern "C" s32 ScriptSlotGetInt_3348b0(Pair *p);
extern "C" f32 ScriptSlotGetFloat_334890(Pair *p);

extern "C" s32 ScriptCmdEffectElemSetAngleAccel_3310a0(Pair *p, s32 n)
{
    Entry *tbl;
    s32 idx;
    s32 count;
    s32 i;
    f32 val;

    if (n != 2 && n != 3) return 0;
    idx = ScriptSlotGetInt_3348b0(p++);
    tbl = D_004826E0->slot60();
    if (tbl == 0) return 1;
    val = ScriptSlotGetFloat_334890(p++);
    count = 1;
    if (n == 3) count = ScriptSlotGetInt_3348b0(p);
    for (i = idx; i < count + idx; i++) {
        tbl[i].val = val;
    }
    return 1;
}
