#include "types.h"
extern s32 GroupFindByKey_40eb80(void*, s16); extern s32 TableFindRowById_40f880(s32,s32);
s32 SkillDefFindMaybe_40ea70(u8*a,s16 b,s32 c){s32 t;if((s16)b<0){s32 p=*(s32*)(a+8);if(!p)return 0;return TableFindRowById_40f880(p,c);}if(!*(s32*)(a+12))return 0;t=GroupFindByKey_40eb80(a,b);if(!t)return 0;return TableFindRowById_40f880(t,c);}
