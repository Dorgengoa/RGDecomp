/* rgp:protos */
#define RGP_SELF_ShadowMapRender_146680 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;
typedef struct { f32 x, y, z, w; } V4;
typedef struct { f32 m[4][4]; } M4;
typedef struct {
    f32 a;
    s32 b;
    s32 c;
    f32 d;
    V4 e;
    V4 f;
    M4 g;
    M4 h;
    void *p;
} Desc;
typedef struct {
    u8 pad0[0xF0];
    u128 q[4];
} Src;
typedef struct {
    u8 pad0[0x28];
    s32 base;
    s32 n;
} Node;
typedef struct Obj {
    u8 pad0[0xF20];
    Src *src;
    u8 padF24[0x36B0 - 0xF24];
    s32 f36B0;
    u8 pad36B4[0x3A70 - 0x36B4];
    s16 s3A70;
    s16 w;
    s16 h;
    u8 pad3A76[0x3AE0 - 0x3A76];
    Desc desc;
} Obj;
typedef struct { s32 v[13]; } Rect;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0046FF90[];

void ShadowMapRender_146680(Obj *arg0, Desc *arg1) {
    M4 *m;
    s32 h;
    Node *node2;
    char *o2;
    Rect r __attribute__((aligned(16)));
    Node *node;
    Node *nodeB;
    Src *src;
    s32 idx;
    s32 k;
    char *o1;
    f32 len;
    s32 k2;
    s32 idx2;


    node = ((Node *)DrawListGetCurBuf_142790(arg0));
    if (node == 0) {
        return;
    }
    if (arg1->b == 0) {
        return;
    }
    if (node->base + node->n * 16 == 0) {
        return;
    }
    arg0->desc.a = arg1->a;
    arg0->desc.b = arg1->b;
    arg0->desc.c = arg1->c;
    arg0->desc.d = arg1->d;
    arg0->desc.e = arg1->e;
    arg0->desc.f = arg1->f;
    arg0->desc.g = arg1->g;
    arg0->desc.h = arg1->h;
    arg0->desc.p = arg1->p;
    arg0->desc.p = 0;
    NameTableCopyNode_15ad70(&arg0->s3A70, arg1->b);
    o1 = ((char *)MemStackNew_14e230(0x60, node));
    MeshMaterialDescInit_14bac0(o1);
    o2 = ((char *)MemStackNew_14e230(0x50, node));
    if (o2 != 0) {
        *(void **)(o2 + 0x40) = D_0046FF90;
    }
    MeshMaterialReset_14b230(o2);
    MeshMaterialBuildPkt_14ac90(o2, o1, node, arg0);
    m = &arg0->desc.g;
    *(s32 *)(o2 + 0xC) = 0;
    arg0->desc.p = o2;
    VecSub_13be40(m->m[2], &arg0->desc.f, &arg0->desc.e);
    len = VecLength_13d4a0(m->m[2]);
    VecNormalize_13bd90(m->m[2], m->m[2]);
    *(u128 *)m->m[1] = 0;
    m->m[1][2] = 1.0f;
    sceVu0OuterProduct(m->m[0], m->m[1], m->m[2]);
    sceVu0OuterProduct(m->m[1], m->m[2], m->m[0]);
    *(u128 *)m->m[3] = *(u128 *)&arg0->desc.f;
    m->m[0][3] = 0.0f;
    m->m[1][3] = 0.0f;
    m->m[2][3] = 0.0f;
    m->m[3][3] = 1.0f;
    MtxInverse_13cf40(m, m);
    DrawEnvPush_144830(arg0);
    DrawEnvSetFrameFromDesc_144fe0(arg0, &arg0->s3A70, 0);
    DrawListAddEnv_1421d0(arg0);
    ViewStackPush_144430(arg0);
    ViewSetProjectionBasic_143180(arg0, 2.0f * Atan2f_1291a8(arg0->desc.d, len), 10.0f, 1000.0f, 1.0f);
    nodeB = ((Node *)DrawListGetCurBuf_142790(arg0));
    if (nodeB != 0) {
        idx = nodeB->base + nodeB->n * 16;
        if (idx != 0) {
            k = CameraWriteViewPacket_148740(arg0, idx);
            if (k > 0) {
                MemStackAllocQw_14d950(nodeB, k);
                DmaPktAddCallTagIfSet_141bb0(arg0, idx);
            }
            arg0->f36B0 = idx;
        }
    }
    CameraSetViewIfActive_142e60(arg0, m, &arg0->desc.f);
    node2 = ((Node *)DrawListGetCurBuf_142790(arg0));
    if (node2 != 0) {
        idx2 = node2->base + node2->n * 16;
        if (idx2 != 0) {
            k2 = DrawPktBuildCameraMatrix_1486c0(arg0, idx2);
            if (k2 > 0) {
                MemStackAllocQw_14d950(node2, k2);
                DmaPktAddCallTagIfSet_141bb0(arg0, idx2);
            }
        }
    }
    src = arg0->src;
    *(u128 *)arg0->desc.h.m[0] = src->q[0];
    *(u128 *)arg0->desc.h.m[1] = src->q[1];
    *(u128 *)arg0->desc.h.m[2] = src->q[2];
    *(u128 *)arg0->desc.h.m[3] = src->q[3];
    arg0->desc.h.m[0][0] *= 0.5f;
    arg0->desc.h.m[1][1] *= -0.5f;
    arg0->desc.h.m[2][0] = -0.5f;
    arg0->desc.h.m[2][1] = -0.5f;
    h = ((s32)DrawListBeginPrim_141b00(arg0));
    GsPktSetZWriteMask_13e430(h, 1);
    GsPktSetZTest_13e450(h, 0);
    GsPktEnableAlphaTest_13e4d0(h, 0);
    GsPktSetDestAlphaTest_13e4a0(h, 0);
    GsPktSetAlphaTestFunc_13e4c0(h, 0, 0);
    GsPktSetAlphaBlend_13e500(h, 0);
    GsPktSetTextured_13e400(h, 0);
    GsPktOpen_13f4a0(h);
    r.v[4] = 0;
    r.v[12] = 1;
    r.v[8] = arg0->w * 16;
    r.v[5] = 0;
    r.v[9] = arg0->h * 16;
    r.v[6] = 0;
    r.v[10] = 0;
    r.v[7] = 0;
    r.v[11] = 0;
    r.v[0] = 0;
    r.v[1] = 0;
    r.v[2] = 0;
    r.v[3] = 0;
    GsPktDrawSprite_13ea30(h, &r);
    GsPktCommit_13f190(h);
    DrawListEndPrim_141a20(arg0);
}
