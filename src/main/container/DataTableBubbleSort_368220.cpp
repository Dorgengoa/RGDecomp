#include "types.h"
class Self { public:
virtual void v8();
virtual void v12();
virtual void v16();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v32();
virtual void v36();
virtual void v40();
virtual void v44();
virtual s32 test();
virtual void *get(s32);
virtual void v56();
virtual s32 stride();
virtual void v64();
virtual void v68();
virtual void v72();
virtual void v76();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v92();
virtual void v96();
virtual void v100();
virtual s32 compare(void *,void *);
u8 pad[0x76];u8 flag:1; u8 other:7;u8 pad2;s16 count;
};
extern "C" { void *memcpy(void *,const void *,u32);void DelayThread_117618(s32);
s32 DataTableBubbleSort_368220(Self *self){
u8 temp[2048];s32 total;
s32 size;
u8 swapped;
void *prev;
s32 i;
void *next;
if(!self->test())return 0;
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
