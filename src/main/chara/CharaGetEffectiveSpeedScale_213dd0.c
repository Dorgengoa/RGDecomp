#include "types.h"

extern f32 CharaGetSpeedScale_238240(void);

f32 CharaGetEffectiveSpeedScale_213dd0(void *arg0)
{
    if (*(s16 *)((u8 *)arg0 + 0xA38) == 0) {
        switch (*(s16 *)((u8 *)arg0 + 0xA32)) {
        case 0:
        case 1:
        case 2:
        case 3:
            return CharaGetSpeedScale_238240();
        }
    } else {
        if (*(s16 *)((u8 *)arg0 + 0xA36) == 1) {
            return CharaGetSpeedScale_238240();
        }
    }
    return 1.0f;
}
