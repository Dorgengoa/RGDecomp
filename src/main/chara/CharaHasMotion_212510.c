#include "types.h"

typedef struct T_00212510 {
    u8 pad1F0[0x1F0];
    s32 f1F0;
    s32 f1F4;
    s32 f1F8;
} T_00212510;

typedef struct S_00212510 {
    u8 pad3F4[0x3F4];
    T_00212510 *f3F4;
} S_00212510;

extern s32 MotionListFindByName_1721d0(s32 *, char *, s32 *, s32 *);

s32 CharaHasMotion_212510(S_00212510 *self, char *name)
{
    s32 buf[3];
    s32 v28;
    s32 v2C;
    T_00212510 *t;
    s32 r;

    if (name != 0) {
        if (name[0] == 0x23) return 1;
    }
    t = self->f3F4;
    if (t == 0) goto zero;
    if (name != 0) goto ok;
zero:
    r = 0;
    goto out;
ok:
    buf[0] = t->f1F0;
    buf[1] = t->f1F4;
    buf[2] = t->f1F8;
    r = MotionListFindByName_1721d0(buf, name, &v28, &v2C);
out:
    return r != 0;
}
