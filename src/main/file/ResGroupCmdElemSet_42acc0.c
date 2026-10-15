#include "types.h"

typedef struct SArg {
    s32 w[2];
} SArg;

extern void * ResGroupListCurElem_42a540(void);
extern s32 VariantGetInt_15f780(SArg *);

/* m08 is 8 bytes wide: retail sign-extends the s32 read with
   dsll32/dsra32 ..,0 and stores it with `sd`. */

extern s16 D_0048400C;

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
    u8 pad004[4];
    s64 m08;
    s16 m10;
    s16 m12;
    s16 m14;
    s16 m16;
    s16 m18;
    s16 m1A;
    s16 m1C;
    s16 m1E;
};

s32 ResGroupCmdElemSet_42acc0(SArg *p0)
{
    struct Obj0 *r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 r7;
    s32 r8;
    s32 r9;
    s32 r10;
    s32 r11;

    r0 = ResGroupListCurElem_42a540();
    if (r0 == 0) {
        return 1;
    }
    r1 = VariantGetInt_15f780(p0++);
    r0->m00 = r1;
    r2 = VariantGetInt_15f780(p0++);
    r0->m02 = r2;
    r3 = VariantGetInt_15f780(p0++);
    r0->m08 = r3;
    r4 = VariantGetInt_15f780(p0++);
    r0->m10 = r4;
    r5 = VariantGetInt_15f780(p0++);
    r0->m12 = r5;
    r6 = VariantGetInt_15f780(p0++);
    r0->m14 = r6;
    r7 = VariantGetInt_15f780(p0++);
    r0->m16 = r7;
    r8 = VariantGetInt_15f780(p0++);
    r0->m18 = r8;
    r9 = VariantGetInt_15f780(p0++);
    r0->m1A = r9;
    r10 = VariantGetInt_15f780(p0++);
    r0->m1C = r10;
    r11 = VariantGetInt_15f780(p0);
    r0->m1E = r11;
    D_0048400C = D_0048400C + 1;
    return 1;
}
