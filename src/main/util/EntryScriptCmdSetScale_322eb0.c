#include "types.h"

extern void *GetEntryTableGlobal_32c2e0(void *);
extern void *EntryTableGetCurrent_323530(void *);
extern f32 VariantGetFloat_15f740(void *);
extern void EntrySetScale_323c10(void *, f32);

s32 EntryScriptCmdSetScale_322eb0(void *p)
{
    void *a;
    void *b;
    f32 f;

    a = GetEntryTableGlobal_32c2e0(p);
    if (a == 0) return 0;
    b = EntryTableGetCurrent_323530(a);
    if (b == 0) return 0;
    f = VariantGetFloat_15f740(p);
    EntrySetScale_323c10(b, f);
    return 1;
}
