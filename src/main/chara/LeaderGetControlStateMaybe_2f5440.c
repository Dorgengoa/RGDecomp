#include "types.h"

/* MAIN LeaderGetControlStateMaybe_2f5440 -- two guards branching the SAME way is an `&&`. */

typedef struct Ctx5440 {
    u8  pad00[0x18];
    u8 *m18;            /* 0x18 */
} Ctx5440;

extern s32 IsInBattle_288420(void);
extern s32 BtlChgMenuIsMemberPageUp_204e20(void);
extern Ctx5440 *GetGameData_1fede0(void);
extern s32 CharaGetControlStateMaybe_2f5320(s32);

s32 LeaderGetControlStateMaybe_2f5440(void)
{
    Ctx5440 *c;

    if (IsInBattle_288420() != 0 && BtlChgMenuIsMemberPageUp_204e20() != 0) {
        return 1;
    }
    c = GetGameData_1fede0();
    return CharaGetControlStateMaybe_2f5320(*(s16 *)(c->m18 + 0x18E));
}
