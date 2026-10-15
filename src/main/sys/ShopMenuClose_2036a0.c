#include "types.h"

extern void ShopMenuRelease_2036d0(void);
extern void MenuTransdataRelease_206260(void);
extern void MenuTranstempRelease_206230(void);

void ShopMenuClose_2036a0(void)
{
    ShopMenuRelease_2036d0();
    MenuTransdataRelease_206260();
    MenuTranstempRelease_206230();
}
