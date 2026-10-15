#include "types.h"

struct E2c6f20 { s32 a; s32 b; };

extern void *D_004DB928[];
extern void *ScriptSlotGetInt_2cc9c0(void *p);
extern s32 ActorGetHpById_2cd870(void *p, s32 *out);
extern void ScriptSlotStoreIntRef_2cc900(void *p, s32 v);

s32 AiCmdGetHp_2c6fe0(struct E2c6f20 *p, s32 kind)
{
    s32 a;
    s32 b;
    s32 r;
    void *x;

    if (*(s32 *)p == 0) {
        x = ScriptSlotGetInt_2cc9c0(p++);
        a = 0;
        r = ActorGetHpById_2cd870(x, &a);
        ScriptSlotStoreIntRef_2cc900(p++, r);
        if (kind == 3) {
            ScriptSlotStoreIntRef_2cc900(p, a);
        }
    } else {
        x = D_004DB928[0];
        b = 0;
        r = ActorGetHpById_2cd870(x, &b);
        ScriptSlotStoreIntRef_2cc900(p++, r);
        if (kind == 2) {
            ScriptSlotStoreIntRef_2cc900(p, b);
        }
    }
    return 1;
}
