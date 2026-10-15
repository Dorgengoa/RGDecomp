#include "types.h"
typedef struct T0025f990 {
    u8 pad[0x24];
    s32 f24;
} T0025f990;

extern T0025f990 *GetGameData_1fede0(void);
extern void RecordSetMode_431310(s32 a, s32 b);

s32 EvCmdRecordSetModeOne_25f990(void)
{
    RecordSetMode_431310(GetGameData_1fede0()->f24, 1);
    return 1;
}
