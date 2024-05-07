# Chess

## Compilation

This project use xmake for powerful cross-platform and highly customizable compilation.

To install xmake, go to the [xmake installation page](https://xmake.io/#/guide/installation) and scroll down to see the installation step for your specific operating system.


Once xmake is installed, go to the project folder and run `xmake` command to compile the project
```
cd chess
xmake
```

Then use `xmake r` to run the executable (alternatively, the executable will be in `chess/build/linux/x86_64/release` or a path similar depending of your architecture).

### If you have any issue
You can change the compilation configuration via `xmake f`, if you are lost, `xmake f --menu` display a graphic interface to help you.

For example, if you have a problem with the display of Unicode chess characters, you can compile the project using only ascii like that:
```sh
xmake f --only_ascii=y
xmake -r  # "-r" is for rebuild all
```

If you are using a cross-platform compiler like MinGW on Windows, you can configure the platform with `-p` argument.
```sh
xmake f -p mingw
```
