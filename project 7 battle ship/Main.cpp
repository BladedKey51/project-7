/*
Lane Jones-Popp
Computer Science Fall 2024
Dec. 17
Lab 6, Binary to Decimal Conversion
A simple battleship game. It will show that I can write good, well thought code.
*/

#include <iostream>
#include <iomanip>
#include <time.h>
#include <random>

using namespace std;

typedef char board[10][10][6]; //The 3d array that becomes the board for the game 


void iniBoard(board Board); //Precondition   Boards are initialized but are not being displayed 
//Postcondition  The boards will be displayed now

void OutputBoard(board Board, int player); //Precondition  There are boards initialized that do not have ships.
//Postcondition  The boards have user ships that can be displayed.

void PPlacement(board Board); //Precondition   There are boards initialized that do not have ships.
//Postcondition   The boards have computer ships that can be displayed.

void APlacement(board Board); //Precondition:   There is no x input to place ship.
//Postcondition   There is now a x input to place ship

void XPlacement(int& xpoint); //Precondition   There is no y input to place ship.
//Postcondition   There is now a y input to place ship.

void YPlacement(int& ypoint); //Precondition    There is no direction input to place ship.
//Postcondition   There is an x direction to place ship

void DirectionPlacement(int& Shipface); //Precondition    You dont know what is on the board.
//Postcondition   You know the state of the shipps on the board :).

void GameState(board Board); //Precondition   Ships need some shooting 
//Postcondition  You can now do some ship shooting.

void pShot(board Board, int player, bool& playing, int& L); //Precondition    You have shipps that can be shot at.
//Postcondition   The computer can shoot at your ships.

void aShot(board Board); //Precondition   Need to know if the ships are destroyed.
//Postcondition   You now know if the ships are destroyed.

void WinCheck(board Board, bool playing, int& L, int& W); //Precondition   The game is over, but you might want to keep playing
//Postcondition  You have the opertunity to continue to play if you want 

void PlayAgain(bool& again, int& player, bool& playing); //Precondition:    Do you want to know how many times you have won or lose 
//Postcondition:   You now know how many times you have won or lose 

void WL(int W, int L);

int main() {
    bool retry = true;
    bool play = true;
    int player = 0;
    int W = 0;
    int L = 0;
    board Board;
    do {
        iniBoard(Board);
        PPlacement(Board);
        APlacement(Board);
        do {
            GameState(Board);
            pShot(Board, player, play, L);
            if (!play)
                break;
            WinCheck(Board, play, L, W);
            aShot(Board);
            WinCheck(Board, play, L, W);
        } while (play);
        PlayAgain(retry, player, play);
    } while (retry);
    WL(W, L);

    return 0;
}

