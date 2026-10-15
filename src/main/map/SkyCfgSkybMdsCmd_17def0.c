#include "types.h"

typedef struct E8_FUN_0017def0 {
    s32 a;
    s32 b;
} E8_FUN_0017def0;

typedef struct B_FUN_0017def0 {
    u8 pad000[0x194];
    char names[4][0x20];
    f32 vals[4];
} B_FUN_0017def0;

extern B_FUN_0017def0 *D_004811AC;
extern f32 D_0047D1FC;

extern s32 VariantGetInt_15f780(E8_FUN_0017def0 *p);
extern char *SlotGetInt_15f720(E8_FUN_0017def0 *p);
extern f32 VariantGetFloat_15f740(E8_FUN_0017def0 *p);
extern char *strcpy(char *d, const char *s);

s32 SkyCfgSkybMdsCmd_17def0(E8_FUN_0017def0 *q)
{
    s32 idx;
    s32 ok;
    char *name;
    f32 v;

    idx = VariantGetInt_15f780(q++);
    if (idx >= 0) {
        if (idx >= 4) { ok = 0; } else { ok = 1; }
    } else {
        ok = 0;
    }
    if (ok == 0) return 0;
    name = SlotGetInt_15f720(q++);
    if (name != 0) {
        strcpy(D_004811AC->names[idx], name);
    }
    v = VariantGetFloat_15f740(q);
    D_004811AC->vals[idx] = D_0047D1FC * v / 180.0f;
    return 1;
}
