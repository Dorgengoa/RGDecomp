#include "types.h"

extern void VariantPoolFireScopeCalls_3d9e70(s8 *, s32);
extern void VariantPoolTrimScope_3d9f40(s8 *);
extern void VariantPoolScopeLeave_3d9ff0(s8 *);
extern void VariantPoolScopeEnter_3da020(s8 *);
extern u8 *ScriptOpSkipArgs_3da0e0(s8 *, s32, s32, u8 *);
extern u8 *ScriptEmitCmdHandlerMaybe_3da110(s8 *, s32, s32, u8 *);
extern u8 *ScriptBinaryOpExec_3da740(s8 *, s32, s32, u8 *);
extern u8 *ScriptEvalQueryOpMaybe_3daaf0(s8 *, s32, s32, u8 *, s32);
extern void VariantPoolReset_3e01f0(void);
extern s32 D_00483960;
extern s32 D_00483964;
extern s8 *D_00483968;
extern s8 D_0048396C;

s8 *ScriptExecOpStream_3dffa0(s8 *arg0, s32 arg1, u8 *arg2, s32 arg3)
{
    s8 *old;
    u8 *end;
    u8 c;
    s32 op;
    s32 lo;
    s16 n;
    s8 *r;

    if (arg2 == NULL || arg1 <= 0) {
        return NULL;
    }
    if (D_00483960 == 0 || D_00483964 == 0) {
        return NULL;
    }
    *(s32 *)arg0 = arg3;
    old = D_00483968;
    D_0048396C = 0;
    D_00483968 = arg0;
    VariantPoolReset_3e01f0();
    end = arg2 + arg1 - 1;
    while (((arg2 != NULL) ^ 1) == 0 && arg2 <= end) {
        c = *arg2;
        op = ((s32)c >> 4) & 0xF;
        lo = c & 0xF;
        arg2++;
        switch (op) {
        case 0:
        case 2:
            arg2 = ScriptEvalQueryOpMaybe_3daaf0(arg0, op, lo, arg2, arg3);
            break;
        case 8:
            arg2 = ScriptBinaryOpExec_3da740(arg0, op, lo, arg2);
            break;
        case 3:
        case 4:
            arg2 = ScriptEmitCmdHandlerMaybe_3da110(arg0, op, lo, arg2);
            break;
        case 1:
            arg2 = ScriptOpSkipArgs_3da0e0(arg0, op, lo, arg2);
            break;
        case 5:
            c = *arg2;
            arg2++;
            switch (c) {
            case 1:
                VariantPoolScopeEnter_3da020(arg0);
                break;
            case 2:
                VariantPoolScopeLeave_3d9ff0(arg0);
                VariantPoolTrimScope_3d9f40(arg0);
                break;
            case 3:
                VariantPoolScopeEnter_3da020(arg0);
                break;
            case 4:
                VariantPoolScopeLeave_3d9ff0(arg0);
                VariantPoolTrimScope_3d9f40(arg0);
                break;
            }
            break;
        case 6:
            arg2++;
            VariantPoolFireScopeCalls_3d9e70(arg0, 1);
            break;
        case 7:
            arg2++;
            VariantPoolFireScopeCalls_3d9e70(arg0, 1);
            break;
        }
    }
    VariantPoolFireScopeCalls_3d9e70(arg0, 0);
    n = *(s16 *)(arg0 + 0xE08);
    r = NULL;
    if (n > 0) {
        r = arg0 + (n - 1) * 0x38 + 8;
    }
    D_00483968 = old;
    return r;
}
