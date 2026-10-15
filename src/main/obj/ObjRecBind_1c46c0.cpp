#include "types.h"
extern "C" char *strcpy(char*,const char*);
class Obj {public:s32 flags;u8 pad[4];char name[24];virtual void reset();void *ptr;};
extern "C" s32 ObjRecBind_1c46c0(Obj*p,void*q,const char*n){if(!n||!q)return -1;p->reset();p->flags=0;p->ptr=q;strcpy(p->name,n);p->flags|=4;return 0;}
