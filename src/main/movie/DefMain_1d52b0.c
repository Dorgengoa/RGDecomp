#include "types.h"

extern void ThreadYield_1d2b70(void);

void DefMain_1d52b0(void)
{
    for (;;) {
        ThreadYield_1d2b70();
    }
}
