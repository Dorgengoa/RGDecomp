/* SPDX-License-Identifier: CC0-1.0 */
/* rg-nr-vudis: disassemble raw VU microcode files (the MPG payloads written by
 * $RG_NR_FXCENSUS_DIR, docs/NATIVE-RENDER.md "INSECT VU1 census").
 *   rg-nr-vudis FILE.bin [DEST_HEX]   (DEST default: from the name mpg_<dest>_<hash>.bin) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vu_decode.h"

int main(int argc, char **argv)
{
    FILE *f;
    unsigned dest = 0;
    long n;
    unsigned char *b;
    const char *base;
    if (argc < 2) { fprintf(stderr, "usage: rg-nr-vudis FILE.bin [DEST_HEX]\n"); return 2; }
    base = strrchr(argv[1], '/');
    base = base ? base + 1 : argv[1];
    if (argc > 2) dest = (unsigned)strtoul(argv[2], NULL, 16);
    else if (!strncmp(base, "mpg_", 4)) dest = (unsigned)strtoul(base + 4, NULL, 16);
    f = fopen(argv[1], "rb");
    if (!f) { perror(argv[1]); return 1; }
    fseek(f, 0, SEEK_END);
    n = ftell(f);
    fseek(f, 0, SEEK_SET);
    b = (unsigned char *)malloc((size_t)n + 8);
    if (!b || fread(b, 1, (size_t)n, f) != (size_t)n) { fclose(f); return 1; }
    fclose(f);
    for (long i = 0; i + 8 <= n; i += 8) {
        unsigned lo, up;
        vu_pair p;
        char buf[256];
        memcpy(&lo, b + i, 4);
        memcpy(&up, b + i + 4, 4);
        vu_decode_pair(lo, up, &p);
        vu_disasm_pair(&p, dest + (unsigned)i, buf, sizeof buf);
        printf("%04x: %s\n", dest + (unsigned)i, buf);
    }
    free(b);
    return 0;
}
