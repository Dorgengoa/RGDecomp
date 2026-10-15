#include "types.h"
#include "vm_slot.h"

/* The 0x26a000 script-command family, restored as one translation unit.
   The three slot accessors are `static` here, defined ahead of the commands
   that call them. Across the jal to ScriptGetInt_26a2a0 / ScriptGetCodeAddr_26a200, retail keeps
   GetGameData_1fede0()'s result in a caller-saved register ($a1 or $t0, and $a1/$a2
   hold arguments across the calls in EvCmdStateFlagSet_26a370 / EvCmdStateVarSet_26a520). mwcc only
   does that when it has already compiled the callee in the same TU and knows
   its real clobber set (the MovieReadThread_1d4f50 / ReadBufEndGet_1d32c0 precedent). Every
   other caller of the accessors lives in another object and reaches them by
   absolute address. See config/hosted.txt. */

typedef struct World_0026a {
    u8 pad000[0x10];
    s32 x10;           /* +0x10 */
} World_0026a;

extern World_0026a *GetGameData_1fede0(void);
extern s32 StateFlagTestByName_3ccd10(s32, s32);
extern s32 StateFlagTest_3ccd70(s32, s32);
extern void StateFlagSetByName_3ccaf0(s32, s32, s32, s32);
extern void StateFlagSet_3ccb70(s32, s32, s32, s32);
extern s32 StateVarGetByName_3cca60(s32, s32);
extern s32 StateVarGet_3ccac0(s32, s32);
extern void StateVarSetByName_3cc940(s32, s32, s16, s32);
extern void StateVarSet_3cc9c0(s32, s32, s16, s32);

/* Only a reference slot (type 3) is written through: store into the slot
   it points at. */
static void ScriptSetRefInt_26a1e0(Slot *v, s32 value)
{
    if (v->type == 3) {
        ((Slot *)v->u.p)->u.i = value;
    }
}

/* Code-address reader. */
static s32 ScriptGetCodeAddr_26a200(Slot *v)
{
    if (v->type == 2) {
        return v->u.i;
    }
    return 0;
}

/* Coercing integer reader. */
static s32 ScriptGetInt_26a2a0(Slot *v)
{
    if (v->type == 1) {
        return (s32)v->u.f;
    }
    return v->u.i;
}

s32 EvCmdStateFlagGet_26a2d0(Slot *p)
{
    World_0026a *w;
    u8 v;

    w = GetGameData_1fede0();
    v = 0;
    switch (p->type) {
    case 0:
    case 1:
        v = StateFlagTest_3ccd70(w->x10, ScriptGetInt_26a2a0(p++));
        break;
    case 2:
        v = StateFlagTestByName_3ccd10(w->x10, ScriptGetCodeAddr_26a200(p++));
        break;
    }
    ScriptSetRefInt_26a1e0(p, v);
    return 1;
}

s32 EvCmdStateFlagSet_26a370(Slot *p, s32 n)
{
    World_0026a *w;
    s32 a;
    s32 b;

    w = GetGameData_1fede0();
    switch (p->type) {
    case 0:
    case 1:
        a = ScriptGetInt_26a2a0(p++);
        b = ScriptGetInt_26a2a0(p++) != 0;
        if (n >= 3) {
            StateFlagSet_3ccb70(w->x10, a, b, ScriptGetInt_26a2a0(p++) != 0);
        } else {
            StateFlagSet_3ccb70(w->x10, a, b, 0);
        }
        break;
    case 2:
        a = ScriptGetCodeAddr_26a200(p++);
        b = ScriptGetInt_26a2a0(p++) != 0;
        if (n >= 3) {
            StateFlagSetByName_3ccaf0(w->x10, a, b, ScriptGetInt_26a2a0(p++) != 0);
        } else {
            StateFlagSetByName_3ccaf0(w->x10, a, b, 0);
        }
        break;
    }
    return 1;
}

s32 EvCmdStateVarGet_26a480(Slot *p)
{
    World_0026a *w;
    s32 r;

    w = GetGameData_1fede0();
    r = -1;
    switch (p->type) {
    case 0:
    case 1:
        r = StateVarGet_3ccac0(w->x10, ScriptGetInt_26a2a0(p++));
        break;
    case 2:
        r = StateVarGetByName_3cca60(w->x10, ScriptGetCodeAddr_26a200(p++));
        break;
    }
    ScriptSetRefInt_26a1e0(p, r);
    return 1;
}

s32 EvCmdStateVarSet_26a520(Slot *p, s32 n)
{
    World_0026a *w;
    s32 a;
    s32 b;

    w = GetGameData_1fede0();
    switch (p->type) {
    case 0:
    case 1:
        a = ScriptGetInt_26a2a0(p++);
        b = ScriptGetInt_26a2a0(p++);
        if (n >= 3) {
            StateVarSet_3cc9c0(w->x10, a, b, ScriptGetInt_26a2a0(p++) != 0);
        } else {
            StateVarSet_3cc9c0(w->x10, a, b, 0);
        }
        break;
    case 2:
        a = ScriptGetCodeAddr_26a200(p++);
        b = ScriptGetInt_26a2a0(p++);
        if (n >= 3) {
            StateVarSetByName_3cc940(w->x10, a, b, ScriptGetInt_26a2a0(p++) != 0);
        } else {
            StateVarSetByName_3cc940(w->x10, a, b, 0);
        }
        break;
    }
    return 1;
}