void iniBoard(board Board) {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            for (int z = 0; z < 6; z++) {
                Board[y][x][z] = '~';
            }
        }
    }
}
void OutputBoard(board Board, int player) {
    for (int z = 0; z < player + 2; z++) {
        cout << endl;
        cout << "   1 2 3 4 5 6 7 8 9 10" << endl;
        for (int y = 0; y < 10; y++) {
            cout << setw(2) << y + 1;
            cout << ' ';
            for (int x = 0; x < 10; x++) {
                cout << Board[y][x][z] << ' ';
            }
            cout << endl;
        }
    }
}
void PPlacement(board Board) {
    int Shipface;
    int xpoint;
    int ypoint;
    char TypeShip;
    int LengthShip;


    for (int a = 0; a < 5; a++) {
        bool print = true;
        OutputBoard(Board, 0);
        switch (a) {
        case 0:
            TypeShip = '5';
            LengthShip = 5;
            cout << "\nPlace your Carrier (length 5)" << endl;
            break;
        case 1:
            TypeShip = '4';
            LengthShip = 4;
            cout << "\nPlace your Battleship (length 4) " << endl;
            break;
        case 2:
            TypeShip = '3';
            LengthShip = 3;
            cout << "\nPlace your Cruiser (length 3) " << endl;
            break;
        case 3:
            TypeShip = '2';
            LengthShip = 3;
            cout << "\nPlace your Submarine (length 3) " << endl;
            break;
        case 4:
            TypeShip = '1';
            LengthShip = 2;
            cout << "\nPlace your Destroyer (length 2) " << endl;
            break;
        }
        XPlacement(xpoint);
        if (!cin) {
            cout << "No input";
            break;
        }
        if (xpoint > 10 || xpoint < 0) {
            cout << "Invalid" << endl;
            a--;
            continue;
        }
        YPlacement(ypoint);
        if (!cin) {
            cout << "No input";
        }
        if (ypoint > 10 || ypoint < 0) {
            cout << "Invalid" << endl;
            a--;
            continue;
        }
        DirectionPlacement(Shipface);
        for (int x = 0; x < LengthShip; x++) {
            if (Shipface == 1) {
                if (Board[ypoint - x][xpoint][1] == '#') {
                    cout << "Invalid" << endl;
                    a--;
                    print = false;
                }
            }
            else if (Shipface == 2) {
                if (Board[ypoint + x][xpoint][1] == '#') {
                    cout << "Invalid" << endl;
                    a--;
                    print = false;
                }
            }
            else if (Shipface == 3) {
                if (Board[ypoint][xpoint - x][1] == '#') {
                    cout << "Invalid" << endl;
                    a--;
                    print = false;
                }
            }
            else if (Shipface == 4) {
                if (Board[ypoint][xpoint + x][1] == '#') {
                    cout << "Invalid" << endl;
                    a--;
                    print = false;
                }
            }
            else {
                if (Board[ypoint][xpoint + x][1] == '#') {
                    cout << "Invalid" << endl;
                    a--;
                    print = false;
                }
            }
            if (!print) {
                break;
            }
        }
        for (int x = 0; x < LengthShip; x++) {
            if (Shipface == 1) {
                if (ypoint - x < 0) {
                    cout << "Invalid" << endl;
                    a--;
                    print = false;
                }
            }
            else if (Shipface == 2) {
                if (ypoint + x > 9) {
                    cout << "Invalid" << endl;
                    a--;
                    print = false;
                }
            }
            else if (Shipface == 3) {
                if (xpoint - x < 0) {
                    cout << "Invalid" << endl;
                    a--;
                    print = false;
                }
            }
            else if (Shipface == 4) {
                if (xpoint + x > 9) {
                    cout << "Invalid" << endl;
                    a--;
                    print = false;
                }
            }
            else {
                if (xpoint + x > 9) {
                    cout << "Invalid" << endl;
                    a--;
                    print = false;
                }
            }
            if (!print) {
                break;
            }
        }
        if (print) {
            for (int x = 0; x < LengthShip; x++) {
                if (Shipface == 1) {
                    Board[ypoint - x][xpoint][1] = '#';
                    Board[ypoint - x][xpoint][4] = TypeShip;
                }
                else if (Shipface == 2) {
                    Board[ypoint + x][xpoint][1] = '#';
                    Board[ypoint + x][xpoint][4] = TypeShip;
                }
                else if (Shipface == 3) {
                    Board[ypoint][xpoint - x][1] = '#';
                    Board[ypoint][xpoint - x][4] = TypeShip;
                }
                else if (Shipface == 4) {
                    Board[ypoint][xpoint + x][1] = '#';
                    Board[ypoint][xpoint + x][4] = TypeShip;
                }
                else {
                    Board[ypoint][xpoint + x][1] = '#';
                    Board[ypoint][xpoint + x][4] = TypeShip;
                }
            }
        }
    }
}
void APlacement(board Board) {
    int Shipface;
    int xpoint;
    int ypoint;
    char TypeShip;
    int LengthShip;

    cout << "The computer will now place its ships...";

    for (int a = 0; a < 5; a++) {
        bool print = true;
        switch (a) {
        case 0:
            TypeShip = '5';
            LengthShip = 5;
            break;
        case 1:
            TypeShip = '4';
            LengthShip = 4;
            break;
        case 2:
            TypeShip = '3';
            LengthShip = 3;
            break;
        case 3:
            TypeShip = '2';
            LengthShip = 3;
            break;
        case 4:
            TypeShip = '1';
            LengthShip = 2;
            break;
        }
        srand(time(NULL));

        xpoint = rand() % 10;
        if (xpoint > 10 || xpoint < 0) {
            a--;
            continue;
        }
        ypoint = rand() % 10;
        if (ypoint > 10 || ypoint < 0) {
            a--;
            continue;
        }
        Shipface = rand() % 4 + 1;
        for (int x = 0; x < LengthShip; x++) {
            if (Shipface == 1) {
                if (Board[ypoint - x][xpoint][3] == '#') {
                    a--;
                    print = false;
                }
            }
            else if (Shipface == 2) {
                if (Board[ypoint + x][xpoint][3] == '#') {
                    a--;
                    print = false;
                }
            }
            else if (Shipface == 3) {
                if (Board[ypoint][xpoint - x][3] == '#') {
                    a--;
                    print = false;
                }
            }
            else if (Shipface == 4) {
                if (Board[ypoint][xpoint + x][3] == '#') {
                    a--;
                    print = false;
                }
            }
            else {
                if (Board[ypoint][xpoint + x][3] == '#') {
                    a--;
                    print = false;
                }
            }
            if (!print) {
                break;
            }
        }
        for (int x = 0; x < LengthShip; x++) {
            if (Shipface == 1) {
                if (ypoint - x < 0) {
                    a--;
                    print = false;
                }
            }
            else if (Shipface == 2) {
                if (ypoint + x > 9) {
                    a--;
                    print = false;
                }
            }
            else if (Shipface == 3) {
                if (xpoint - x < 0) {
                    a--;
                    print = false;
                }
            }
            else if (Shipface == 4) {
                if (xpoint + x > 9) {
                    a--;
                    print = false;
                }
            }
            else {
                if (xpoint + x > 9) {
                    a--;
                    print = false;
                }
            }
            if (!print) {
                break;
            }
        }
        if (print) {
            for (int x = 0; x < LengthShip; x++) {
                if (Shipface == 1) {
                    Board[ypoint - x][xpoint][3] = '#';
                    Board[ypoint - x][xpoint][5] = TypeShip;
                }
                else if (Shipface == 2) {
                    Board[ypoint + x][xpoint][3] = '#';
                    Board[ypoint + x][xpoint][5] = TypeShip;
                }
                else if (Shipface == 3) {
                    Board[ypoint][xpoint - x][3] = '#';
                    Board[ypoint][xpoint - x][5] = TypeShip;
                }
                else if (Shipface == 4) {
                    Board[ypoint][xpoint + x][3] = '#';
                    Board[ypoint][xpoint + x][5] = TypeShip;
                }
                else {
                    Board[ypoint][xpoint + x][3] = '#';
                    Board[ypoint][xpoint + x][5] = TypeShip;
                }
            }
        }
    }
}
void DirectionPlacement(int& Shipface) {
    cout << "Please choose a direction you would like your ship to point(1: Up | 2:Down | 3:Left | 4:Right): ";
    cin >> Shipface;
}
void XPlacement(int& xpoint) {
    cout << "Please choose a x location (top) to place your ship(1-10): ";
    cin >> xpoint;
    xpoint = xpoint - 1;
}
void YPlacement(int& ypoint) {
    cout << "Please choose a y location (side) to place your ship(1-10): ";
    cin >> ypoint;
    ypoint = ypoint - 1;
}
void GameState(board Board) {
    int PCarrier = 0;
    int PBattleship = 0;
    int PCruiser = 0;
    int PSubmarine = 0;
    int PDestroyer = 0;
    int ACarrier = 0;
    int ABattleship = 0;
    int ACruiser = 0;
    int ASubmarine = 0;
    int ADestroyer = 0;

    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if (Board[y][x][4] == '5')
                PCarrier++;
            if (Board[y][x][4] == '4')
                PBattleship++;
            if (Board[y][x][4] == '3')
                PCruiser++;
            if (Board[y][x][4] == '2')
                PSubmarine++;
            if (Board[y][x][4] == '1')
                PDestroyer++;
        }
    }
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if (Board[y][x][5] == '5')
                ACarrier++;
            if (Board[y][x][5] == '4')
                ABattleship++;
            if (Board[y][x][5] == '3')
                ACruiser++;
            if (Board[y][x][5] == '2')
                ASubmarine++;
            if (Board[y][x][5] == '1')
                ADestroyer++;
        }
    }
    if (PCarrier == 0)
        cout << "Your Carrier has been destroyed :(\n";
    if (PBattleship == 0)
        cout << "Your Battleship has been destroyed :(\n";
    if (PCruiser == 0)
        cout << "Your Cruiser has been destroyed :(\n";
    if (PSubmarine == 0)
        cout << "Your Submarine has been destroyed :(\n";
    if (PDestroyer == 0)
        cout << "Your Destroyer has been destroyed :(\n";

    if (ACarrier == 0)
        cout << "Enemy Carrier has been destroyed :)\n";
    if (ABattleship == 0)
        cout << "Enemy Battleship has been destroyed :)\n";
    if (ACruiser == 0)
        cout << "Enemy Cruiser has been destroyed :)\n";
    if (ASubmarine == 0)
        cout << "Enemy Submarine has been destroyed :)\n";
    if (ADestroyer == 0)
        cout << "Enemy Destroyer has been destroyed :)\n";
}
void pShot(board Board, int player, bool& playing, int& L) {
    int xshot;
    int yshot;
    bool active = true;

    OutputBoard(Board, player);

    cout << "\nYour turn to shoot.\nTo choose to surrender enter 42069.";

    do {
        do {
            cout << "\nEnter the x-coridinate (horizontal) to shoot: ";
            cin >> xshot;
            if (xshot == 42069) {
                playing = false;
                active = false;
                L++;
                break;
            }
            if (xshot <= 10 && xshot > 0) {
                xshot -= 1;
                active = false;
            }
            else if (xshot != 42069) {
                cout << "\nBad Input";
            }
        } while (active);
        if (!playing)
            break;
        do {
            cout << "\nEnter the y-coridinate (vertical) to shoot:";
            cin >> yshot;
            if (xshot == 42069) {
                playing = false;
                active = false;
                L++;
                break;
            }
            if (yshot <= 10 && yshot > 0) {
                yshot -= 1;
                active = false;
            }
            else if (yshot != 42069) {
                cout << "\nBad Input";
            }
        } while (active);
        if (!playing)
            break;
        if (Board[yshot][xshot][0] == 'M' || Board[yshot][xshot][0] == 'H')
            cout << "\nInvalid inputs";
        else
            active = false;
    } while (active);

    if (xshot != 42069) {
        if (Board[yshot][xshot][3] == '#') {
            Board[yshot][xshot][0] = 'H';
            Board[yshot][xshot][3] = 'H';
            cout << "\nHit!\n";
        }
        else {
            Board[yshot][xshot][0] = 'M';
            Board[yshot][xshot][3] = 'M';
            cout << "\nMiss!\n";
        }
    }
}

