#include "types.h"
extern void UiGetWidgetTextSize_28f430(s32,s32,s32 *,s32 *,s32);
extern void *UiGetWidgetSprite_28fe10(s32,s32,s32);
extern void UiWindowFrameSetSize_388380(void *,s32,s32);
extern s32 ScreenGetWidth_390d10(void),ScreenGetHeight_390ce0(void);
extern void UiSetWidgetPos_290f60(s32,s32,s32,s32);
extern s32 D_00483308;
void UiFitCenterWindow_388270(s32 a,s32 mode){
 s32 width,height,x;
 UiGetWidgetTextSize_28f430(D_00483308,a,&width,&height,0);
 UiWindowFrameSetSize_388380(UiGetWidgetSprite_28fe10(D_00483308,a,0),width+0x18,height+0x14);
 x=(ScreenGetWidth_390d10()>>1)-(width>>1)-0xC;
 if(mode==0){UiSetWidgetPos_290f60(D_00483308,a,x,0x4C);return;}
 if(mode==1){UiSetWidgetPos_290f60(D_00483308,a,x,(ScreenGetHeight_390ce0()>>1)-(height>>1));return;}
 if(mode==2){UiSetWidgetPos_290f60(D_00483308,a,x,0x74);return;}
}
