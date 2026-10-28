#include "types.h"
/* normal_TransMenuResReady_516a90 shape: a bare tail call to the ready poll */
s32 normal_ResPoll_4ec140(void);

void normal_ResReady_4ec100(void)
{
    normal_ResPoll_4ec140();
}

s32 normal_ResPoll_4ec140(void)
{
    return 1;
}
