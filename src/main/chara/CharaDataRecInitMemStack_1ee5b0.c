#include "types.h"

extern void MemStackInit_14d810(void *);
extern void MemStackReset_14d830(void *);

void CharaDataRecInitMemStack_1ee5b0(u8 *p)
{
    MemStackInit_14d810(p + 8);
    MemStackReset_14d830(p + 8);
}
