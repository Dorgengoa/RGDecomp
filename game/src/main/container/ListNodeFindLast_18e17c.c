/* rgp:protos */
#define RGP_SELF_ListNodeFindLast_18e17c 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void **ListNodeFindLast_18e17c(void **p)
{
    void **n;

    for (; p != NULL; p = n) {
        n = (void **)*p;
        if (n == NULL) {
            break;
        }
    }
    return p;
}
