///*********************************************************///
///     Developed By:   Keivan Ipchi Hagh                   ///
///     Student Number: 9831073                             ///
///     Due Date:       Thursday, January 23, 2020          ///
///     Course:         Fundamentals Of Programming In C    ///
///     Project Name:   Game Of Life                        ///
///*********************************************************///

#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

/// Function: Game Of Life Header

void GameOfLife_Header() {
    SetColor(9);
    printf("----------------------------------------------- Game Of Life Simulation ------------------------------------------------\n\n");
    SetColor(15);
}

/// Function: Single Player Header
void SinglePlayer_Header() {
    SetColor(9);
    printf("-------------------------------------- Game Of Life Simulation - Single Player ----------------------------------------\n\n");
    SetColor(15);
}

/// Function: Multi Player Header
void MultiPlayer_header() {
    SetColor(9);
    printf("--------------------------------------- Game Of Life Simulation - MultiPlayer -----------------------------------------\n\n");
    SetColor(15);
}

#endif // HEADERS_H_INCLUDED
