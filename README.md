# AppLinkDesktop

Simple application for managing applications' links on the desktop.
<p align="center">
   <img src="https://github.com/YetAnotherWorld/AppLinkDesktop/blob/main/screenshot/screenshot.png"/>
</p>

## Features

* displays a list of all linkable applications on the desktop;
* add application link on the desktop;
* remove application link;
* changes are made only when clicking the apply button.

## Dependancies

This application is written using KDE framework, KDE Kirigmai, Qt and Qml. Here is a list of all dependancies needed to build the project:

* ECM (required version >= 5.68)
* Qt5Gui
* Qt5Network (required version >= 5.15.5)
* Qt5Qml
* Qt5QmlModels (required version >= 5.15.5)
* Qt5Quick (required version >= 5.15.5)
* Qt5QuickControls2
* Qt5Widgets (required version >= 5.15.5)
* Qt5Svg
* Qt5 (required version >= 5.15)
* KF5Kirigami2 (required version >= 5.83)
* KF5CoreAddons (required version >= 5.83)
* KF5Config (required version >= 5.83)
* Qt5Core (required version >= 5.15.2)
* Gettext
* KF5I18n (required version >= 5.83)
* KF5 (required version >= 5.83)

### How to install dependancies

#### Debian (sid), Ubuntu and Ubuntu based system(Pop!\_OS, Linus Mint, KDE Neon...)

You need at least version 21.10.
Open your favorite **terminal emulator**

```bash
sudo apt install cmake extra-cmake-modules qml qtdeclarative5-dev qtquickcontrols2-5-dev libqt5svg5-dev libkf5coreaddons-dev Libkf5config-dev libkf5i18n-dev gettext
```

#### Manjaro and Arch

```bash
sudo pacman -Syu --needed base-devel cmake extra-cmake-modules
```

if you are not already using KDE desktop environment:

```bash
sudo pacman -Syu --needed qt5-svg qt5-tools qt5-x11extras kdesdk 
```

## Building and Installation

Open your favorite **terminal emulator**

Upgrade your system:
-> For Debian based distros:

```bash
sudo apt update 
sudo apt upgrade
```

-> For Arch based distros:

```bash
sudo pacman -Syu
```

Make a directory for Github project:

```bash
mkdir $HOME/Github
```
Go into it:

```bash
cd $HOME/Github
```
Clone this Github repository inside (if you don't have git, install it or download the project archive from Github)

```bash
git clone https://github.com/YetAnotherWorld/AppLinkDesktop.git
```
Make a new repository for building the project:

```bash
mkdir AppLinkDesktop/build
```

Go into it:

```bash
cd AppLinkDesktop/build
```

Build the project:

```bash
cmake -DCMAKE_INSTALL_PREFIX=`kf5-config --prefix` -DCMAKE_BUILD_TYPE=release ..
```
Install it:

```bash
sudo make install
```

## Uninstall

```bash
sudo xargs rm < $HOME/Github/AppLinkDesktop/build/install_manifest.txt
```

or 

```bash
cd $HOME/Github/ApplinkDesktop/build
sudo make uninstall
```

## Upgrade

```bash
cd $HOME/Github/ApplinkDesktop/
git fetch
git pull origin main
cd $HOME/Github/ApplinkDesktop/build
cmake -DCMAKE_INSTALL_PREFIX=`kf5-config --prefix` -DCMAKE_BUILD_TYPE=release ..
sudo make install
```

## TODO
- [ ] better align icons with each other
- [ ] add fallback icons
- [ ] add tooltips
- [ ] translation

