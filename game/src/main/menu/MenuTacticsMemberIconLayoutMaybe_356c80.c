/* rgp:protos */
#define RGP_SELF_MenuTacticsMemberIconLayoutMaybe_356c80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct {s16 a,b;} Pair;
extern Pair D_0047F7C0[3] __attribute__((section(".sdata")));
/*rgp*/
/*rgp*/
/*rgp*/
s32 MenuTacticsMemberIconLayoutMaybe_356c80(u8 *arg0,s32 arg1) {
 Pair local[3] __attribute__((aligned(16)));const Pair *src;Pair *dst;
 u8 *out; s32 n,i,k;
 out=((u8 *)UiGetWidgetSprite_28fe10(*(void **)(arg0+0x5c),arg1,0));
 if(!out)return 0;
 n=PartyCountMembers_3c2010(*(void **)(((u8 *)GetGameData_1fede0())+0x18),1,1);
 src=D_0047F7C0;dst=local;k=3;
 do {k--;*dst++=*src++;} while(k>0);
 for(i=0;i<n;i++) *(Pair *)(out+i*32)=local[i];
 *(s16 *)(out+n*32)=-1;
 return 1;
}
