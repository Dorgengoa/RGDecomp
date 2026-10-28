/* rgp:protos */
#define RGP_SELF_Base58EncodeChecked_42f120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern void strcat(s8 *arg0, s8 *arg1);
extern s32 strlen(s8 *arg0);

s32 Base58EncodeChecked_42f120(u8 *arg0, s32 arg1, s8 *arg2)
{
    s64 sp68;
    u8 sp58[0xC];
    s64 sp50;
    s32 var_18;
    u8 *var_17;
    s32 var_16;
    s32 var_4;

    var_18 = arg1;
    var_17 = arg0;
    *arg2 = 0;
    while (var_18 > 0) {
        sp68 = 0;
        var_16 = var_18;
        if (var_18 > 8) {
            var_16 = 8;
        }

        for (var_4 = 0; var_4 < var_16; var_4++) {
            ((u8 *)&sp68)[var_4] = *var_17++;
        }
        Base58EncodeBlock_42f2d0(sp68, sp58);
        sp58[0xB] = 0;
        if (Base58DecodeBlock_42f200(sp58, &sp50) == 0 || sp68 != sp50) {
            return -1;
        }
        strcat(arg2, (s8 *)sp58);
        var_18 -= var_16;
    }
    return strlen(arg2);
}
