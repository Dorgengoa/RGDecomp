# SPDX-License-Identifier: CC0-1.0
# Included after every project() in a Linux cross build with RG_LINUX_SYSROOT
# (cmake/toolchain-linux-i686.cmake).  tools/linux/sysroot.py --set gui leaves out the unversioned
# dev links (libX11.so -> libX11.so.6.4.0) of the libraries SDL3 dlopens: find them by their
# soname files, so SDL3's FindLibraryAndSONAME bakes the soname (libX11.so.6) into the build.
set(CMAKE_FIND_LIBRARY_SUFFIXES .so .so.0 .so.1 .so.2 .so.3 .so.6 .a)
