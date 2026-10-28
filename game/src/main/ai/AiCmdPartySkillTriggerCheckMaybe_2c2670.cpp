/* rgp:protos */
#line 1
#include "types.h"

struct V2c2670 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f48() { return VCM0(s32, 0x48); }
    
    
    
    
    
    
    
    
    s32 f6c(s32 a0) { return VCM(s32, (void *, s32), 0x6C, a0); }
};

extern "C" {
s32 GetCurrentScene_1f5be0();
struct T2c2670 { u8 pad[0x18]; s32 m18; };
T2c2670 *GetGameData_1fede0();
s32 ScriptSlotGetInt_2cc9c0(void *);
s32 PartyCountMembers_3c2010(s32, s32, s32);
V2c2670 *PartyGetNonLeaderChara_3c2700(s32, s32);
V2c2670 *PartyGetLeaderChara_3c2820(s32);
s32 SkillTriggerEvalMaybe_3e1200(void *, V2c2670 *);
void ActionPacketInitAiScriptMaybe_3e2fa0(void *, s32, V2c2670 *, s32);
void ActionPacketReset_3e3d00(void *);
V2c2670 *ActorFindById_3eb870(T2c2670 *, s32);
extern s32 D_004DB928[0x10];
}

extern "C" s32 AiCmdPartySkillTriggerCheckMaybe_2c2670(s32 arg0, s32 arg1)
{
    s32 mode;
    T2c2670 *top;
    V2c2670 *o;
    s32 n;
    s32 i;
    V2c2670 *tbl[4];
    u8 ctx[0x30] __attribute__((aligned(16)));

    mode = 1;
    if (arg1 > 0) {
        mode = ScriptSlotGetInt_2cc9c0((void *)arg0);
    }
    n = D_004DB928[0];
    top = GetGameData_1fede0();
    o = ActorFindById_3eb870(top, n);
    n = GetCurrentScene_1f5be0();
    ActionPacketReset_3e3d00(ctx);
    ActionPacketInitAiScriptMaybe_3e2fa0(ctx, n, o, mode);
    if (o == 0) {
        goto end;
    }
    if (((unsigned char)SkillTriggerEvalMaybe_3e1200(ctx, o)) & 0xFF) {
        goto end;
    }
    if (o->f48() == 0) {
        goto end;
    }
    n = PartyCountMembers_3c2010(top->m18, 1, 1);
    tbl[0] = PartyGetLeaderChara_3c2820(top->m18);
    for (i = 1; i < n; i++) {
        tbl[i] = PartyGetNonLeaderChara_3c2700(top->m18, i - 1);
    }
    for (i = 0; i < n; i++) {
        o = tbl[i];
        if (o == 0) {
            continue;
        }
        if (o->f6c(0) == 0) {
            continue;
        }
        if (((unsigned char)SkillTriggerEvalMaybe_3e1200(ctx, o)) & 0xFF) {
            goto end;
        }
    }
end:
    return 1;
}
