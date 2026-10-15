#include "types.h"

typedef struct SArg {
    s32 w[2];
} SArg;

extern void * ResGroupListCurElem_42a510(void);
extern s32 VariantGetInt_15f780(SArg *);

struct Obj0;

struct Obj0 {
    u8 pad000[2];
    s16 m02;
    s16 m04;
};

s32 ResGroupCmdObjSetPair_42ab40(SArg *p0)
{
    struct Obj0 *r0;
    s32 r1;
    s32 r2;

    r0 = ResGroupListCurElem_42a510();
    if (r0 == 0) {
        return 1;
    }
    r1 = VariantGetInt_15f780(p0++);
    r0->m02 = r1;
    r2 = VariantGetInt_15f780(p0);
    r0->m04 = r2;
    return 1;
}
