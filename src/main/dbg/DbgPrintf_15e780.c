#include "types.h"
typedef char *va_list;extern u8 D_0047DF34;extern void Vprintf_138e68(s32,void*);
#pragma opt_propagation off
void DbgPrintf_15e780(s32 arg0,...){va_list ap;s32 n;if(D_0047DF34){n=1;ap=(va_list)__builtin_next_arg(arg0)-(n>=8?0:(8-n)*8);Vprintf_138e68(*(volatile s32*)&arg0,ap);}}
