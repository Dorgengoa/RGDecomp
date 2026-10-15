#include "types.h"

/* Member access, not a pointer walk: the cast walk makes mwcc keep p+4 in a
   third callee-saved register. */

typedef struct {
    s32 m0;
    void *m4;
    s32 m8;
} Obj_183720;

extern void OperatorDeleteArray_100820(void *p);
extern void OperatorDelete_100840(void *p);

void *CdDirTableDtor_183720(Obj_183720 *p, s32 n)
{
    if (p != 0) {
        OperatorDeleteArray_100820(p->m4);
        p->m4 = 0;
        p->m8 = 0;
        if ((s16)n > 0) {
            OperatorDelete_100840(p);
        }
    }
    return p;
}
