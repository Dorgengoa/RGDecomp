#include "types.h"

extern void MenuTransResRelease_2037e0(void);
extern void MenuTransdataRelease_206260(void);
extern void MenuTranstempRelease_206230(void);

void TransMenuClose_2037b0(void)
{
    MenuTransResRelease_2037e0();
    MenuTransdataRelease_206260();
    MenuTranstempRelease_206230();
}
