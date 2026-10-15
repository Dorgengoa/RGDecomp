#include "types.h"
typedef struct{s16 count,pad;void*data;s16 a,b,c,d,e,f,g,h;}O;extern void*ConstructNewArray_100710(void*,void*,s32,s32,s32);extern void*MemStackNew_14e0b0(s32);extern void SlotRecordCtor_3ee7d0(void);
void SlotRecordRingInit_3ee730(O*p,s32 enabled,s32 n){p->count=0;p->data=0;p->a=0;p->b=-1;p->c=-1;p->d=0;p->e=-1;p->f=-1;p->g=-1;p->h=-1;if(enabled && n>0){u32 count=n;p->count=n;p->data=ConstructNewArray_100710(MemStackNew_14e0b0(count*0x350+0x10),(void*)SlotRecordCtor_3ee7d0,0,0x350,count);}}
