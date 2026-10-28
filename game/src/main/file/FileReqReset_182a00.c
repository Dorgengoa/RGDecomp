/* rgp:protos */
#define RGP_SELF_FileReqReset_182a00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_00495FD0[];          /* %hi/%lo => incomplete array */
extern s32 D_004811F0;
extern s32 D_004811EC;
extern s32 D_004811E8;

void FileReqReset_182a00(void)
{
    s32 i;

    for (i = 0; i < 0x20; i++) {
        *(s32 *)(D_00495FD0 + i * 0x128 + 0x120) = 0;
    }
    D_004811F0 = 0;
    D_004811EC = -1;
    D_004811E8 = 0;
}
