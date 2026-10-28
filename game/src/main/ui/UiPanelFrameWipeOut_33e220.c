/* rgp:protos */
#define RGP_SELF_UiPanelFrameWipeOut_33e220 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
s32 UiPanelFrameWipeOut_33e220(s32 arg0,f32 f) {
 s32 a,b;u8 *o,*p;
 o=((u8 *)UiFindWidget_290460(((s32)UiPanelGetWidgetList_33e860((void *)arg0)),2));
 if(!o)return 0;
 p=*(u8 **)(o+0x20);
 if(!p)return 0;
 UiPanelGetGlyphSpacing_33dfc0(arg0);UiPanelGetCellSize_33e920(arg0,&a,&b);
 if((f32)*(s16 *)(p+4)+f<=0.0f){*(s16 *)(p+0xC)=0;*(s16 *)(p+4)=0;return 1;}
 *(s16 *)p=(s16)((f32)*(s16 *)p+f);
 *(s16 *)(p+4)=(s16)((f32)*(s16 *)(p+4)-f);
 return 0;
}
