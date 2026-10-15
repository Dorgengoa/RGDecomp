#include "types.h"

typedef struct E8_2C18 {
    u8 b[8];
} E8_2C18;

extern void *D_004DB928[];

extern void *GetCurrentScene_1f5be0(void);
extern void *ScriptSlotGetInt_2cc9c0(E8_2C18 *p);
extern void ParamTableFadeToOne_1cf9e0(void *a, void *b, void *c);

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
