///*********************************************************///
///     Developed By:   Keivan Ipchi Hagh                   ///
///     Student Number: 9831073                             ///
///     Due Date:       Thursday, January 23, 2020          ///
///     Course:         Fundamentals Of Programming In C    ///
///     Project Name:   Game Of Life                        ///
///*********************************************************///

#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

/*  --- Coloring Guide ---
	Black           |   0
	Blue            |   1
	Green           |   2
	Cyan            |   3
	Red             |   4
	Magenta         |   5
	Brown           |   6
	Light Gray      |   7
	Dark Gray       |   8
	Light Blue      |   9
	Light Green     |   10
	Light Cyan      |   11
	Light Red       |   12
	Light Magenta   |   13
	Yellow          |   14
	White           |   15
*/

typedef enum Blocks {
    ENERGY = 1,     /// Cell Code Color:    2
    MITOSIS = 2,     /// Cell Code Color:   9
    FORBIDDEN = 3,     /// Cell Code Color: 4
    NORMAL = 4,     /// Cell Code Color:    8
} Blocks;

/// Function: Set Cell Color
void setCellColor(int mapSize, int i, int j, Blocks blockMatrix[][mapSize]) {
    switch(blockMatrix[i][j]) {
        case 1: SetColor(2); break;
        case 2: SetColor(9); break;
        case 3: SetColor(4); break;
        case 4: SetColor(8); break;
    }
}

/// Function: Set Color For Output
void SetColor(int ForgC) {

  	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  	CONSOLE_SCREEN_BUFFER_INFO csbi;

    /// We use 'csbi' for the wAttributes word - /Mask out all but the background attribute, and add in the foreground color
 	if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
      	SetConsoleTextAttribute(hStdOut, (csbi.wAttributes & 0xF0) + (ForgC & 0x0F));
}

#endif // COLOR_H_INCLUDED
