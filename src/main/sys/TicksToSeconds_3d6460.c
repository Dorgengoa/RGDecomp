#include "types.h"

extern s64 U64ToDouble_100370(void);
extern void dpdiv(s64, double);

void TicksToSeconds_3d6460(void)
{
    dpdiv(U64ToDouble_100370(), 60.0);
}
