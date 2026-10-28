/* rgp:protos */
#line 1
#include "types.h"
class Self { public:
VC_VPTR_MEMBER;









s32 test(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x30, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
void * get(s32 a0) { return VCM(void *, (void *, s32), 0x34, a0); }

s32 stride() { return VCM0(s32, 0x3C); }










s32 compare(void * a0, void * a1) { return VCM(s32, (void *, void *, void *), 0x68, a0, a1); }
u8 pad[0x76];u8 flag:1; u8 other:7;u8 pad2;s16 count;
};
extern "C" { void *memcpy(void *,const void *,u32);void DelayThread_117618(s32);
s32 DataTableBubbleSort_368220(Self *self, int rgp_a1, int rgp_a2, int rgp_a3){
u8 temp[2048] __attribute__((aligned(16)));s32 total;
s32 size;
u8 swapped;
void *prev;
s32 i;
void *next;
if(!self->test((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3)))return 0;
if(self->count<=0)return 0;
total=0;size=self->stride();
do{swapped=false;prev=self->get(0);i=1;
while(i<self->count){
next=self->get(i);if(self->compare(prev,next)>0){memcpy(temp,next,size);memcpy(next,prev,size);memcpy(prev,temp,size);swapped=true;}
total++;prev=next;if(!(total&255))DelayThread_117618(10);i++;
}
}while(swapped);
self->flag=1;return 1;
}}
