/* rgp:protos */
#line 1
#include "types.h"

/* jalr $25 == a C++ VIRTUAL call.  Slot byte offset = 8 + 4*index,
   because mwcc's vtable carries two leading words. */

struct Rec { u8 pad00[0x4]; void *f4; };
struct CObj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Rec * v205() { return VCM0(Rec *, 0x33C); }
};

struct Hit2 { u8 pad00[0xC]; void *fC; };
struct Hit { u8 pad00[0x10]; Hit2 *f10; };
struct Reg { u8 pad00[0x14]; void *f14; void *f18; u8 pad1C[0x4]; void *f20; };
struct Sys { u8 pad000[0x244]; void *f244; };
struct Reg2 { u8 pad00[0x20]; Sys *f20; };

extern "C" s32 D_004825DC;
extern "C" Reg *GetGameData_1fede0(void);
extern "C" Hit *InvFindInCategoryRange_3c8370(void *, void *, s32, s32, s32, s32);
extern "C" char *ScriptStrTableNextScratch_2ccde0(s32 *);
extern "C" void *CharaMgrPoolFindById_3a8c60(void *, void *);
extern "C" char *MsgGetTextByIndex_279040(s32);
extern "C" void Sprintf_1343b8(char *, char *, void *, void *);
extern "C" u32 strlen(char *);
extern "C" void CharaSysEventLogKeyAdd_3a33b0(void *, s32, s32);
extern "C" void CharaEventLogRecord_3a62f0(void *, s32, s32, s32, s32);
extern "C" void CharaSysEventLogKeyRemove_3a3380(void *, s32, int);
extern "C" void FieldHudLogOpen_203fb0(void);

extern "C" void CharaEventLogAddItemUse_2ccc40(void *a, void *b)
{
    s32 out;
    char *buf;
    Reg *e;
    Hit *r;
    void *u;
    Rec *w;
    Hit2 *r2;
    void *z;

    if (D_004825DC == 0) {
        return;
    }
    e = GetGameData_1fede0();
    r = InvFindInCategoryRange_3c8370(e->f18, b, 0, -1, 0, 0);
    if (r == 0) {
        return;
    }
    buf = ScriptStrTableNextScratch_2ccde0(&out);
    u = CharaMgrPoolFindById_3a8c60(e->f14, a);
    if (buf == 0) {
        return;
    }
    if (u == 0) {
        return;
    }
    w = ((CObj *)u)->v205();
    r2 = r->f10;
    if (r2 == 0) {
        return;
    }
    if (w == 0) {
        return;
    }
    Sprintf_1343b8(buf, MsgGetTextByIndex_279040(0x26), w->f4, r2->fC);
    if (strlen(buf) < 0x50) {
        z = ((Reg2 *)GetGameData_1fede0())->f20->f244;
        if (z == 0) {
            return;
        }
        CharaSysEventLogKeyAdd_3a33b0(e->f20, out, 0);
        CharaEventLogRecord_3a62f0(z, out, out, -2, 1);
        CharaSysEventLogKeyRemove_3a3380(e->f20, out, 0);
        FieldHudLogOpen_203fb0();
    }
}
