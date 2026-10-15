#include "types.h"

extern void * GetGameData_1fede0(void);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern s32 PartyCountReserve_3c1c20(s32, s32, s32);

s32 MenuPartyWidgetToCursorCell_29f580(void *arg0, s32 arg1, void *arg2)
{
    s32 var_7;
    s16 t;
    s32 var_16;
    s32 var_3;
    void *temp_2;

    var_7 = 0;
    var_16 = 0;
    if (arg2 == NULL) {
        return 0;
    }
    t = *(s16 *)((u8 *)arg2 + 0x12);
    if (t == 1) {
        temp_2 = GetGameData_1fede0();
        if (temp_2 == NULL) {
            return 0;
        }
        var_3 = PartyCountReserve_3c1c20(*(s32 *)((u8 *)temp_2 + 0x18), 1, 1) - 5;
        if (var_3 <= 0) {
            var_3 = 0;
        }
        var_7 = 0x107;
        if (var_3 == 0) {
            t = *(s16 *)((u8 *)arg2 + 0x10);
            if (t == 4) {
                var_16 = 0xE6;
            } else {
                var_16 = (t * 0x4F) + 0x55;
            }
        } else if (var_3 == 1) {
            t = *(s16 *)((u8 *)arg2 + 0x10);
            if (t >= 4) {
                var_16 = ((5 - t) * -0x3E) + 0xE6;
            } else {
                var_16 = (t * 0x3F) + 0x55;
            }
        } else if (var_3 == 2) {
            t = *(s16 *)((u8 *)arg2 + 0x10);
            if (t >= 4) {
                var_16 = ((6 - t) * -0x36) + 0xF0;
            } else {
                var_16 = (t * 0x36) + 0x4E;
            }
        }
    } else if (t == 0) {
        var_7 = 0x60;
        var_16 = (*(s16 *)((u8 *)arg2 + 0x10) * 0x82) + 0x18;
    }
    UiSetWidgetPos_290f60(*(s32 *)((u8 *)arg0 + 0x4C4), arg1, var_16, var_7);
    return 1;
}
