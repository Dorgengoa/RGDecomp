#include "types.h"
typedef struct { u8 pad[0x500]; u8 *array; } Obj;
extern s32 strcmp(const char *,const char *);
s32 SaveDirListContains_3732b0(Obj *arg0, const char * arg1) { s32 i;
if (!arg0->array || !arg1) return 0;
for (i=0;i<50;i++) {if (!strcmp((const char*)arg1,(const char*)(arg0->array+(i<<6)+0x20))) return 1;}return 0; }
