/* rgp:protos */
#define RGP_SELF_MesWinCountPageLines_2726d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct {u8 pad[0x5C];s16 rows[1];} Obj;
/*rgp*/
/*rgp*/
/*rgp*/
void MesWinCountPageLines_2726d0(Obj *o){s32 count,row,i,t;
 MesWinClearPageLineCounts_272a70(o);count=0;row=0;i=0;
 while(i<MesWinGetCharCount_274c70(o)) {
  t=((unsigned short)MesWinGetCharCode_274dd0(o,i))&0xFFFF;
 switch(t){case 0xFF00:count++;break;
case 0xFF03:o->rows[row]=count+1;count=0;row++;break;
case 0xFF01:o->rows[row]=count+1;return;
}
 i++;
 }
 o->rows[row]=count+1;
}
