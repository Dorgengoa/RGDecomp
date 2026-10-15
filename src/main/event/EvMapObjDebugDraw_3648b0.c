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

extern void FrameCalcWorldMatrix_148ff0(void *q, f32 *v);
extern void VecScale_1cbca0(f32 *d, f32 *s, f32 t);
extern void GsPktSetTextured_13e400(void *dl, s32 v);
extern void GsPktEnableZTest_13e460(void *dl, s32 v);
extern void GsPktOpenPrim_13f730(void *dl, s32 v);
extern void VecAdd_1cbdc0(f32 *d, f32 *s, f32 *t);
extern void GsPktDrawLine3D_1cca80(void *dl, f32 *a, f32 *b, f32 *c);
extern void GsPktClose_13f5b0(void *dl);

extern s32 EvMapObjGetMode_366b80(void *);
extern void *TargetRefGetMapObj_2e7050(void *);
extern void NodeCalcWorldMatrixThunk_186130(void *,f32 *);
extern void EvMapObjNodeDrawAxes_3670b0(void *,void *);
void EvMapObjDebugDraw_3648b0(void *p, void *dl)
{
    f32 a[4];
    f32 b[4];
    f32 c[4];
    f32 d[4];
    f32 e[4];
    f32 f[4];
    f32 g[4];
    f32 h[4];
    void *q;
    f32 t;
    f32 k;
 u8 *entry;
 s32 type,i;

    if (dl == 0) {
        return;
    }
    type=EvMapObjGetMode_366b80(p);
    if(type==3)return;
    if(type==2)goto children;
    if(type!=1){*(s16 *)((u8 *)p+0x300)=0;return;}
      q=TargetRefGetMapObj_2e7050((u8 *)p+0xA0);
      if(q==0)return;
      NodeCalcWorldMatrixThunk_186130(q,d);
    k = *(volatile f32 *)&D_0045B080.v;
    t = 2.0f * k;
    VecScale_1cbca0(d, d, t);
    VecScale_1cbca0(c, c, t);
    VecScale_1cbca0(b, b, t);
    GsPktSetTextured_13e400(dl, 0);
    GsPktEnableZTest_13e460(dl, 0);
    GsPktOpenPrim_13f730(dl, 1);
    f[0] = D_0047F960;
    f[1] = D_0047F964;
    f[2] = D_0047F968;
    f[3] = D_0047F96C;
    VecAdd_1cbdc0(e, d, a);
    GsPktDrawLine3D_1cca80(dl, a, e, f);
    g[0] = D_0047F970;
    g[1] = D_0047F974;
    g[2] = D_0047F978;
    g[3] = D_0047F97C;
    VecAdd_1cbdc0(e, c, a);
    GsPktDrawLine3D_1cca80(dl, a, e, g);
    h[0] = D_0047F980;
    h[1] = D_0047F984;
    h[2] = D_0047F988;
    h[3] = D_0047F98C;
    VecAdd_1cbdc0(e, b, a);
    GsPktDrawLine3D_1cca80(dl, a, e, h);
    GsPktClose_13f5b0(dl);
children:
    entry=*(u8 **)((u8 *)p+0x2F4);
    for(i=0;i<*(s16 *)((u8 *)p+0x2FC);){
      EvMapObjNodeDrawAxes_3670b0(entry,dl);
      i++;entry+=0x150;
    }
}
