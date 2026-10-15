#include "types.h"
extern char*strcpy(char*,const char*);extern char*strcat(char*,const char*);extern char *D_0044A610[];extern char D_00459730[];extern s32 D_0047E00C;extern char D_00495EB0[];
void FileMakeDevicePath_181980(char*src,char*dst){char*p;s32 single;s32 count;s64 c;p=src;count=0;while((c=*p)!=0){if((s64)((s64)c<<56)>>56==58)break;p++;count++;}single=count==1;if(c!=0 && !single){strcpy(dst,src);return;}if(D_0047E00C>=0 && D_0047E00C<5){strcpy(dst,D_0044A610[D_0047E00C]);strcat(dst,D_00459730);}if(!single)strcat(dst,D_00495EB0);strcat(dst,src);}
