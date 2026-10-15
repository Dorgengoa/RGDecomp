#include "types.h"
extern void *GetEffectMgr_2d9040(void);
extern s32 ScriptGetCodeAddr_26a200(s64 *);
extern void EffectCreateByName_2e1020(void *,void *,s32,s32);
extern void ScriptSetRefInt_26a1e0(s64 *,s32);
s32 EvCmdEffectCreate_25cc50(s64 *p){u8 local[0x20];void *ctx=GetEffectMgr_2d9040();EffectCreateByName_2e1020(local,ctx,ScriptGetCodeAddr_26a200(p++),4000);ScriptSetRefInt_26a1e0(p,*(s32*)(local+4));return 1;}
