#include "types.h"

typedef struct E8_FUN_00322e20 {
    s32 a;
    s32 b;
} E8_FUN_00322e20;

extern void *GetEntryTableGlobal_32c2e0(void);
extern void *EntryTableGetCurrent_323530(void *a);
extern f32 VariantGetFloat_15f740(E8_FUN_00322e20 *p);
extern void EntrySetOrigin_323c00(void *b, f32 x, f32 y);

s32 EntryScriptCmdSetOrigin_322e20(E8_FUN_00322e20 *q)
{
    void *a;
    void *b;
    f32 x;
    f32 y;

    a = GetEntryTableGlobal_32c2e0();
    if (a == 0) return 0;
    b = EntryTableGetCurrent_323530(a);
    if (b == 0) return 0;
    x = VariantGetFloat_15f740(q++);
    y = VariantGetFloat_15f740(q);
    EntrySetOrigin_323c00(b, x, y);
    return 1;
}
