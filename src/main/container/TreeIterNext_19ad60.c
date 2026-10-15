#include "types.h"
typedef struct N {
    struct N *n0;
    struct N *n4;
    struct N *n8;
} N;

typedef struct O {
    u8 pad0[0x98];
    N *unk98;
} O;

N *TreeIterNext_19ad60(O *arg0)
{
    N *cur;
    N *t;
    N *u;

    cur = arg0->unk98;
    if (cur == NULL) {
        return NULL;
    }
    if (cur->n4 != NULL) {
        arg0->unk98 = cur->n4;
        return cur;
    }
    if (cur->n8 != NULL) {
        arg0->unk98 = cur->n8;
        return cur;
    }
    t = cur->n0;
    if (t != NULL) {
        arg0->unk98 = t;
        while (arg0->unk98 != NULL) {
            if (arg0->unk98->n8 != NULL) {
                arg0->unk98 = arg0->unk98->n8;
                return cur;
            }
            arg0->unk98 = arg0->unk98->n0;
        }
    } else {
        arg0->unk98 = NULL;
    }
    return cur;
}
