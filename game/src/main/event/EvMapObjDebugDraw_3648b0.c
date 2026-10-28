/* rgp:protos */
#define RGP_SELF_EvMapObjDebugDraw_3648b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern struct { f32 v; f32 pad[3]; } D_0045B080;
extern f32 D_0047F960;
extern f32 D_0047F964;
extern f32 D_0047F968;
extern f32 D_0047F96C;
extern f32 D_0047F970;
extern f32 D_0047F974;
extern f32 D_0047F978;
extern f32 D_0047F97C;
extern f32 D_0047F980;
extern f32 D_0047F984;
extern f32 D_0047F988;
extern f32 D_0047F98C;

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
void EvMapObjDebugDraw_3648b0(void *p, void *dl)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x30 + sizeof(f32[4])]; char m1[0x20 + sizeof(f32[4])]; char m2[0x10 + sizeof(f32[4])]; char m3[0x0 + sizeof(f32[4])]; char m4[0x40]; char m5[0x10]; char m6[0x20]; char m7[0x30]; })]; typedef char rgp_blk1_chk0[(0x0) + sizeof(f32[4]) <= (0x10) && (0x0) >= 0 ? 1 : -1]; typedef char rgp_blk1_chk1[(0x10) + sizeof(f32[4]) <= (0x20) && (0x10) >= 0 ? 1 : -1]; typedef char rgp_blk1_chk2[(0x20) + sizeof(f32[4]) <= (0x30) && (0x20) >= 0 ? 1 : -1];
    
    
    
    f32 e[4] __attribute__((aligned(16)));
    f32 f[4] __attribute__((aligned(16)));
    f32 g[4] __attribute__((aligned(16)));
    f32 h[4] __attribute__((aligned(16)));
    void *q;
    f32 t;
    f32 k;
 u8 *entry;
 s32 type,i;

    if (dl == 0) {
        return;
    }
    type=((short)EvMapObjGetMode_366b80(p));
    if(type==3)return;
    if(type==2)goto children;
    if(type!=1){*(s16 *)((u8 *)p+0x300)=0;return;}
      q=TargetRefGetMapObj_2e7050((u8 *)p+0xA0);
      if(q==0)return;
      NodeCalcWorldMatrixThunk_186130(q,(*(f32 (*)[4])(rgp_blk1 + 0x0)));
    k = *(volatile f32 *)&D_0045B080.v;
    t = 2.0f * k;
    VecScale_1cbca0((*(f32 (*)[4])(rgp_blk1 + 0x0)), (*(f32 (*)[4])(rgp_blk1 + 0x0)), t);
    VecScale_1cbca0((*(f32 (*)[4])(rgp_blk1 + 0x10)), (*(f32 (*)[4])(rgp_blk1 + 0x10)), t);
    VecScale_1cbca0((*(f32 (*)[4])(rgp_blk1 + 0x20)), (*(f32 (*)[4])(rgp_blk1 + 0x20)), t);
    GsPktSetTextured_13e400(dl, 0);
    GsPktEnableZTest_13e460(dl, 0);
    GsPktOpenPrim_13f730(dl, 1);
    f[0] = D_0047F960;
    f[1] = D_0047F964;
    f[2] = D_0047F968;
    f[3] = D_0047F96C;
    VecAdd_1cbdc0(e, (*(f32 (*)[4])(rgp_blk1 + 0x0)), (*(f32 (*)[4])(rgp_blk1 + 0x30)));
    GsPktDrawLine3D_1cca80(dl, (*(f32 (*)[4])(rgp_blk1 + 0x30)), e, f);
    g[0] = D_0047F970;
    g[1] = D_0047F974;
    g[2] = D_0047F978;
    g[3] = D_0047F97C;
    VecAdd_1cbdc0(e, (*(f32 (*)[4])(rgp_blk1 + 0x10)), (*(f32 (*)[4])(rgp_blk1 + 0x30)));
    GsPktDrawLine3D_1cca80(dl, (*(f32 (*)[4])(rgp_blk1 + 0x30)), e, g);
    h[0] = D_0047F980;
    h[1] = D_0047F984;
    h[2] = D_0047F988;
    h[3] = D_0047F98C;
    VecAdd_1cbdc0(e, (*(f32 (*)[4])(rgp_blk1 + 0x20)), (*(f32 (*)[4])(rgp_blk1 + 0x30)));
    GsPktDrawLine3D_1cca80(dl, (*(f32 (*)[4])(rgp_blk1 + 0x30)), e, h);
    GsPktClose_13f5b0(dl);
children:
    entry=*(u8 **)((u8 *)p+0x2F4);
    for(i=0;i<*(s16 *)((u8 *)p+0x2FC);){
      EvMapObjNodeDrawAxes_3670b0(entry,dl);
      i++;entry+=0x150;
    }
}
