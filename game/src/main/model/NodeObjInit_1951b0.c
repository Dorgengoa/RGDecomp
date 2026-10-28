/* rgp:protos */
#define RGP_SELF_NodeObjInit_1951b0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#pragma vu0_mmi_reg_binding on
typedef rg_s128 __attribute__((aligned(4))) rgvb_vz1951b0_t; /* rg:vu0bind vf0 */
#define vz1951b0 RG_VU0_BIND_VF(0, rgvb_vz1951b0_t)


typedef struct Obj1951b0 {
    u8 pad0[0x3C];
    u8 sub3c[0x30];
    u8 b6c;
    u8 pad6d[0x1F];
    s32 w8c;
    s32 w90;
    s32 w94;
    s32 w98;
    s32 w9c;
    s32 wa0;
    s32 wa4;
    s32 wa8;
    s32 wac;
    rg_s128 vb0;
    rg_s128 vc0;
    rg_s128 vd0;
    rg_s128 ve0;
    rg_s128 vf0_;
    rg_s128 v100;
    s32 w110;
    u8 sub114[0x10];
    s32 w124;
    s32 w128;
    s32 w12c;
    s32 w130;
    s32 w134;
    s32 w138;
    s32 w13c;
    s32 w140;
    s32 pad144;
    s32 w148;
} Obj1951b0;

/*rgp*/
/*rgp*/
/*rgp*/

void NodeObjInit_1951b0(Obj1951b0 *p)
{ RG_VU0_FRAME;
    NodeInit_185f60(p);
    FarClipRecInit_186e30(p->sub3c);
    p->w94 = 0;
    p->b6c = 0;
    p->w8c = 0;
    p->w90 = 0;
    p->w140 = 1;
    p->w98 = 0;
    FuncDataTableInit_18fc00(p->sub114);
    p->w148 = 0;
    p->w110 = 0;
    p->w12c = 0;
    p->w128 = 0;
    p->w130 = -1;
    p->w134 = 0;
    p->w124 = 0;
    p->w13c = 0;
    p->wa8 = 0;
    p->vb0 = vz1951b0;
    p->vc0 = vz1951b0;
    p->vd0 = 0;
    p->wa0 = 0;
    p->wa4 = 0;
    p->wac = 0;
    p->ve0 = vz1951b0;
    p->vf0_ = vz1951b0;
    p->v100 = 0;
    p->w9c = 0;
    p->w138 = 0;
}
