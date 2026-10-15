#include "types.h"
static inline s32 lookup(s32 id){s32 r=-1;if(id!=21){if(id!=7){if(id!=6){if(id!=5){if(id!=4){if(id!=3){switch(id){case 2:r=460;break;}}else{r=461;}}else{r=462;}}else{r=463;}}else{r=464;}}else{r=465;}}else{r=466;}done:return r;}
s32 SavePointAreaCompleteFlagIdMaybe_3ec9b0(u8*self,s32 id){s32 r;if(id<0)id=*(s16*)(*(u8**)(self+24)+4);r=lookup(id);if(r<0)r=-1;return r;}
