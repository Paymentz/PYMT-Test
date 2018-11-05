
Debian
====================
This directory contains files used to package PYMTd/PYMT-qt
for Debian-based Linux systems. If you compile PYMTd/PYMT-qt yourself, there are some useful files here.

## PYMT: URI support ##


PYMT-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install PYMT-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your PYMTqt binary to `/usr/bin`
and the `../../share/pixmaps/PYMT128.png` to `/usr/share/pixmaps`

PYMT-qt.protocol (KDE)

