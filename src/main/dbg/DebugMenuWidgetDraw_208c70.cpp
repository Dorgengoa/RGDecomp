/* PARK: same length as retail, 19 bad words after 1 round. Not re-tried. */
#include "types.h"
extern "C" {

extern void DebugMenuWidgetDrawWindow_209310(void *arg0, s32 arg1, s32 arg2, f32 arg3);
extern void *DebugMenuWidgetGetCurrentChild_209dd0(void *arg0);
extern s32 DebugMenuWidgetHasPosFlagMaybe_209e20(void);
extern s32 DebugMenuWidgetShouldDrawWindowMaybe_209eb0(void *arg0);
extern f32 D_0047D1E0;

class VC_0 {
public:
    u8 pad[0x2C];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void f(s32 x0, s32 x1);
};
void DebugMenuWidgetDraw_208c70(void *arg0, s32 arg1, s32 arg2)
{
    s32 var_18;
    s32 var_17;
    void *temp_2;

    var_18 = arg1;
    var_17 = arg2;
    if (DebugMenuWidgetHasPosFlagMaybe_209e20() == 0) {
        var_18 = 0;
        var_17 = 0;
    }
    if (*(u16 *)((u8 *)arg0 + 0x2A) & 0x40) {
        temp_2 = DebugMenuWidgetGetCurrentChild_209dd0(arg0);
        if ((temp_2 != NULL) && (*(u16 *)((u8 *)temp_2 + 0x2A) & 0x40)) {
            if (DebugMenuWidgetShouldDrawWindowMaybe_209eb0(arg0) != 0) {
                DebugMenuWidgetDrawWindow_209310(arg0, var_18, var_17, D_0047D1E0);
            }
            ((VC_0 *)(temp_2))->f(var_18 + *(s16 *)((u8 *)arg0 + 0x26), var_17 + *(s16 *)((u8 *)arg0 + 0x28));
            return;
        }
        if (DebugMenuWidgetShouldDrawWindowMaybe_209eb0(arg0) != 0) {
            DebugMenuWidgetDrawWindow_209310(arg0, var_18, var_17, 1.0f);
        }
    }
}

}
