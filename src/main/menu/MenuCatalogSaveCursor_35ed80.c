#include "types.h"
extern u8*GetGameData_1fede0(void);extern void PartyMenuCursorSet_3c0710(s32,s32,s32);
void MenuCatalogSaveCursor_35ed80(u8*p){u8*g=GetGameData_1fede0();if(*(s16*)(*(u8**)(g+12)+0x26)==1){
PartyMenuCursorSet_3c0710(*(s32*)(g+0x18),0x1b,*(s16*)(p+0x204));
PartyMenuCursorSet_3c0710(*(s32*)(g+0x18),0x11,(s16)(*(s32*)(p+0x208)+(*(s32*)(p+0x20c)+*(s32*)(p+0x224))*4));
PartyMenuCursorSet_3c0710(*(s32*)(g+0x18),0x12,(s16)(*(s32*)(p+0x214)+*(s32*)(p+0x22c)));
}}
