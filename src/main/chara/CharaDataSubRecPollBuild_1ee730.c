#include "types.h"
extern void CharaDataNodeBuildPoll_1ef600(void*,void*);
void CharaDataSubRecPollBuild_1ee730(u8*p){u8*q;s32 found;u8 mode;if(p[10]!=2)return;q=*(u8**)(p+0x64);if(!q)return;found=0;while(q){CharaDataNodeBuildPoll_1ef600(q,p+12);mode=q[0x1e];switch(mode){case 1:case 2:found=1;break;case 4:p[10]=4;return;}q=*(u8**)(q+4);}if(!found)p[10]=3;}
