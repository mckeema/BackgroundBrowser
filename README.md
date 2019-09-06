# BackgroundBrowser

BackgroundBrowser is an image viewer/downloader for [Wallhaven](https://wallhaven.cc).

__Features__
* Display 6, 12, or 24 images at a time
* Easily download multiple images at once
* Save to user-specified download folder
* Input your Wallhaven API key

## Screenshots

![Main Window](https://i.imgur.com/ZtbcaqP.png)
![Settings](https://i.imgur.com/JGIyM2t.png)
![Image Window](https://i.imgur.com/buBlTN6.png)

## Download

[Linux](http://bit.ly/BBlinux8664)

[Windows](http://bit.ly/BBwin86)

## Compilation

### Linux

Clone or download the repository from this page, then enter the BackgroundBrowser
directory and execute the following:

```bash
qmake .
make
```

If you wish to create an AppDir for AppImage creation, also create a folder named
"AppDir" and execute:

```bash
make install INSTALL_ROOT=AppDir
```

### Windows (on Linux using cross compiler)

Download mxe:

```bash
git clone https://github.com/mxe/mxe.git
```

Enter the mxe directory and run:

```bash
make qt5
```

Enter the BackgroundBrowser directory and add mxe to your path:

```bash
export PATH=$PATH:<mxe directory>/usr/bin
```

Run mxe's qmake:

```bash
<mxe directory>/usr/i686-w64-mingw32.static/qt5/bin/qmake
make
```

The executable should appear in a new directory called "release".

Thanks to [this Stack Overflow user](https://stackoverflow.com/users/321731/tshepang) for 
[these instructions](https://stackoverflow.com/a/13211922), which I based the above on.

## About Qt

BackgroundBrowser was created using Qt 5.12.3. See more about Qt at [qt.io](https://qt.io).
