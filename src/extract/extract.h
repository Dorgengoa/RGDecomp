// SPDX-License-Identifier: CC0-1.0
// rg-extract core: verify the user's Rogue Galaxy disc image and unpack it into data/.
#pragma once

#include <cstdint>
#include <filesystem>
#include <ostream>
#include <string>

namespace rgx {

// The one image rg-extract accepts: Rogue Galaxy (USA), SCUS-97490, VER 1.01 (DVD9).
struct AcceptedImage {
    const char* title;
    const char* serial;   // as in SYSTEM.CNF BOOT2, e.g. "SCUS_974.90"
    const char* version;  // SYSTEM.CNF VER
    uint64_t size;
    const char* sha1;
};
extern const AcceptedImage kAcceptedImage;

enum ExitCode : int {
    kOk = 0,
    kUsage = 1,
    kUnreadableIso = 2,
    kWrongImage = 3,
    kOutputExists = 4,
    kWriteFailed = 5,  // includes disk full
    kMalformedIso = 6,
};

struct Options {
    std::filesystem::path iso;
    std::filesystem::path out;   // final data directory
    bool force = false;          // replace an existing extraction
    bool list_only = false;      // print the file table and stop (no hash, no writes)
    std::string expect_sha1;     // empty = kAcceptedImage; otherwise accept this SHA-1 instead
    bool convert_movies = true;  // also write data/converted/MOVIE/... (docs/MVI.md)
    bool progress = true;
    std::ostream* log = nullptr;  // informational output (default std::cout)
    std::ostream* err = nullptr;  // errors and progress (default std::cerr)
};

int run_extract(const Options& opt);

// SYSTEM.CNF fields of an image, for naming a wrong disc. Empty when absent.
struct DiscIdentity {
    std::string boot2;    // e.g. "cdrom0:\SCUS_974.90;1"
    std::string serial;   // e.g. "SCUS-97490"
    std::string version;  // e.g. "1.01"
    std::string region;   // "USA (NTSC-U)", "Europe (PAL)", "Japan/Asia (NTSC-J)" or ""
};
DiscIdentity parse_system_cnf(const std::string& text);

}  // namespace rgx
