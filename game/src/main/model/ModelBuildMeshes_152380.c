/* rgp:protos */
#define RGP_SELF_ModelBuildMeshes_152380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Two-phase scene build.  Every guard is an early `return 0;` and the tail
   falls through to `return 1;`.
   MeshMaterialBuildPkt_14ac90's second argument is ArrayGetChecked_14c5e0's RETURN value ($2 read after
   three jals cannot be a saved offset).
   Stack: tmp is at 0xA0 and st at 0xC0, and the last-declared local gets the
   LOWEST address, so st is declared before tmp. */

typedef struct Node Node;
struct Node {
    Node *f00;
    Node *f04;
    u8 pad08[0x10];
    s32 f18;
};

typedef struct {
    s32 f00;
    s32 f04;
    void *f08;
    void *f0C;
    u8 pad10[0x34];
    Node *f44;
} A;

typedef struct {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
} Blk;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void ModelResGetMeshInfo_14c440(Blk *out, void *b, s32 k);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ModelBuildMeshes_152380(A *p, void *b, void *c, void *d)
{
    Blk st __attribute__((aligned(16)));
    Blk tmp __attribute__((aligned(16)));
    Node *node;
    Node *nx;
    Node *hd;
    Node *t;
    Node *h;
    void *arr;
    s32 i;
    s32 n1;
    void *e;
    void *q;
    s32 n2;
    s32 k;

    n1 = ModelResGetMaterialCount_14c640(b);
    n2 = ModelResGetMeshCount_14c5c0(b);
    q = MemStackNew_14e230(0x10, d);
    if (q != 0) {
        ParallelArray3Clear_1531a0(q);
    }
    p->f08 = q;
    if (q == 0) {
        return 0;
    }
    if (ParallelArray3Alloc_153030(q, n1, d) == 0) {
        return 0;
    }
    arr = MemStackNew_14e1b0(n1 * 0x50 + 0x10, d);
    arr = ConstructNewArray_100710(arr, MeshMaterialCtor_1526b0, 0, 0x50, n1);
    if (arr == 0) {
        return 0;
    }
    for (i = 0; i < n1; i++) {
        e = (u8 *)arr + i * 0x50;
        MeshMaterialReset_14b230(e);
        ArraySetChecked_153120(p->f08, i, e);
        MeshMaterialBuildPkt_14ac90(e, ((s32)ArrayGetChecked_14c5e0(b, i)), d, c);
    }
    q = MemStackNew_14e230(0x10, d);
    if (q != 0) {
        ParallelArray3Clear_152e80(q);
    }
    p->f0C = q;
    if (q == 0) {
        return 0;
    }
    if (ParallelArray3Alloc_152d10(q, n2, d) == 0) {
        return 0;
    }
    st.f00 = 0;
    st.f04 = 0;
    st.f0C = 0;
    st.f1C = 0;
    st.f18 = 0;
    st.f14 = 0;
    st.f10 = 0;
    for (k = 0; k < n2; k++) {
        ModelResGetMeshInfo_14c440(&tmp, b, k);
        st.f00 = tmp.f00;
        st.f04 = tmp.f04;
        st.f08 = tmp.f08;
        st.f0C = tmp.f0C;
        st.f10 = tmp.f10;
        st.f14 = tmp.f14;
        st.f18 = tmp.f18;
        st.f1C = tmp.f1C;
        if (ModelResGetSkinInfluenceCount_14cdb0(&st) > 0) {
            p->f04 = 1;
        }
        ArraySetChecked_152e00(p->f0C, k, ((s32)ModelMeshCreate_14e4d0(&st, d, (u8 *)c + 0xD0)));
    }
    if (ModelBuildFrameRefListMaybe_1521f0(p, b, d) == 0) {
        return 0;
    }
    node = p->f44;
    while (node != 0) {
        nx = node->f00;
        if (ArrayGetChecked_152e40(p->f0C, node->f18) == 0) {
            if (p->f44 != 0) {
                t = node->f04;
                if (t != 0) {
                    h = node->f00;
                    t->f00 = h;
                    if (h != 0) {
                        h->f04 = t;
                    }
                    for (hd = node->f04; hd->f04 != 0; hd = hd->f04) {
                        ;
                    }
                } else {
                    h = node->f00;
                    if (h != 0) {
                        h->f04 = 0;
                    }
                    hd = node->f00;
                }
                node->f04 = 0;
                node->f00 = 0;
                p->f44 = hd;
            }
        }
        node = nx;
    }
    p->f00 = 1;
    return 1;
}
