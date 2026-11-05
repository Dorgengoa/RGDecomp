/* SPDX-License-Identifier: CC0-1.0 */
/* Saves tools in the exe (docs/SAVES.md "Named slots and metadata", "PCSX2 import in the
 * exe"): read a PCSX2 memory card (an 8 MB .ps2 image with or without ECC, or a PCSX2
 * folder card) and import its save directories into one of the port's cards through the
 * card model (mccard.h), so the writes are the card model's crash-safe writes and a replaced
 * save is backed up first.  The source card is opened read-only and never written: the exe
 * imports only (tools/saves/ps2card.py exports).
 *
 * Written from public descriptions of the PS2 memory card file system (superblock,
 * indirect FAT, 512-byte directory entries); the same layout as tools/saves/ps2card.py.
 * No emulator or GPL code. */
#ifndef RG_MC_IMPORT_H
#define RG_MC_IMPORT_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "mccard.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mc_src_file {
    char name[MC_NAME_MAX];
    uint8_t *data;
    uint32_t len;
    uint16_t mode;
    int has_time;               /* image cards: created / modified from the entry */
    mc_datetime ctime, mtime;
} mc_src_file;

typedef struct mc_src_dir {
    char name[MC_NAME_MAX];
    uint16_t mode;
    int has_time;
    mc_datetime ctime, mtime;
    char title[160];            /* icon.sys title */
    int nfiles;
    mc_src_file *files;         /* card order (folder cards: icon.sys, icons, the data last) */
} mc_src_dir;

typedef struct mc_src_card {
    int kind;                   /* 1 image (.ps2), 2 PCSX2 folder card */
    int ecc;                    /* image with the 16-byte spare area */
    int ndirs;
    mc_src_dir *dirs;
} mc_src_card;

/* 0 ok; -1 with a reason in err (not a card, unformatted, a broken FAT chain, ...) */
int mc_src_open(const char *path, mc_src_card *card, char *err, size_t errcap);
/* the same from an image in memory (tests) */
int mc_src_open_image(const uint8_t *img, size_t len, mc_src_card *card, char *err, size_t errcap);
void mc_src_free(mc_src_card *card);

/* '*' and '?' wildcards, whole string */
int mc_glob(const char *pattern, const char *s);

/* import card->dirs[i] into the port's card `port` (0 = card1; mccard_init done).
 * 0 imported, 1 skipped (a directory of that name exists and force == 0), < 0 error
 * (reason in err; a new directory that failed half-way is removed again).  force replaces
 * the existing directory's files (the card model backs it up first, saves.backup_keep). */
int mc_src_import(const mc_src_card *card, int i, int port, int force, char *err, size_t errcap);

/* The command-line tools of rg-game (rg_game_main.c):
 *   --list-saves                      both cards: directories, names, summaries
 *   --name-save C:NN=TEXT             name save BASCUS-97490LV5RG_NN (or a full directory
 *                                     name) on card C (1, 2); empty TEXT removes the name
 *   --import-card PATH                import a PCSX2 card's saves into card --import-slot
 *   --import-slot N, --import-save GLOB (default BASCUS-97490LV5RG_*), --import-force,
 *   --import-list (list the source card only)
 * Each runs on the saves dir and exits (the game does not start). */
typedef struct mc_cli_opts {
    int list_saves;
    const char *name_save;      /* "C:NN=TEXT" */
    const char *import_card;
    int import_slot;            /* 1 or 2 (0 = 1) */
    const char *import_glob;    /* NULL = BASCUS-97490LV5RG_* */
    int import_force;
    int import_list;
} mc_cli_opts;
/* 1 when argv[*i] (with its value argv[*i + 1]) is one of the options above (and *i moved
 * past it); 0 otherwise; -1 a bad value */
int mc_cli_arg(mc_cli_opts *o, int argc, char **argv, int *i);
int mc_cli_wanted(const mc_cli_opts *o);
/* run them on `root` (the saves dir); the exit code (0 ok, 1 something failed, 2 usage) */
int mc_cli_run(const mc_cli_opts *o, const char *root, int backup_keep, FILE *out);

#ifdef __cplusplus
}
#endif
#endif
