/* rgp:protos */
#define RGP_SELF_ActInfoLocus_23ea90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                      /* extern */
/*rgp*/                           /* extern */
/*rgp*/       /* extern */
/*rgp*/            /* extern */
/*rgp*/                         /* extern */
/*rgp*/                              /* extern */
extern u8 D_0044C850[0x400];
extern u8 D_004BCE20[0x400];
extern u8 D_004BCE74[0x400];
extern u8 D_004BCE96[0x400];

s32 ActInfoLocus_23ea90(s32 arg0, s32 arg1) {
    s32 temp_17_2;

s32 temp_16;
s32 temp_20;
s32 temp_19;
s32 temp_19_2;
s32 temp_17;
s32 temp_18;

s32 temp_18_2;
if ((arg1 != 4) && (arg1 != 5)) {
        return 0;
    }
    if (!((*(s32 *)D_004BCE74) != 0)) {
        return 1;
    }
    if (!((*(s16 *)D_004BCE96) < 0x10)) {
        return 1;
    }
    temp_16 = (s32)((u8 *)(*(s32 *)D_004BCE74) + ((*(s16 *)D_004BCE96) * 0x18));
    switch (arg1) {

        /* irregular */
    case 4:
        temp_19 = ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0)));
        temp_18 = LookupNameValueNoCase_1cab50(ScriptArgGetStr_23fba0(arg0 + 8), &(*(s32 *)D_0044C850), 0);
        temp_17 = ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0 + 0x10)));
        ActInfoLocusInitWep_22fa40(temp_16, temp_19, temp_18, temp_17, ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0 + 0x18))));
        break;
    case 5:
        temp_20 = ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0)));
        temp_19_2 = ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0 + 8)));
        temp_18_2 = ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0 + 0x10)));
        temp_17_2 = ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0 + 0x18)));
        ActInfoLocusInit_22f9d0(temp_16, temp_20, temp_19_2, temp_18_2, temp_17_2, ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0 + 0x20))));
        break;
    }
    ActCfgTableSetLocusCount_223bd0(&(*(s32 *)D_004BCE20), (*(s16 *)D_004BCE96) + 1);
    return 1;
}
