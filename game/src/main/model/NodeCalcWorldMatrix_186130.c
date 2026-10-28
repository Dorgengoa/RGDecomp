/* rgp:protos */
#define RGP_SELF_NodeCalcWorldMatrix_186130 1
#include "port/game_protos.h"
#line 1
/* PARKED s17b: not attempted, no draft read yet this session. See
   asm/matchings/main/NodeCalcWorldMatrix_186130.s and build/b_drafts/NodeCalcWorldMatrix_186130.txt
   (m2c draft already generated, just not worked). */
/* s49m: MATCH */
#include "types.h"
#include "vec.h"

typedef struct { f32 x, y, z, w; } V4;

typedef struct Node {
    u8 pad00[0x0C];
    f32 m0C;
    f32 m10;
    f32 m14;
    f32 m18;
    f32 m1C;
    f32 m20;
    f32 m24;
    f32 m28;
    f32 m2C;
    s16 m30;
    struct Node *m34;
    void *m38;
} Node;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void NodeCalcWorldMatrix_186130(Node *n, Mtx4 *out)
{
    Mtx4 m290 __attribute__((aligned(16)));
    Mtx4 m250 __attribute__((aligned(16)));
    Mtx4 m210 __attribute__((aligned(16)));
    Mtx4 m1D0 __attribute__((aligned(16)));
    V4 c1 __attribute__((aligned(16)));
    V4 b1 __attribute__((aligned(16)));
    V4 a1 __attribute__((aligned(16)));
    V4 c2 __attribute__((aligned(16)));
    V4 b2 __attribute__((aligned(16)));
    V4 a2 __attribute__((aligned(16)));
    V4 c3 __attribute__((aligned(16)));
    V4 b3 __attribute__((aligned(16)));
    V4 a3 __attribute__((aligned(16)));
    Mtx4 m100 __attribute__((aligned(16)));
    Mtx4 mC0 __attribute__((aligned(16)));
    Mtx4 m80 __attribute__((aligned(16)));
    Mtx4 m40 __attribute__((aligned(16)));
    Node *p;

    p = n->m34;
    if (p != 0) {
        if (p->m34 != 0) {
            NodeCalcWorldMatrix_186130(p->m34, &m100);
            NodeCalcLocalMatrix_186400(p, &mC0);
            MtxMul_13d240(&m290, &m100, &mC0);
        } else if (p->m38 != 0) {
            FrameCalcWorldMatrix_148ff0(p->m38, &m80);
            NodeCalcLocalMatrix_186400(p, &m40);
            MtxMul_13d240(&m290, &m80, &m40);
        } else {
            NodeCalcLocalMatrix_186400(p, &m290);
        }
        if (n->m30 != 0) {
            MtxLoad3x4_186ec0(&m250, n);
        } else {
            c1.x = n->m18;
            c1.y = n->m1C;
            c1.z = n->m20;
            b1.x = n->m0C;
            b1.y = n->m10;
            b1.z = n->m14;
            a1.x = n->m24;
            a1.y = n->m28;
            a1.z = n->m2C;
            MatFromSRTVu0_13bc90(&m250, &c1, &b1, &a1);
        }
        MtxMul_13d240(out, &m290, &m250);
        return;
    }
    if (n->m38 != 0) {
        FrameCalcWorldMatrix_148ff0(n->m38, &m210);
        if (n->m30 != 0) {
            MtxLoad3x4_186ec0(&m1D0, n);
        } else {
            c2.x = n->m18;
            c2.y = n->m1C;
            c2.z = n->m20;
            b2.x = n->m0C;
            b2.y = n->m10;
            b2.z = n->m14;
            a2.x = n->m24;
            a2.y = n->m28;
            a2.z = n->m2C;
            MatFromSRTVu0_13bc90(&m1D0, &c2, &b2, &a2);
        }
        MtxMul_13d240(out, &m210, &m1D0);
        return;
    }
    if (n->m30 != 0) {
        MtxLoad3x4_186ec0(out, n);
    } else {
        c3.x = n->m18;
        c3.y = n->m1C;
        c3.z = n->m20;
        b3.x = n->m0C;
        b3.y = n->m10;
        b3.z = n->m14;
        a3.x = n->m24;
        a3.y = n->m28;
        a3.z = n->m2C;
        MatFromSRTVu0_13bc90(out, &c3, &b3, &a3);
    }
}
