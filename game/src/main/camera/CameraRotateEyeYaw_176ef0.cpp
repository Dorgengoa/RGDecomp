#include "types.h"
typedef rg_u128 u128;
typedef struct {u128 q;}Vec;
class Obj{public:u8 pad[0xc0];VC_VPTR_MEMBER;void pos(Vec* a0) { VCM(void, (void *, Vec*), 0x94, a0); }void target(Vec* a0) { VCM(void, (void *, Vec*), 0x98, a0); }u8 padc4[0x2c];Vec out;};
extern "C" {void VecAdd_13be20(void*,void*,void*);void VecSub_13be40(void*,void*,void*);f32 WrapAngle_13c050(f32);void MtxMulDir_13c860(void*,void*,void*);void MtxIdentity_13d2e0(void*);void sceVu0RotMatrixY(void*,void*,f32);}
extern "C" void CameraRotateEyeYaw_176ef0(Obj*p,f32 angle){Vec v90,v80,v70;Vec m30[4];p->pos(&v70);p->target(&v80);VecSub_13be40(&v90,&v80,&v70);MtxIdentity_13d2e0(m30);sceVu0RotMatrixY(m30,m30,WrapAngle_13c050(angle));MtxMulDir_13c860(&v90,m30,&v90);VecAdd_13be20(&v80,&v70,&v90);p->out=v80;}
