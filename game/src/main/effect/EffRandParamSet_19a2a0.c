/* rgp:protos */
#define RGP_SELF_EffRandParamSet_19a2a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern s32 strcmp(s32, void *);

typedef rg_u128 u128;

extern u8 D_0045A030[];
extern u8 D_0045A038[];
extern u8 D_0045A040[];
extern u8 D_0045A048[];
extern u8 D_0045A050[];
extern u8 D_0045A058[];

struct Obj0 {
    s32 m00;
    s32 m04;
    u8 pad008[0x8];
    u128 m10;
    u128 m20;
};

struct Obj1 { u128 m00; };
struct Obj2 { u128 m00; };

void EffRandParamSet_19a2a0(struct Obj0 *p0, s32 p1, s32 p2, struct Obj1 *p3, struct Obj2 *p4)
{
    s32 a;
    s32 b;

    if (p2 == 0) {
        a = 0;
    } else if (Strcasecmp_1345b8(p2, D_0045A030) == 0) {
        a = 1;
    } else if (Strcasecmp_1345b8(p2, D_0045A038) == 0) {
        a = 2;
    } else if (Strcasecmp_1345b8(p2, D_0045A040) == 0) {
        a = 3;
    } else if (Strcasecmp_1345b8(p2, D_0045A048) == 0) {
        a = 4;
    } else {
        a = 0;
    }
    if (p1 == 0) {
        b = 0;
    } else if (strcmp(p1, D_0045A050) == 0) {
        b = 1;
    } else if (strcmp(p1, D_0045A058) == 0) {
        b = 2;
    } else {
        b = 0;
    }
    p0->m00 = b;
    p0->m04 = a;
    p0->m10 = p3->m00;
    p0->m20 = p4->m00;
}
