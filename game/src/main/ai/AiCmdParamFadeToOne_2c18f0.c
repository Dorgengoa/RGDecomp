/* rgp:protos */
#define RGP_SELF_AiCmdParamFadeToOne_2c18f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8_2C18 {
    u8 b[8];
} E8_2C18;

extern void *D_004DB928[];

/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdParamFadeToOne_2c18f0(E8_2C18 *p, s32 mode)
{
    void *ctx;
    void *x;
    void *y;

    ctx = GetCurrentScene_1f5be0();
    x = D_004DB928[0];
    if (mode == 2) {
        x = ScriptSlotGetInt_2cc9c0(p++);
    }
    y = ScriptSlotGetInt_2cc9c0(p);
    ParamTableFadeToOne_1cf9e0(ctx, x, y);
    return 1;
}
