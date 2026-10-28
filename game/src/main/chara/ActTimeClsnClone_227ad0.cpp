#pragma opt_propagation off
#pragma inline_depth(8)
#include "types.h"

extern "C" s32 StrPoolIntern_302fd0(s32, s32, s32);

struct S227ad0 {
    f32 m0;
    s32 m4;
    s32 m8;
    f32 mC;
    f32 m10;
    f32 m14;
    s32 m18;

    void clear() {
        m0 = 0.0f;
        m4 = 0;
        m8 = 0;
        mC = 0.0f;
        m10 = 0.0f;
        m14 = 0.0f;
        m18 = -1;
    }
    bool load(const S227ad0 *s, s32 a2, s32 a3) {
        clear();
        if (a2 == 0 || a3 == 0) {
            return false;
        }
        if (s == 0 || s->m4 == 0 || s->m8 == 0) {
            return false;
        }
        m0 = s->m0;
        m4 = s->m4;
        m8 = s->m8;
        mC = s->mC;
        m10 = s->m10;
        m14 = s->m14;
        m18 = s->m18;
        if ((m4 = StrPoolIntern_302fd0(a3, m4, a2)) == 0) {
            return false;
        }
        if ((m8 = StrPoolIntern_302fd0(a3, m8, a2)) == 0) {
            return false;
        }
        return true;
    }
};

struct O227ad0 {
    f32 m0;
    S227ad0 sub;

    bool load(const O227ad0 *s, s32 a2, s32 a3) {
        m0 = -1.0f;
        sub.clear();
        if (a2 == 0 || a3 == 0 || s == 0) {
            return false;
        }
        m0 = s->m0;
        return sub.load(&s->sub, a2, a3);
    }
};

extern "C" u32 ActTimeClsnClone_227ad0(O227ad0 *self, const O227ad0 *src, s32 a2, s32 a3)
{
    S227ad0 *d;
    const S227ad0 *s;
    bool ok;

    self->m0 = -1.0f;
    self->sub.clear();
    if (a2 == 0 || a3 == 0 || src == 0) {
        return (bool)(false);
    }
    s = &src->sub;
    d = &self->sub;
    self->m0 = src->m0;
    d->clear();
    if (a2 == 0 || a3 == 0 || s == 0 || s->m4 == 0 || s->m8 == 0) {
        return (bool)(false);
    }
    d->m0 = s->m0;
    d->m4 = s->m4;
    d->m8 = s->m8;
    d->mC = s->mC;
    d->m10 = s->m10;
    d->m14 = s->m14;
    d->m18 = s->m18;
    if ((d->m4 = StrPoolIntern_302fd0(a3, d->m4, a2)) == 0) {
        return (bool)(false);
    }
    if ((d->m8 = StrPoolIntern_302fd0(a3, d->m8, a2)) != 0) {
        goto okl;
    }
    return (bool)(false);
okl:
    ok = true;
    return (bool)(ok);
}
