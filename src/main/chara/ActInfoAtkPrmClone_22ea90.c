#include "types.h"

/* The two entry guards branch in OPPOSITE directions, so they are an `||`.
   StrPoolIntern_302fd0 is the three-argument form (the third register is the
   untouched incoming parameter at the first call site of its family). */

struct A {
    s32 m00;
    s32 m04;
    s32 m08;
};

struct B {
    u8 pad[0x50];
    struct A *m50;
};

struct G {
    s32 m00;
    s32 m04;
    struct B *m08;
};

struct H {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
};

struct Out {
    s16 m00;
    s16 m02;
    s32 m04;
};

extern struct G *GetGameData_1fede0(void);
extern struct H *TableFindByNameHashed_3f86e0(s32, s32);
extern s32 StrPoolIntern_302fd0(s32, s32, s32);

s32 ActInfoAtkPrmClone_22ea90(struct Out *out, struct Out *s, s32 c, s32 d)
{
    struct H *h;

    out->m00 = 0;
    out->m02 = -1;
    out->m04 = 0;
    if (s == 0 || c == 0) {
        return 0;
    }
    out->m00 = s->m00;
    out->m02 = s->m02;
    h = TableFindByNameHashed_3f86e0(GetGameData_1fede0()->m08->m50->m08, s->m04);
    if (h != 0) {
        out->m04 = h->m0C;
    } else {
        out->m04 = StrPoolIntern_302fd0(d, s->m04, c);
    }
    if (out->m04 == 0) {
        return 0;
    }
    return 1;
}
