#include "types.h"

typedef struct V_00228260 {
    f32 f0;
    s32 f4;
} V_00228260;

extern void ScriptCallClear_302b00(s32 *);
extern void *IdentityPtr_302ac0(s32 *);
extern s32 VariantArrayClone_3027d0(void *, void *, s32, s32);

s32 ActTimeEvntClone_228260(V_00228260 *d, V_00228260 *s, s32 c, s32 e)
{
    void *p;
    void *q;
    d->f0 = -1.0f;
    ScriptCallClear_302b00(&d->f4);
    if (c == 0) goto zero;
    if (e == 0) goto zero;
    if (s != 0) goto ok;
zero:
    return 0;
ok:
    d->f0 = s->f0;
    p = IdentityPtr_302ac0(&d->f4);
    q = IdentityPtr_302ac0(&s->f4);
    return VariantArrayClone_3027d0(p, q, c, 0);
}
