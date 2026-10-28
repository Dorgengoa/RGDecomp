/* rgp:protos */
#line 1
#include "types.h"
extern "C" char *strcpy(char*,const char*);
class Obj {public:s32 flags;u8 pad[4];char name[24];VC_VPTR_MEMBER; void reset(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, int, int, int), 0x8, rgp_fwd1, rgp_fwd2, rgp_fwd3); }void *ptr;};
extern "C" s32 ObjRecBind_1c46c0(Obj*p,void*q,const char*n, int rgp_a3){if(!n||!q)return -1;p->reset((int)(long)(q), (int)(long)(n), (int)(long)(rgp_a3));p->flags=0;p->ptr=q;strcpy(p->name,n);p->flags|=4;return 0;}
