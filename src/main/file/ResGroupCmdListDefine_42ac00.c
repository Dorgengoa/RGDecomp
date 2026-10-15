#include "types.h"

typedef struct SArg {
    s32 w[2];
} SArg;

extern s32 VariantGetInt_15f780(SArg *);
extern s32 ResGroupListAppendNew_42c070(s32 *, s32, s32);

/* %hi/%lo on D_004684C0 => incomplete array.  The scan is a for(;;) with two
   breaks: retail puts the terminator test at the TOP with the back edge on
   the KEY compare, which a `for (; e->k >= 0; e++)` rotates away from.
   The trailing `D_00483FF8 = r3` is one statement, duplicated into the bltzl
   delay slot. */

extern s32 *D_00483FE0;
extern s32 D_00483FF8;
extern s32 D_00483FFC;
extern s16 D_00484010;

struct Pair;

struct Pair {
    s32 k;
    s32 v;
};

extern struct Pair D_004684C0[];

s32 ResGroupCmdListDefine_42ac00(SArg *p0)
{
    struct Pair *e;
    s32 r1;
    s32 r2;
    s32 r3;

    D_00484010 = -1;
    D_00483FF8 = 0;
    r1 = VariantGetInt_15f780(p0++);
    r2 = VariantGetInt_15f780(p0);
    r3 = ResGroupListAppendNew_42c070(D_00483FE0, r1, r2);
    e = D_004684C0;
    for (;;) {
        if (e->k < 0) {
            break;
        }
        if (e->k == r1) {
            *D_00483FE0 = e->v;
            break;
        }
        e++;
    }
    D_00483FF8 = r3;
    D_00484010 = 0;
    D_00483FFC = 0;
    return 1;
}
