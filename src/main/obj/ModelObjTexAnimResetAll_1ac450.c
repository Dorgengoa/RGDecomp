#include "types.h"

struct N1AC450 { struct N1AC450 *f00; u8 pad004[0x10]; void *f14; };
struct T1AC450 { u8 pad000[0x220]; struct N1AC450 *f220; };

extern void TexAnimSeqResetAll_162b20(void *e);

void ModelObjTexAnimResetAll_1ac450(struct T1AC450 *p)
{
    struct N1AC450 *n;
    void *e;

    n = p->f220;
    while (n != 0) {
        e = n->f14;
        if (e != 0) {
            TexAnimSeqResetAll_162b20(e);
        }
        n = n->f00;
    }
}
