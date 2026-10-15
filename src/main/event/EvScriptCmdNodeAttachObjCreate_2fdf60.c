#include "types.h"

/* ---- mechanical m2c draft (lane u31) -------------------------------------
   Produced by build/u31/gendraft.py from m2c --valid-syntax.  This is a
   STARTING POINT, not a match: every M2C_* macro below marks something m2c
   could not type or could not translate.  Replace them as the unit is worked.
   -------------------------------------------------------------------- */
typedef unsigned __int128 u128;
typedef __int128 s128;
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK(x) (0)
#define M2C_SYNC() (0)
#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

s32 GetEventObjMgr_2d1960();                                 /* extern */
M2C_UNK EventObjMgrCreateNodeAttachObj_2e9f90(s32, s32, s32, M2C_UNK *);     /* extern */
s32 ScriptArgGetAreaId_3019b0(s32);                              /* extern */
s32 ScriptArgGetStr_301a00(s32);                              /* extern */
s64 EventStrDup_301aa0(s32);                              /* extern */
M2C_UNK EvScriptTemplatesReset_301c20();                             /* extern */
M2C_UNK EvNodeAttachObjInitByName_3534e0(M2C_UNK *, s64, M2C_UNK, s64, s32, s64, s64, s32, s64, s64, s64, s64); /* extern */
M2C_UNK EvNodeAttachObjCtor_353620(M2C_UNK *);                    /* extern */
extern s32 D_0047F0C0;
extern s32 D_0047F0C4;

s32 EvScriptCmdNodeAttachObjCreate_2fdf60(s32 arg0, s32 arg1) {
    s64 temp_20_2;
    s32 temp_19_2;
    s64 temp_18_2;
    s64 temp_17_2;
    s32 temp_21_2;
    s64 temp_22_2;
    s64 temp_23_2;
    s64 temp_16_2;
    s64 temp_20;
    s64 temp_19;
    s32 temp_18;
    s64 temp_17;
    s64 temp_21;
    s32 temp_22;
    s64 temp_23;
    s64 temp_30;
    s64 temp_16;
    M2C_UNK spC0[81];

    if ((arg1 != 9) && (arg1 != 0xA)) {
        return 0;
    }
    EvScriptTemplatesReset_301c20();
    EvNodeAttachObjCtor_353620(spC0);
    switch (arg1) {                                 /* irregular */
    case 9:
        temp_20_2 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0));
        temp_19_2 = ScriptArgGetAreaId_3019b0(arg0 + 8);
        temp_18_2 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x10));
        temp_17_2 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x18));
        temp_21_2 = ScriptArgGetAreaId_3019b0(arg0 + 0x20);
        temp_22_2 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x28));
        temp_23_2 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x30));
        temp_16_2 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x38));
        EvNodeAttachObjInitByName_3534e0(spC0, temp_20_2, 0, 0, temp_19_2, temp_18_2, temp_17_2, temp_21_2, temp_22_2, temp_23_2, temp_16_2, EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x40)));
        break;
    case 10:
        temp_20 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0));
        temp_19 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x48));
        temp_18 = ScriptArgGetAreaId_3019b0(arg0 + 8);
        temp_17 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x10));
        temp_21 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x18));
        temp_22 = ScriptArgGetAreaId_3019b0(arg0 + 0x20);
        temp_23 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x28));
        temp_30 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x30));
        temp_16 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x38));
        EvNodeAttachObjInitByName_3534e0(spC0, temp_20, 0, temp_19, temp_18, temp_17, temp_21, temp_22, temp_23, temp_30, temp_16, EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x40)));
        break;
    }
    EventObjMgrCreateNodeAttachObj_2e9f90(GetEventObjMgr_2d1960(), D_0047F0C0, D_0047F0C4, spC0);
    return 1;
}
