/* rgp:protos */
#define RGP_SELF_EffTexResStepAnim_1a8460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 pad[3];
    void *fC;
    s32 f10;
} T_001a8460;

/*rgp*/
/*rgp*/

void EffTexResStepAnim_1a8460(T_001a8460 *p, s32 v)
{
    void *q;

    if (v == p->f10) return;
    p->f10 = v;
    q = p->fC;
    if (q != 0) {
        TexAnimSeqUpdate_163dd0(q, 1.0f);
        GetDrawCtx_15de80();
    }
}
