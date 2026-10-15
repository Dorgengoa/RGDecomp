#include "types.h"

extern void MenuThinkResRelease_2035d0(void);
extern void MenuTransdataRelease_206260(void);
extern void MenuTranstempRelease_206230(void);

void ThinkMenuClose_2035a0(void)
{
    MenuThinkResRelease_2035d0();
    MenuTransdataRelease_206260();
    MenuTranstempRelease_206230();
}
