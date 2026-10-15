#include "types.h"

extern void HatenaMarkListAssignNearby_344900(void);
extern void HatenaMarkStep_345540(void *);

void HatenaMarkListStep_344ee0(u8 *arg0)
{
    u8 *temp_3;
    u8 *temp_3_2;
    u8 *var_4;

    HatenaMarkListAssignNearby_344900();
    if (*(void **)(arg0 + 4) == NULL) {
        *(void **)(arg0 + 4) = *(void **)(arg0 + 0);
        *(s32 *)(arg0 + 8) = 0;
    }
    for (;;) {
        temp_3 = *(u8 **)(arg0 + 4);
        if (temp_3 == NULL) {
            var_4 = NULL;
        } else {
            var_4 = temp_3 + 0x10;
            temp_3_2 = *(u8 **)temp_3;
            *(void **)(arg0 + 4) = temp_3_2;
            if (temp_3_2 == NULL) {
                *(s32 *)(arg0 + 8) = 1;
            }
        }
        if (var_4 != NULL) {
            HatenaMarkStep_345540(var_4);
            continue;
        }
        break;
    }
    *(void **)(arg0 + 4) = NULL;
    *(s32 *)(arg0 + 8) = 0;
}
