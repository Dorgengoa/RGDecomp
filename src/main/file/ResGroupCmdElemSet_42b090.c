#include "types.h"

typedef struct SArg {
    s32 w[2];
} SArg;

extern void * ResGroupListCurElem_42a5a0(void);
extern s32 VariantGetInt_15f780(SArg *);
extern f32 VariantGetFloat_15f740(SArg *);

/* m10/m14 are f32 (swc1 off VariantGetFloat_15f740).  The last field is written only
   when the command carried enough arguments: retail falls through into the
   `sh 0x1C` block when p1 < 0xD is false, so the source guard is p1 >= 0xD.
   The D_00484004 increment is shared and duplicated into the bnel slot. */

extern s16 D_00484004;

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
    s16 m04;
    s16 m06;
    s16 m08;
    s16 m0A;
    s16 m0C;
    s16 m0E;
    f32 m10;
    f32 m14;
    s16 m18;
    s16 m1A;
    s16 m1C;
};

s32 ResGroupCmdElemSet_42b090(SArg *p0, s32 p1)
{
    struct Obj0 *r0;
    SArg *q;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 r7;
    s32 r8;
    f32 r9;
    f32 r10;
    s32 r11;
    s32 r12;
    s32 r13;

    q = p0;
    r0 = ResGroupListCurElem_42a5a0();
    if (r0 == 0) {
        return 1;
    }
    r1 = VariantGetInt_15f780(q++);
    r0->m00 = r1;
    r2 = VariantGetInt_15f780(q++);
    r0->m02 = r2;
    r3 = VariantGetInt_15f780(q++);
    r0->m04 = r3;
    r4 = VariantGetInt_15f780(q++);
    r0->m06 = r4;
    r5 = VariantGetInt_15f780(q++);
    r0->m08 = r5;
    r6 = VariantGetInt_15f780(q++);
    r0->m0A = r6;
    r7 = VariantGetInt_15f780(q++);
    r0->m0C = r7;
    r8 = VariantGetInt_15f780(q++);
    r0->m0E = r8;
    r9 = VariantGetFloat_15f740(q++);
    r0->m10 = r9;
    r10 = VariantGetFloat_15f740(q++);
    r0->m14 = r10;
    r11 = VariantGetInt_15f780(q++);
    r0->m18 = r11;
    r12 = VariantGetInt_15f780(q++);
    r0->m1A = r12;
    if (p1 >= 0xD) {
        r13 = VariantGetInt_15f780(q);
        r0->m1C = r13;
    }
    D_00484004 = D_00484004 + 1;
    return 1;
}