void aShot(board Board) {
    int xshot, yshot;
    bool active = true;

    // Initialize random generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 9);

    cout << "The enemy is firing.";

    do {
        xshot = dis(gen);
        yshot = dis(gen);

        if (Board[yshot][xshot][2] == 'M' || Board[yshot][xshot][2] == 'H') {
            active = true;
        }
        else {
            active = false;
        }

    } while (active);

    if (Board[yshot][xshot][1] == '#') {
        Board[yshot][xshot][2] = 'H';
        Board[yshot][xshot][1] = 'H';
        cout << "\nComputer Hit!\n";

    }
    else { 
        Board[yshot][xshot][2] = 'M';
        Board[yshot][xshot][1] = 'M';
        cout << "\nComputer Miss!\n";
    }
}

void WinCheck(board Board, bool playing, int& L, int& W) {

    int PCarrier = 0;
    int PBattleship = 0;
    int PCruiser = 0;
    int PSubmarine = 0;
    int PDestroyer = 0;

    int ACarrier = 0;
    int ABattleship = 0;
    int ACruiser = 0;
    int ASubmarine = 0;
    int ADestroyer = 0;

    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if (Board[y][x][4] == '5') {
                PCarrier++;
            }
            else if (Board[y][x][4] == '4') {
                PBattleship++;
            }
            else if (Board[y][x][4] == '3') {
                PCruiser++;
            }
            else if (Board[y][x][4] == '2') {
                PSubmarine++;
            }
            else if (Board[y][x][4] == '1') {
                PDestroyer++;
            }
        }
    }
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if (Board[y][x][5] == '5') {
                ACarrier++;
            }
            else if (Board[y][x][5] == '4') {
                ABattleship++;
            }
            else if (Board[y][x][5] == '3') {
                ACruiser++;
            }
            else if (Board[y][x][5] == '2') {
                ASubmarine++;
            }
            else if (Board[y][x][5] == '1') {
                ADestroyer++;
            }
        }
    }
    if (PCarrier == 0 && PBattleship == 0 && PCruiser == 0
        && PSubmarine == 0 && PDestroyer == 0) {
        cout << "All of your ships have been destroyed. You lose!" << endl;
        L++;
        playing = false;
    }
    if (ACarrier == 0 && ABattleship == 0 && ACruiser == 0
        && ASubmarine == 0 && ADestroyer == 0) {
        cout << "You destroyed all of the enemy ships. You win!" << endl;
        W++;
        playing = false;

    }
}
void PlayAgain(bool& again, int& player, bool& playing) {
    int a = 0;
    cout << "\n play again? 1:Yes 2:No\n:";
    cin >> a;
    if (a != 1) {
        again = false;
    }
    else {
        player = 0;
        again = true;
        playing = true;
    }
}
void WL(int W, int L) {
    cout << "\n\nYou ended with " << W << " wins and " << L << " loses.\n";
}