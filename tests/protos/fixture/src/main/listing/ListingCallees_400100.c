#include "types.h"
void SetScale_400100(void *o, f32 x, f32 y) { ((f32 *)o)[31] = x; ((f32 *)o)[32] = y; }
void UseNothing_400200(void *o, s32 n) { ((s32 *)o)[0] = 0; }
void ReadsA1_400300(void *o, s32 n) { ((s32 *)o)[0] = n; }
s32 Other_400400(void) { return 1; }
void ClearClip_400500(void *p) { ((s16 *)p)[16] = 0; }
void VecFill_400600(f32 *dst, f32 *src) { dst[0] = src[0]; }
s32 FindFree_400700(void *t) { return t != 0; }
void PutPoint_400b00(void *p, s32 v) { ((s32 *)p)[0] = v; }
void PutRay_400b10(void *c, void *d) { ((f32 *)c)[0] = 0.0f; ((f32 *)d)[0] = 0.0f; }
s32 SweepB_400b20(f32 *p) { return p[0] < p[12]; }
void MatRows_400b30(void *m) { ((f32 *)m)[12] = ((f32 *)m)[0]; }
void CopyHandle_401680(s32 *h) { h[0] = h[1] = h[2] = h[3] = h[4] = 0; }
void SwitchReach_4016c0(s32 *k) { switch (k[0]) { case 0: k[1] = 0; break; default: k[3] = 0; } }
void PutPair_401780(void *p) { ((s32 *)p)[0] = 0; ((s32 *)p)[4] = 0; }
