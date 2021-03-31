#include <iostream>
#include <Windows.h>
#include <string>
#include <time.h>
#include <fstream>
using namespace std;

//This game is platform-dependent

bool gameOver = false;
char nick[5]{};
int odliczacz{};
int poziom = 1;

//to nie jest moj kod
// x is the column, y is the row. The origin (0,0) is top-left.
void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

//to juz moj kod

void WYBOR()
{
    cout << "PODAJ SWOJ NICK (4 znaki): ";
    cin.getline(nick, 5);

    setCursorPosition(0, 0);
    cout << "                                                                                                           ";
    setCursorPosition(0, 0);
    system("cls");
}

void GRA()
{
    fstream plik;
    bool wMenu = true;
    bool wGrze = false;
    bool wWyjsciu = false;
    bool wInstrukcjach = false;
    bool wSalichwaly = false;
    bool ekranPrzegranego = false;
    bool wUstawieniach = false;
    bool wybierajka;
    bool wybierajka2;
    bool wybierajka3;
    bool wybierajka4;
    bool wybierajka5;
    bool wybierajka6;
    bool przeciwnik_zyje = true;
    int wybierajkaX = 9;
    int wybierajkaY = 11;
    int tymwybierajkaX{0};
    int tymwybierajkaY{0};
    int graczX = 579;
    int graczY = 20;
    int przeciwnikX = 10;
    int przeciwnikY = 1;
    int score{};
    int pociski = 9;
    char tabMenu[22][22] =
    { 
        {"#####################"},
        {"#                   #"},
        {"#                   #"},
        {"#    {PROMIENIE}    #"},
        {"#   {MAGNETYCZNE}   #"},
        {"#       {GRA}       #"},
        {"#                   #"},
        {"#       |\\ /|       #"},
        {"#       | - |       #"},
        {"#       | - |       #"},
        {"#                   #"},
        {"#         ^         #"},
        {"#         S         #"},
        {"#         I         #"},
        {"#         W         #"},
        {"#        SCH        #"},
        {"#         U         #"},
        {"#         v         #"},
        {"#                   #"},
        {"#       ENTER       #"},
        {"#  aby zatwierdzic  #"},
        {"#####################"}
    };

    char tabMapa[22][22] = 
    {
        {"#####################"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#         @         #"},
        {"#####################"}
    };

    char tabKoniecgry[22][22] =
    {
        {"#####################"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#         :(        #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#    KONIEC GRY!    #"},
        {"#                   #"},
        {"#                   #"},
        {"#  WYNIK:           #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#                   #"},
        {"#   [ENTER] menu    #"},
        {"# [ESC] wyjdz z gry #"},
        {"#####################"}
    };

    char tabInstrukcje[22][22] =
    {
        {"_____________________"},
        {"      INSTRUKCJA     "},
        {"                     "},
        {"                     "},
        {" Twoim zadaniem jak  "},
        {" to zwykle bywa...   "},
        {" zebrac najwiecej    "},
        {" punktow. Jako @     "},
        {" mozesz poruszac sie "},
        {" za pomoca [A] i [D] "},
        {" oraz strzelac przy  "},
        {" uzyciu [SPACE] (gdy "},
        {" masz naboje). Twoje "},
        {" wszystkie wyniki    "},
        {" mozesz sprawdzic w  "},
        {" SALI CHWALY z MENU. "},
        {"                     "},
        {"                     "},
        {" POWODZENIA!         "},
        {"                     "},
        {" [ESC] wroc do menu  "},
        {"_____________________"}
    };
     
    //petla ktora rysuje menu

    setCursorPosition(0, 0);

    for (int y = 0; y < 22; y++)
    {
        for (int x = 0; x < 22; x++)
        {
            cout << tabMenu[y][x];
        }
        cout << endl;
    }

    tabMapa[przeciwnikY][przeciwnikX] = '$';

    while (wMenu)
    {
        wybierajka = true;
        wybierajka2 = true;
        wybierajka3 = true;
        wybierajka4 = true;
        wybierajka5 = true;
        wybierajka6 = true;

        //zmiana wyboru w menu
        while (wybierajka)
        {

            if ((GetKeyState(0x28) & 0x8000) && wybierajkaY <= 15)
            {
                if (wybierajkaY == 15)
                {
                    setCursorPosition(wybierajkaX - 1, wybierajkaY);
                    cout << " ";
                    setCursorPosition(wybierajkaX + 3, wybierajkaY);
                    cout << " ";
                    wybierajkaY += 1;
                    setCursorPosition(wybierajkaX, wybierajkaY);
                    cout << "|";
                    setCursorPosition(wybierajkaX + 2, wybierajkaY);
                    cout << "|";

                    setCursorPosition(7, 24);
                    cout << "                        ";
                    setCursorPosition(7, 24);
                    cout << "USTAWIENIA";
                }
                else if (wybierajkaY == 14)
                {
                    setCursorPosition(wybierajkaX, wybierajkaY);
                    cout << " ";
                    setCursorPosition(wybierajkaX + 2, wybierajkaY);
                    cout << " ";
                    wybierajkaY += 1;
                    setCursorPosition(wybierajkaX - 1, wybierajkaY);
                    cout << "|";
                    setCursorPosition(wybierajkaX + 3, wybierajkaY);
                    cout << "|";
                    
                    setCursorPosition(7, 24);
                    cout << "                        ";
                    setCursorPosition(7, 24);
                    cout << "SALA CHWALY";
                }
                else if (wybierajkaY == 13)
                {
                    setCursorPosition(wybierajkaX, wybierajkaY);
                    cout << " ";
                    setCursorPosition(wybierajkaX + 2, wybierajkaY);
                    cout << " ";
                    wybierajkaY += 1;
                    setCursorPosition(wybierajkaX, wybierajkaY);
                    cout << "|";
                    setCursorPosition(wybierajkaX + 2, wybierajkaY);
                    cout << "|";

                    setCursorPosition(7, 24);
                    cout << "                        ";
                    setCursorPosition(7, 24);
                    cout << "WYJSCIE";
                }
                else if (wybierajkaY == 12)
                {
                    setCursorPosition(wybierajkaX, wybierajkaY);
                    cout << " ";
                    setCursorPosition(wybierajkaX + 2, wybierajkaY);
                    cout << " ";
                    wybierajkaY += 1;
                    setCursorPosition(wybierajkaX, wybierajkaY);
                    cout << "|";
                    setCursorPosition(wybierajkaX + 2, wybierajkaY);
                    cout << "|";

                    setCursorPosition(7, 24);
                    cout << "                        ";
                    setCursorPosition(7, 24);
                    cout << "INSTRUKCJA";
                }
                else if (wybierajkaY == 11)
                {
                    setCursorPosition(wybierajkaX, wybierajkaY);
                    cout << " ";
                    setCursorPosition(wybierajkaX + 2, wybierajkaY);
                    cout << " ";
                    wybierajkaY += 1;
                    setCursorPosition(wybierajkaX, wybierajkaY);
                    cout << "|";
                    setCursorPosition(wybierajkaX + 2, wybierajkaY);
                    cout << "|";

                    setCursorPosition(7, 24);
                    cout << "                        ";
                    setCursorPosition(7, 24);
                    cout << "START";
                }
                wybierajka = false;
                Sleep(150);
            }
            else if ((GetKeyState(0x26) & 0x8000) && wybierajkaY > 12)
            {
                if (wybierajkaY == 16)
                {
                    setCursorPosition(wybierajkaX, wybierajkaY);
                    cout << " ";
                    setCursorPosition(wybierajkaX + 2, wybierajkaY);
                    cout << " ";
                    wybierajkaY -= 1;
                    setCursorPosition(wybierajkaX - 1, wybierajkaY);
                    cout << "|";
                    setCursorPosition(wybierajkaX + 3, wybierajkaY);
                    cout << "|";
                    
                    setCursorPosition(7, 24);
                    cout << "                        ";
                    setCursorPosition(7, 24);
                    cout << "SALA CHWALY";
                }
                else if (wybierajkaY == 15)
                {
                    setCursorPosition(wybierajkaX - 1, wybierajkaY);
                    cout << " ";
                    setCursorPosition(wybierajkaX + 3, wybierajkaY);
                    cout << " ";
                    wybierajkaY -= 1;
                    setCursorPosition(wybierajkaX, wybierajkaY);
                    cout << "|";
                    setCursorPosition(wybierajkaX + 2, wybierajkaY);
                    cout << "|";

                    setCursorPosition(7, 24);
                    cout << "                        ";
                    setCursorPosition(7, 24);
                    cout << "WYJSCIE";
                    
                }
                else if (wybierajkaY == 14)
                {
                    setCursorPosition(wybierajkaX, wybierajkaY);
                    cout << " ";
                    setCursorPosition(wybierajkaX + 2, wybierajkaY);
                    cout << " ";
                    wybierajkaY -= 1;
                    setCursorPosition(wybierajkaX, wybierajkaY);
                    cout << "|";
                    setCursorPosition(wybierajkaX + 2, wybierajkaY);
                    cout << "|";

                    setCursorPosition(7, 24);
                    cout << "                        ";
                    setCursorPosition(7, 24);
                    cout << "INSTRUKCJA";
                }
                else if (wybierajkaY == 13)
                {
                    setCursorPosition(wybierajkaX, wybierajkaY);
                    cout << " ";
                    setCursorPosition(wybierajkaX + 2, wybierajkaY);
                    cout << " ";
                    wybierajkaY -= 1;
                    setCursorPosition(wybierajkaX, wybierajkaY);
                    cout << "|";
                    setCursorPosition(wybierajkaX + 2, wybierajkaY);
                    cout << "|";

                    setCursorPosition(7, 24);
                    cout << "                        ";
                    setCursorPosition(7, 24);
                    cout << "START";
                }

                wybierajka = false;
                Sleep(150);
            }


            if ((GetKeyState(0x0D) & 0x8000) && wybierajkaY == 12)
            {
                wGrze = true;
                wMenu = false;
                wybierajka = false;
                system("cls");
                for (int y = 0; y < 22; y++)
                {
                    for (int x = 0; x < 22; x++)
                    {
                        cout << tabMapa[y][x];
                    }
                    cout << endl;
                }
            }
            else if ((GetKeyState(0x0D) & 0x8000) && wybierajkaY == 13)
            {
                wInstrukcjach = true;
                wMenu = false;
                wybierajka = false;
                system("cls");
                setCursorPosition(0, 0);
            }
            else if ((GetKeyState(0x0D) & 0x8000) && wybierajkaY == 14)
            {
                wWyjsciu = true;
                wMenu = false;
                wybierajka = false;
                setCursorPosition(0, 25);
                gameOver = true;
            }
            else if ((GetKeyState(0x0D) & 0x8000) && wybierajkaY == 15)
            {
                wSalichwaly = true;
                wMenu = false;
                wybierajka = false;
                system("cls");
                setCursorPosition(0, 0);
            }
            else if ((GetKeyState(0x0D) & 0x8000) && wybierajkaY == 16)
            {
                wUstawieniach = true;
                wMenu = false;
                wybierajka = false;
                system("cls");
                setCursorPosition(0, 0);
            }
        }
    }

    while (wUstawieniach)
    {
        cout << "NACISNIJ ODPOWIEDNI KLAWISZ\n\n[L] - Latwy\n[S] - Sredni\n[T] - Trudny\n\nAby wybrac poziom trudnosci.";

        while (wybierajka6)
        {
            if (GetKeyState('L') & 0x8000)
            {
                wMenu = true;
                poziom = 3;
                wybierajka6 = false;
                wUstawieniach = false;
                system("cls");
            }
            else if (GetKeyState('S') & 0x8000)
            {
                wMenu = true;
                poziom = 2;
                wybierajka6 = false;
                wUstawieniach = false;
                system("cls");
            }
            else if (GetKeyState('T') & 0x8000)
            {
                wMenu = true;
                poziom = 1;
                wybierajka6 = false;
                wUstawieniach = false;
                system("cls");
            }
        }
    }

    while (wSalichwaly)
    {
        plik.open("SALA_CHWALY.txt", ios::in);

        if (plik.good() == false)
        {
            cout << "TO JUZ WSZYSCY\n[ESC] aby wrocic...";
            exit(0);
        }

        string linia;
        int licznik = 1;

        cout << "        |\\/\\/|     " << endl;
        cout << "**********************" << endl;

        while (getline(plik,linia))
        {
            setCursorPosition(0, licznik);
            cout << "*";
            setCursorPosition(5, licznik);
            cout << linia;
            setCursorPosition(21, licznik);
            cout << "*";
            licznik++;
            cout << endl;
        }

        cout <<"**********************" << endl;

        cout << endl <<"TO JUZ WSZYSCY\n[ESC] aby wrocic...";

        while (wybierajka5)
        {
            if (GetKeyState(0x1B) & 0x8000)
            {
                wMenu = true;
                wybierajka5 = false;
                wSalichwaly = false;
                system("cls");
            }
        }
    }

    while (wInstrukcjach)
    {
        for (int y = 0; y < 22; y++)
        {
            for (int x = 0; x < 22; x++)
            {
                cout << tabInstrukcje[y][x];
            }
            cout << endl;
        }

        while (wybierajka4)
        {
            if (GetKeyState(0x1B) & 0x8000)
            {
                wMenu = true;
                wInstrukcjach = false;
                wybierajka4 = false;
                system("cls");
            }
        }
    }

    while (wGrze)
    {
        srand(time(NULL));
        while (wybierajka2)
        {
            if (GetKeyState('D') & 0x8000)
            {
                setCursorPosition(graczX%19 + 1, graczY);
                cout << " ";
                graczX += 1;
                setCursorPosition(graczX%19 + 1, graczY);
                cout << "@";
                setCursorPosition(0, 25);
            }            
            else if (GetKeyState('A') & 0x8000)
            {
                setCursorPosition(graczX % 19 + 1, graczY);
                cout << " ";
                graczX -= 1;
                setCursorPosition(graczX % 19 + 1, graczY);
                cout << "@";
                setCursorPosition(0, 25);
            }
            
            setCursorPosition(przeciwnikX, przeciwnikY);
            cout << " ";

            //poziom trudnosci

            if (odliczacz % poziom == 0)
            {
                przeciwnikY += 1;
            }

            setCursorPosition(przeciwnikX, przeciwnikY);
            cout << "$";
            setCursorPosition(0, 25);

            if ((GetKeyState(0x20) & 0x8000) && (pociski > 0))
            {
                int pozycja_strzalu = graczX % 19 + 1;

                for (int i = 1; i < 22; i++)
                {
                    setCursorPosition(pozycja_strzalu, i % 19 + 1);
                    cout << " ";
                    setCursorPosition(pozycja_strzalu, i % 19 + 1);
                    cout << "|";
                    if (tabMapa[i][pozycja_strzalu%20] == '$')
                    {
                        tabMapa[i][pozycja_strzalu%20] = ' ';
                        przeciwnikX = rand() % 19 + 1;
                        przeciwnikY = 1;
                        tabMapa[przeciwnikY][przeciwnikX] = '$';
                        score += 100;
                        pociski = pociski + 2;
                    }
                }
                Sleep(10);
                for (int i = 1; i < 22; i++)
                {
                    setCursorPosition(pozycja_strzalu, i % 19 + 1);
                    cout << " ";
                }
                
                setCursorPosition(0, 23);
                cout << "                                            ";
                setCursorPosition(0, 23);
                
                if (pociski - 1 >= 0)
                {
                    pociski = pociski - 1;
                }
                cout << "PUNKTY: " << score << " POCISKI: " << pociski;
            }

            if (przeciwnikY == 20)
            {
                wGrze = false;
                wybierajka2 = false;
                ekranPrzegranego = true;
                system("cls");
            }

            Sleep(60);
            odliczacz++;
        }
    }

    while (ekranPrzegranego)
    {
        for (int y = 0; y < 22; y++)
        {
            for (int x = 0; x < 22; x++)
            {
                cout << tabKoniecgry[y][x];
            }
            cout << endl;
        }

        if (score >= 1000)
        {
            plik.open("SALA_CHWALY.txt", ios::out | ios::app);

            if ((nick[0] != 0) && (nick[1] != 0) && (nick[2] != 0) && (nick[3] != 0))
            {
                plik << nick[0] << nick[1] << nick[2] << nick[3] << "  " << score << endl;
            }
            else
            {
                plik << "      " << score << endl;
            }



            plik.close();
        }

        setCursorPosition(9, 13);
        cout << score;

        while (wybierajka3)
        {
            if (GetKeyState(0x1B) & 0x8000)
            {
                ekranPrzegranego = false;
                wybierajka3 = false;
                gameOver = true;
                system("cls");
            }
            else if (GetKeyState(0x0D) & 0x8000)
            {
                ekranPrzegranego = false;
                wybierajka3 = false;
                wMenu = true;
                system("cls");
            }
        }
    }

}

int main() 
{
    WYBOR();

    while (!gameOver)
    {
        GRA();
    }
    return 0;
}
