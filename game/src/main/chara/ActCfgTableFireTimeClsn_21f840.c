/* rgp:protos */
#define RGP_SELF_ActCfgTableFireTimeClsn_21f840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 unk0;
    s32 *unk4;
    u8 pad8[4];
    u8 *unkC;
    u8 pad10[0x14];
    s16 unk24;
    u8 pad26[2];
    s16 unk28;
} Node;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void ActCfgTableFireTimeClsn_21f840(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 x, f32 y) {
    u8 *p;
    s32 cnt;
    s32 j;
    s32 i;
    s32 cnt2;
    Node *n;
    s32 *q;

    n = ((Node *)ActCfgTableFindStepByName_222610(arg0, arg2, arg3));
    if (n == NULL) {
        return;
    }
    p = n->unkC;
    if (p != NULL) {
        GetActionMgr_1fdb50();
        cnt = n->unk28;
        for (i = 0; i < cnt; i++, p += 0x20) {
            if (((unsigned char)ActTimeClsnInRange_228560(p, x, y)) != 0) {
                ActTimeClsnFire_227ac0(p, arg1, arg0, n->unk0);
            }
        }
    }
    q = n->unk4;
    cnt2 = n->unk24;
    if (q != NULL) {
        for (j = 0; j < cnt2; j++, q += 2) {
            ActCfgTableFireTimeClsn_21f840(arg0, arg1, q[0], q[1], x, y);
        }
    }
}
