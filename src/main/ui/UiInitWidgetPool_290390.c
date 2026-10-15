#include "types.h"

extern s32 ConstructNewArray_100710(s32, void *, s32, s32, s32);
extern s32 MemStackNew_14e1b0(s32);
extern void UiWidgetPoolEntryCtor_290430(void);

void UiInitWidgetPool_290390(void *self, s32 arg1, s32 arg2)
{
    u8 *arr;
    s32 i;
    u8 *e;

    if (arg1 != 0) {
        arr = (u8 *)ConstructNewArray_100710(MemStackNew_14e1b0(arg2 * 0xC + 0x10),
                                  (void *)UiWidgetPoolEntryCtor_290430, 0, 0xC, arg2);
        *(u8 **)self = arr;
        for (i = 0; i < arg2; i++) {
            e = *(u8 **)self + i * 0xC;
            *(s32 *)(e + 0) = 0;
            *(s32 *)(e + 8) = 0;
            *(s32 *)(e + 4) = 0;
        }
        *(s16 *)((u8 *)self + 0xE) = arg2;
    }
}
