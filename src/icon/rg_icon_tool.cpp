// SPDX-License-Identifier: CC0-1.0
// rg-icon: the game icon from the player's own data/ (docs/ICON.md).
//
//   rg-icon ico   DATA_DIR OUT.ico [--source NAME]   write a multi-size .ico (NAME: jaster ship galaxy logo birthmark seal globe crest)
//   rg-icon embed EXE DATA_DIR     [--source NAME]   add it to an exe (Windows)
//   rg-icon has   EXE                                            exit 0 = has an icon, 1 = none
//
// Game art: write the .ico / iconed exe under out/ or a build dir, never into the tree, and
// never publish an exe that carries it (tools/release/make_release.py refuses one).
#include "rg_icon.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

static int usage() {
    fprintf(stderr,
            "usage: rg-icon ico DATA_DIR OUT.ico [--source NAME]\n"
            "       rg-icon embed EXE DATA_DIR [--source NAME]\n"
            "       rg-icon has EXE\n");
    return 2;
}

int main(int argc, char **argv) {
    if (argc < 3) return usage();
    int source = RG_ICON_DEFAULT;
    for (int i = 1; i + 1 < argc; i++)
        if (!strcmp(argv[i], "--source")) {
            source = rg_icon_source_by_name(argv[i + 1]);
            if (source < 0) return usage();
            argc = i;   // options last
            break;
        }
    const char *cmd = argv[1];
    char err[512] = "";
    if (!strcmp(cmd, "has")) {
        int h = rg_icon_exe_has_icon(argv[2]);
        printf("%s: %s\n", argv[2], h ? "has an icon" : "no icon");
        return h ? 0 : 1;
    }
    if (argc < 4) return usage();
    rg_icon_set s;
    const char *data = !strcmp(cmd, "ico") ? argv[2] : argv[3];
    if (rg_icon_build(data, source, &s, err, sizeof err)) {
        fprintf(stderr, "rg-icon: %s\n", err);
        return 1;
    }
    int rc = 0;
    if (!strcmp(cmd, "ico")) {
        size_t n = 0;
        uint8_t *b = rg_icon_ico_bytes(&s, &n);
        FILE *f = b ? fopen(argv[3], "wb") : nullptr;
        if (!f || fwrite(b, 1, n, f) != n) {
            fprintf(stderr, "rg-icon: cannot write %s\n", argv[3]);
            rc = 1;
        }
        if (f && fclose(f)) rc = 1;
        free(b);
        if (!rc) printf("rg-icon: %s (%s, %zu bytes)\n", argv[3], rg_icon_source_name(source), n);
    } else if (!strcmp(cmd, "embed")) {
        if (rg_icon_embed_exe(argv[2], &s, err, sizeof err)) {
            fprintf(stderr, "rg-icon: %s: %s\n", argv[2], err);
            rc = 1;
        } else {
            printf("rg-icon: icon (%s) added to %s\n", rg_icon_source_name(source), argv[2]);
        }
    } else {
        rc = usage();
    }
    rg_icon_free(&s);
    return rc;
}
