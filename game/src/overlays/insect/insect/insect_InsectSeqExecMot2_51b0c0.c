/* rgp:protos */
#define RGP_SELF_insect_InsectSeqExecMot2_51b0c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051B0C0 -- 336 bytes.  A two-phase scripted line: phase 0 formats
 * the caption and starts the actor's talk, phase 1 waits for the talk timer to
 * pass the recorded deadline. */

typedef struct Actor {
    u8 pad0000[0x38];
    s8 f38;                         /* +0x38 */
    s8 f39;                         /* +0x39 */
    u8 pad003A[0x4C - 0x3A];
    s8 f4C;                         /* +0x4C */
} Actor;

typedef struct Step {
    u8  pad0000[0x4];
    s32 f4;                         /* +0x04 */
    u8  pad0008[0xC - 0x8];
    u8  fC[0x14];                   /* +0x0C */
    f32 f20;                        /* +0x20 */
    f32 f24;                        /* +0x24 */
    s32 f28;                        /* +0x28 */
} Step;

/*rgp*/
/*rgp*/
extern void   memset(void *p, s32 v, s32 n);
extern void   Sprintf_1343b8(void *b, const u8 *f, ...);
/*rgp*/
/*rgp*/
/*rgp*/

extern u8 insect_D_005253D8[];
extern u8 insect_D_005253E0[];
extern u8 insect_D_005253E8[];

s32 insect_InsectSeqExecMot2_51b0c0(Step *p)
{
    u8     buf[0x20] __attribute__((aligned(16)));
    void  *s;
    Actor *a;
    f32    t;

    s = InsectBattleGet_31a8d0();
    if (p == 0 || s == 0) {
        return 1;
    }
    a = ((Actor *)insect_InsectBattleGetActorSlot_50db40(s, 0));
    if (a == 0) {
        return 1;
    }
    switch (p->f4) {
    case 0:
        memset(buf, 0, 0x20);
        if (a->f38 == 0xC) {
            if (a->f4C > 0) {
                Sprintf_1343b8(buf, insect_D_005253D8, p->fC);
            } else {
                Sprintf_1343b8(buf, insect_D_005253E0, p->fC);
            }
        } else {
            Sprintf_1343b8(buf, insect_D_005253E8, p->fC, a->f39 + 1);
        }
        insect_InsectPieceMotionQueueClear_514320(a);
        insect_InsectPieceMotionQueuePush_514510(a, buf, p->f28, p->f20, p->f24);
        p->f4 = p->f4 + 1;
        break;
    case 1:
        t = p->f24;
        if (insect_InsectPieceGetMotionPhase_5142d0(a) >= t) {
            return 1;
        }
        break;
    }
    return 0;
}
