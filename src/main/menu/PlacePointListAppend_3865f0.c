#include "types.h"
#include "vec.h"
typedef struct {u128 a,b;} V;typedef struct {u8 pad[24];s32 id;u8 pad2[4];} Rec;typedef struct{Rec*array;s32 count;} O;extern void Copy20Bytes_3869c0(void*,void*,void*);
void* PlacePointListAppend_3865f0(O*a,V*b){V local=*b;s32 n=a->count;if(n>=256)return 0;Copy20Bytes_3869c0(a->array+n,&local,&local);a->array[a->count].id=a->count+1;{Rec *p=a->array+a->count;a->count++;return p;}}
