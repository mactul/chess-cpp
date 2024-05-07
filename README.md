# Chess C++

## Compilation

This project use xmake for powerful cross-platform and highly customizable compilation.

To install xmake, go to the [xmake installation page](https://xmake.io/#/guide/installation) and scroll down to see the installation step for your specific operating system.


Once xmake is installed, go to the project folder and run `xmake` command to compile the project
```
cd chess-cpp
xmake
```

Then use `xmake r` to run the executable (alternatively, the executable will be in `chess-cpp/build/linux/x86_64/release` or a path similar depending of your architecture).

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

## Structure of the project

### Main.cpp

The game interface is contained in `main.cpp` file.  
This file is mostly a big loop that requests for algebraic notations, display error messages and switch from black to white player each turn.

### Board.cpp

This file contains all the method to manipulate the board.  
The board is mostly a 8x8 array containing pointers to `Piece` or `nullptr` for an empty square.

To interact with the board, we have to use the `get_piece` and `set_piece` methods.  
To move a piece, we have to set the pointer at the new position and set `nullptr` at the last position.  
This mechanic is operated by the `piece.cpp/unrestricted_move` method which also ensure that every duplicated data between Board/Piece stays coherent and each eaten Piece is deleted in memory.

### Piece.cpp

This file contains all the method for the abstract class representing a piece.  
The most important method of this file is `move_no_geometry`. With this method, we can move a piece regardless of the geometry of the movement but ensuring that every other aspect of the move is legal. In particular, a move that makes the king in chess is illegal.

The method `Piece.move` is defined as a virtual method and precisely defined for each type of piece in the `pieces` folder.
This method move the piece only if the movement is entirely legal.