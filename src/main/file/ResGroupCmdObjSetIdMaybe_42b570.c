#include "types.h"

typedef struct SArg {
    s32 w[2];
} SArg;

extern void * ResGroupListCurElem_42a5d0(void);
extern s32 VariantGetInt_15f780(SArg *);

struct Obj0;

/* MEASURED (this unit, 7-arm sweep): with a SECOND parameter present the
   cursor must be a LOCAL COPY of the argument.  Post-incrementing the
   parameter itself gives it the higher callee-saved register ($18) and the
   count the lower ($17); retail is the other way round.  Reordering the
   locals and naming the count in a local are both INERT (one object sha1). */

struct Obj0 {
    s16 m00;
    s16 m02;
};

extern struct Obj0 *D_00483FE8;

s32 ResGroupCmdObjSetIdMaybe_42b570(SArg *p0, s32 p1)
{
    struct Obj0 *r0;
    SArg *q;
    s32 r1;
    s32 r2;

    q = p0;
    D_00483FE8 = 0;
    r0 = ResGroupListCurElem_42a5d0();
    if (r0 == 0) {
        return 1;
    }
    r1 = VariantGetInt_15f780(q++);
    r0->m00 = r1;
    if (p1 >= 2) {
        r2 = VariantGetInt_15f780(q);
        r0->m02 = r2;
    }
    D_00483FE8 = r0;
    return 1;
}
