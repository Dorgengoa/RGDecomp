/* rgp:protos */
#define RGP_SELF_DbgPrintf_15e780 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include <stdarg.h>
extern u8 D_0047DF34;extern void Vprintf_138e68(s32,void*);
#pragma opt_propagation off
void DbgPrintf_15e780(s32 arg0,...){va_list ap;s32 n;if(D_0047DF34){n=1;va_start(ap, arg0);Vprintf_138e68(*(volatile s32*)&arg0,ap);}}
