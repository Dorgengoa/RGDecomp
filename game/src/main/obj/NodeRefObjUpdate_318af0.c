/* rgp:protos */
#define RGP_SELF_NodeRefObjUpdate_318af0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 t;
    u8 pad[8];
} E0C318;

typedef struct {
    f32 t;
    u8 pad[0x10];
} E14318;

/*rgp*/
/*rgp*/

s32 NodeRefObjUpdate_318af0(u8 *arg0, int rgp_a1, f32 dt)
{
    u8 any;
    u8 *p;
    E14318 *b;
    s32 i;
    E0C318 *a;


    JudgeObjectStep_314360((void *)arg0, (int)rgp_a1, (float)dt);
    if (*(s16 *)(arg0 + 0xB6) != 0) {
        return 0;
    }
    if (!(*(f32 *)(arg0 + 0xC8) < 0.0f)) {
        return 0;
    }
    {
        any = 0;
        p = arg0 + 0x180;
        for (i = 0; i < *(s16 *)(arg0 + 0x680); i++, p += 0x50) {
            any = (any | NodeRefUpdateWorldPos_319290(p)) != 0;
        }
        if (!any) {
            *(s16 *)(arg0 + 0xB6) = 1;
        }
        a = (E0C318 *)(arg0 + 0x684);
        for (i = 0; i < *(s16 *)(arg0 + 0x884); i++, a++) {
            a->t -= dt;
            if (a->t < 0.0f) {
                a->t = 0.0f;
            }
        }
        b = (E14318 *)(arg0 + 0x744);
        for (i = 0; i < *(s16 *)(arg0 + 0x886); i++, b++) {
            b->t -= dt;
            if (b->t < 0.0f) {
                b->t = 0.0f;
            }
        }
    }
    return 0;
}
