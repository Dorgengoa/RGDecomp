#include "types.h"

typedef struct Cur8 { s32 a, b; } Cur8;

extern void *GetMinimapSubGlobal_32c2c0(void);
extern void *GetEntryTableGlobal_32c2e0(void);
extern char *SlotGetInt_15f720(Cur8 *);
extern f32 VariantGetFloat_15f740(Cur8 *);
extern void *EntryListFindByNameInRange_323420(void *, char *, f32, f32);
extern void Vec3Set_32b0b0(void *, f32, f32, f32);
extern void EntryPosRecSetEntry_32b0a0(void *, void *);
extern void MinimapSubAppendPos_32aeb0(void *, void *);

s32 MinimapScriptCmdAddPos_32ad30(Cur8 *q)
{
    void *p;
    void *t;
    void *r;
    char *s;
    f32 a;
    f32 b;
    f32 c;
    u8 buf[16];

    p = GetMinimapSubGlobal_32c2c0();
    t = GetEntryTableGlobal_32c2e0();
    if (p != 0) {
        if (t != 0) {
            s = SlotGetInt_15f720(q++);
            a = VariantGetFloat_15f740(q++);
            b = VariantGetFloat_15f740(q++);
            c = VariantGetFloat_15f740(q);
            r = EntryListFindByNameInRange_323420(t, s, b, 0.0f);
            Vec3Set_32b0b0(buf, a, b, c);
            EntryPosRecSetEntry_32b0a0(buf, r);
            MinimapSubAppendPos_32aeb0(p, buf);
        }
    }
    return 1;
}
