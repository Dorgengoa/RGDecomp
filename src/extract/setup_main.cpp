// SPDX-License-Identifier: CC0-1.0
// rg-setup: the one-step first run of a published build (docs/RELEASE.md).
//
//   Setup.exe [disc image .iso]          (Linux: ./rg-setup [disc image .iso])
//
// 1. Finds the disc image: the argument (drag the .iso onto Setup.exe), else the one .iso
//    in Setup.exe's folder.
// 2. Unpacks it into data/ beside Setup.exe with rg-extract's code (checks it is the
//    supported disc first). Skipped when data/ is already complete.
// 3. Builds rg-game.exe from rg-game.blank + rg-game.fill: the published exe has the bytes
//    that come from the game's own files zeroed, and the .fill table says which file and
//    offset in data/ each run is copied back from. Both SHA-256 values are checked.
// 4. Gives the finished exe its file icon, made from data/ (src/icon, docs/ICON.md): the
//    zip carries no art, so the icon resource is added here, after the checksum check
//    (the checked bytes are the published exe's; the icon is extra and deterministic).
#include "extract.h"
#include "hash.h"
#include "rg_icon.h"

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <system_error>
#include <vector>

namespace fs = std::filesystem;

namespace {

// Linux (docs/RELEASE.md "Linux player zip"): the same steps; the finished game is
// `rg-game` with the execute bits set, and there is no exe icon (the game sets its window
// icon itself, src/icon).
#ifdef _WIN32
#define RG_GAME_NAME "rg-game.exe"
#else
#define RG_GAME_NAME "rg-game"
#endif

bool read_file(const fs::path& p, std::vector<uint8_t>& out) {
    std::ifstream f(p, std::ios::binary);
    if (!f) return false;
    out.assign(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
    return true;
}

std::string sha256_hex(const std::vector<uint8_t>& b) {
    rgx::Sha256 h;
    h.update(b.data(), b.size());
    return h.finish_hex();
}

int fill_exe(const fs::path& dir) {
    const fs::path blank_p = dir / "rg-game.blank", table_p = dir / "rg-game.fill";
    const fs::path data = dir / "data", out_p = dir / RG_GAME_NAME;
    std::vector<uint8_t> exe;
    if (!read_file(blank_p, exe)) {
        std::cerr << "Setup: rg-game.blank is missing. Unzip the whole package again.\n";
        return 10;
    }
    std::ifstream t(table_p);
    if (!t) {
        std::cerr << "Setup: rg-game.fill is missing. Unzip the whole package again.\n";
        return 10;
    }
    std::string line, blank_sha, exe_sha;
    std::map<std::string, std::vector<uint8_t>> files;
    size_t rows = 0;
    while (std::getline(t, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream s(line);
        std::string a, b, c, d;
        s >> a >> b;
        if (a == "blank_sha256") { blank_sha = b; continue; }
        if (a == "exe_sha256") { exe_sha = b; continue; }
        if (a == "exe_size") continue;
        s >> c >> d;
        if (d.empty()) {
            std::cerr << "Setup: rg-game.fill is damaged. Unzip the whole package again.\n";
            return 11;
        }
        if (rows == 0 && sha256_hex(exe) != blank_sha) {
            std::cerr << "Setup: rg-game.blank is damaged. Unzip the whole package again.\n";
            return 11;
        }
        const uint64_t eo = std::stoull(a, nullptr, 16), fo = std::stoull(c, nullptr, 16),
                       n = std::stoull(d, nullptr, 16);
        auto it = files.find(b);
        if (it == files.end()) {
            std::vector<uint8_t> v;
            if (!read_file(data / fs::path(b), v)) {
                std::cerr << "Setup: data/" << b << " is missing. Delete the data folder and run Setup again.\n";
                return 12;
            }
            it = files.emplace(b, std::move(v)).first;
        }
        if (eo + n > exe.size() || fo + n > it->second.size()) {
            std::cerr << "Setup: rg-game.fill does not match data/" << b << ".\n";
            return 11;
        }
        std::copy_n(it->second.begin() + fo, n, exe.begin() + eo);
        rows++;
    }
    if (sha256_hex(exe) != exe_sha) {
        std::cerr << "Setup: the finished " RG_GAME_NAME " does not check out (wrong disc files or a damaged download).\n";
        return 13;
    }
    const fs::path tmp = dir / RG_GAME_NAME ".partial";
    {
        std::ofstream o(tmp, std::ios::binary | std::ios::trunc);
        o.write(reinterpret_cast<const char*>(exe.data()), static_cast<std::streamsize>(exe.size()));
        if (!o) {
            std::cerr << "Setup: could not write " RG_GAME_NAME " (disk full or folder read-only?).\n";
            return 5;
        }
    }
    // the file icon (optional: without it the game still runs and sets its window icon itself)
#ifdef _WIN32
    {
        rg_icon_set icon;
        char err[256] = "";
        if (rg_icon_build(data.u8string().c_str(), RG_ICON_DEFAULT, &icon, err, sizeof err) == 0) {
            if (rg_icon_embed_exe(tmp.u8string().c_str(), &icon, err, sizeof err) == 0)
                std::cout << "Setup: added the game icon to rg-game.exe.\n";
            else
                std::cout << "Setup: (no exe icon: " << err << ")\n";
            rg_icon_free(&icon);
        } else {
            std::cout << "Setup: (no exe icon: " << err << ")\n";
        }
    }
#else
    {
        std::error_code pe;
        fs::permissions(tmp, fs::perms::owner_exec | fs::perms::group_exec | fs::perms::others_exec,
                        fs::perm_options::add, pe);
        if (pe) {
            std::cerr << "Setup: could not make " RG_GAME_NAME " executable: " << pe.message() << "\n";
            return 5;
        }
    }
#endif
    std::error_code ec;
    fs::rename(tmp, out_p, ec);
    if (ec) {
        std::cerr << "Setup: could not write " RG_GAME_NAME ": " << ec.message() << "\n";
        return 5;
    }
    std::cout << "Setup: built " RG_GAME_NAME " (" << rows << " runs restored, checksum OK).\n";
    return 0;
}

fs::path find_iso(const fs::path& dir, std::string& why) {
    std::vector<fs::path> isos;
    std::error_code ec;
    for (auto& e : fs::directory_iterator(dir, ec)) {
        auto ext = e.path().extension().u8string();
        std::transform(ext.begin(), ext.end(), ext.begin(), [](char ch) { return (char)std::tolower((unsigned char)ch); });
        if (e.is_regular_file() && ext == ".iso") isos.push_back(e.path());
    }
    if (isos.size() == 1) return isos[0];
#ifdef _WIN32
    why = isos.empty() ? "No .iso file found next to Setup.exe. Copy your Rogue Galaxy (USA) disc image into this folder, or drag it onto Setup.exe."
                       : "More than one .iso file is in this folder. Leave only the Rogue Galaxy one, or drag it onto Setup.exe.";
#else
    why = isos.empty() ? "No .iso file found next to rg-setup. Copy your Rogue Galaxy (USA) disc image into this folder, or give its path: ./rg-setup /path/to/image.iso"
                       : "More than one .iso file is in this folder. Leave only the Rogue Galaxy one, or give its path: ./rg-setup /path/to/image.iso";
#endif
    return {};
}

int run(const fs::path& self, const fs::path& arg_iso) {
    const fs::path dir = self.parent_path();
    const fs::path data = dir / "data";
    if (fs::exists(data / "MANIFEST.tsv")) {
        std::cout << "Setup: data/ is already unpacked; skipping the disc.\n";
    } else {
        std::string why;
        fs::path iso = arg_iso.empty() ? find_iso(dir, why) : arg_iso;
        if (iso.empty()) {
            std::cerr << "Setup: " << why << "\n";
            return 1;
        }
        std::cout << "Setup: unpacking " << iso.filename().u8string()
#ifdef _WIN32
                  << " into data\\ (about 9 GB, takes a few minutes)...\n";
#else
                  << " into data/ (about 9 GB, takes a few minutes)...\n";
#endif
        rgx::Options opt;
        opt.iso = iso;
        opt.out = data;
        int rc = rgx::run_extract(opt);
        if (rc != rgx::kOk) {
            std::cerr << "Setup: unpacking failed (code " << rc << "). See the message above.\n";
            return rc;
        }
    }
    int rc = fill_exe(dir);
    if (rc == 0)
#ifdef _WIN32
        std::cout << "\nAll done. Double-click rg-game.exe to play. You may delete the .iso now.\n";
#else
        std::cout << "\nAll done. Run ./rg-game to play. You may delete the .iso now.\n";
#endif
    return rc;
}

void pause_if_console_owner() {
#ifdef _WIN32
    std::cout << "\nPress Enter to close this window.";
    std::string s;
    std::getline(std::cin, s);
#endif
}

}  // namespace

#ifdef _WIN32
int wmain(int argc, wchar_t** argv) {
    fs::path self = fs::absolute(fs::path(argv[0]));
    int rc = run(self, argc > 1 ? fs::path(argv[1]) : fs::path());
    pause_if_console_owner();
    return rc;
}
#else
int main(int argc, char** argv) {
    return run(fs::absolute(fs::path(argv[0])), argc > 1 ? fs::path(argv[1]) : fs::path());
}
#endif
