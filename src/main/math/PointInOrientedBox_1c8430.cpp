#include "types.h"
extern "C" {
extern f32 MtxInverseAffine_1cb640(void*,void*);extern void MatMulPointRelMaybe_1cb5d0(void*,void*,void*,void*);
bool PointInOrientedBox_1c8430(void*p,void*m){f32 inv[16];f32 v[4];bool result;bool ok;if(MtxInverseAffine_1cb640(inv,m)==0.0f)return 0;MatMulPointRelMaybe_1cb5d0(v,m,inv,p);result=0;ok=0;if(v[0]*v[0]<=1.0f && v[1]*v[1]<=1.0f)ok=1;if(ok && v[2]*v[2]<=1.0f)result=1;return result;}
}
