/* rgp:protos */
#define RGP_SELF_EvCmdEffectCreate_25cc50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
s32 EvCmdEffectCreate_25cc50(s64 *p){u8 local[0x20] __attribute__((aligned(16)));void *ctx=GetEffectMgr_2d9040();EffectCreateByName_2e1020(local,ctx,ScriptGetCodeAddr_26a200(p++),4000);ScriptSetRefInt_26a1e0(p,*(s32*)(local+4));return 1;}
