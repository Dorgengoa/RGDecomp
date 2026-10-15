#include "types.h"
extern s32 sceMcInit_12c648(void);
s32 SaveMcInitStatus_375ea0(void){s32 v; s32 r; v=sceMcInit_12c648();if(v!=-121){if(v!=-120){if(v!=-101){if(v!=0)r=v;else r=0;}else r=1;}else r=1;}else r=1;return r;}
