#include "types.h"

typedef struct N1AC {
    struct N1AC *m00;
    u8           pad004[0x10];
    void        *m14;
} N1AC;

typedef struct P1AC {
    u8     pad000[0x220];
    N1AC  *m220;
} P1AC;

extern s32 TexAnimSeqFindByName_162e40(void *h, void *arg);
extern void TexAnimSeqStart_162ae0(void *h, s32 r);

void ModelObjTexAnimStartByName_1ac590(P1AC *p, void *arg)
{
    void *h;
    N1AC *n;
    volatile s32 r;
    s32 t;

    for (n = p->m220; n != 0; n = n->m00) {
        h = n->m14;
        if (h == 0) {
            continue;
        }
        t = TexAnimSeqFindByName_162e40(h, arg);
        if (t < 0) {
            continue;
        }
        r = t;
        goto found;
    }
    h = 0;
found:
    if (h != 0) {
        TexAnimSeqStart_162ae0(h, r);
    }
}
