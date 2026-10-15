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
