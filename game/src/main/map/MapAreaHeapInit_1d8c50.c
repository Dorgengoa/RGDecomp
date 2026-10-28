/* rgp:protos */
#define RGP_SELF_MapAreaHeapInit_1d8c50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char *strcpy(char *, char *);
extern u32 strlen(char *);

s32 MapAreaHeapInit_1d8c50(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 temp_17;
    s32 temp_18;
    s32 temp_2;

    if (arg1 == 0 || arg2 <= 0) {
        return -1;
    }
    temp_17 = AlignUp16_1cacd0(0x58);
    *arg0 = arg1;
    MemStackClear_14dff0(arg1);
    MemStackInit_14d810(*arg0, PtrAddAligned16_1cac90(arg1, temp_17), arg2 - (temp_17 >> 4));
    temp_2 = MapDataGetName_1e7bf0(arg0);
    temp_18 = *arg0;
    if (strlen((char *) temp_2) < 0x10U) {
        strcpy((char *) temp_18, (char *) temp_2);
    }
    MemStackReset_14d830(*arg0);
    return 2;
}
