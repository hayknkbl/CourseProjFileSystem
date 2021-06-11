#include <iostream>
#include "windows.h"
#include "tchar.h"
#include "conio.h"
#include <fstream>
#include <string>
//#include "dirent.h"
//#include "stdafx.h"

using namespace std;

void chartot(char* dir, TCHAR* direct)
{
    for (int i = 0; i < 255; i++)
    {
        direct[i] = dir[i];
    }
    
}

void ttochar(char* dir, TCHAR* direct)
{
    for (int i = 0; i < 255; i++)
    {
        dir[i] = direct[i];
    }
    /*int i = 0;
    while (direct[i] != NULL)
    {
        dir[i] = direct[i];
        i++;
    }*/
}

void cdback(char* dir, TCHAR* direct)
{
    int i = 254;
    while (i>=0)
    {
        if (dir[i] == '\\' )
        {
            dir[i] = '\0';
            //dir[i-1] = ' ';
            break;
        }
        dir[i] = '\0';
        --i;
    }
    chartot(dir, direct);
    
    _tchdir(direct);

}

void adder(char* dir, TCHAR* direct, char* p )
{
    int i = 254;
    if (p[0] == '\0')
    {
        p[0] = '\\';
        p[1] = '*';
    }
    while (dir[i] == '\0')
    {
        i--;
    }
    int z = 0;
    i++;
    while (p[z] != '\0')
    {
        dir[i] = p[z];
        i++;
        z++;
    }
    chartot(dir, direct);
}

int filelist(char* dir, TCHAR* direct)
{
    int max = 0;
    char p[2];
    p[0] = '\\';// empty
    int i = 254;
    p[1] = '*';
    while (dir[i] == '\0')
    {
        i--;
    }
    int z = 0;
    i++;
    while (z < 2)
    {
        dir[i] = p[z];
        i++;
        z++;
    }
    chartot(dir, direct);
    WIN32_FIND_DATA FFD;
    HANDLE hfind;
    char file[255];
    chartot(dir, direct);
    hfind = FindFirstFile(direct, &FFD);
    ttochar(file, FFD.cFileName);
    cout << file << endl;
    ++max;
    while (FindNextFile(hfind, &FFD))
    {
        ttochar(file, FFD.cFileName);
        cout << file << endl;
        ++max;
    }
    FindClose(hfind);
    /*
    * maqrum a hetevic avelacrac ankaputyun@ (*p-n), vor normal ashxati
    */

    i = 254;
    while (i >= 0)
    {
        if (dir[i] == '\\')
        {
            dir[i] = '\0';
            //dir[i-1] = ' ';
            break;
        }
        dir[i] = '\0';
        --i;
    }
    //cout << max << endl;
    //system("pause");
    system("CLS");
    max++;
    return max;
}

void flistdraw(char* dir, TCHAR* direct, int k, char* chsdir, TCHAR* choosedir)
{

    system("CLS");
    cout << dir << endl << endl;
    char p[3] = { '\0' }; // empty
    adder(dir, direct, p);
    WIN32_FIND_DATA FFD;
    HANDLE hfind;
    char file[255];
    
    hfind = FindFirstFile(direct, &FFD);
    /*ttochar(file, FFD.cFileName);
    if (k == 1)
    {
        cout << "-->   " << file << endl;
        choosedir = FFD.cFileName;
        ttochar(chsdir, choosedir);
    }
    else
    {
        cout << "      " << file << endl;
    }
    --k;
     */   
    while (FindNextFile(hfind, &FFD))
    {
        ttochar(file, FFD.cFileName);
        if (k == 1)
        {
            cout << "-->   " << file << endl;
            choosedir = FFD.cFileName;
            ttochar(chsdir, choosedir);
        }
        else
        {
            cout << "      " << file << endl;
        }
        --k;
        
    }
    //FindClose(hfind);
    cout << endl << endl;
    if (k == 1)
    {
        cout << "-->   " << "Add new directory" << endl;
    }
    else
    {
        cout << "      " << "Add new directory" << endl;
    }
    --k;
    if (k == 1)
    {
        cout << "-->   " << "Add new file" << endl;
    }
    else
    {
        cout << "      " << "Add new file" << endl;
    }
    --k;
    int i = 254;
    while (i >= 0)
    {
        if (dir[i] == '\\')
        {
            dir[i] = '\0';
            //dir[i-1] = ' ';
            break;
        }
        dir[i] = '\0';
        --i;
    }
}

int getarrow()
{
    int c;
    c = _getch();
    if ((c == 0) || (c == 224))
    {
        c = _getch();
        if (c == 72)
        {
            return -1;//up
        }
        else if (c == 80)
        {
            return 1;//down
        }
        else if (c == 77)
        {
            return 6;//enter
        }
        else if (c == 75)
        {
            return 4;//back
        }
        else if (c == 83)
        {
            return 9;//del
        }
        else
        {
            c = getarrow();
            return c;
        }
    } //arrow keys
    else if (c == 13)
    {
        return 6;//enter
    }
    else if (c == 27)
    {
        return 7;//esc
    }
    else if (c == 8)
    {
        return 4;//bsck
    }

}

int change(int k, int max, int c)
{
    k += c;
    if (k == 0)
    {
        k = max;
    }
    if (k == max + 1)
    {
        k = 1;
    }
    return k;
}

int exitprog(int a)
{
    int c;
    system("CLS");
    if (a == 0)
    {
        cout << "Are you sure you want to go to the menu?" << endl;
    }
    if (a == 1)
    {
        cout << "Are you sure that you want to exit programm?" << endl;

    }
    cout << "Yes: press Enter" << endl << "No: press ESC" << endl;
    c = getarrow();
    if (c == 6)
    {

        return 0;
    }
    else if (c == 7)
    {
        return 1;
    }
    else
    {
        c = exitprog(0);
        return c;
    }
}

void changedirect(char* chsdir)
{
    char abc[255] = {};
    int i = 0;
    while (chsdir[i] != 0)
    {
        abc[i] = chsdir[i];
        chsdir[i] = 0;
        i++;
    }
    chsdir[0] = '\\';
    while (i >= 0)
    {
        chsdir[i+1] = abc[i];
        i--;
    }
}

void choosecolor(int* t, int* bg)
{
    system("CLS");
    int final;
    *t = 15;
    
    int i = 0;
    int arrow;
    while (i != 100)
    {
        cout << "Choose background colour" << endl << endl;
        for (int j = 0; j < 16; ++j)
        {
            final = (16 * j) + ((*t+j)%2);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), final);
            if (i == j)
            {
                cout << "-->  ";
            }
            else
            {
                cout << "     ";
            };
            cout << "this color" << endl;
        }
        arrow = getarrow();
        system("color 0F");
        system("CLS");
        if (arrow == 6)
        {
            *bg = i;
            i = 100;
        }
        else
        {
            if (arrow <= 1)
            {
                i += arrow;
                if (i == -1)
                {
                    i = 15;
                }
                i = i % 16;
            }
        }
        
    }
    system("CLS");
    i = *bg+1;
    arrow;
    while (i != 100)
    {
        cout << "Choose text colour" << endl << endl;
        for (int j = 0; j < 16; ++j)
        {
            if (j == *bg)   continue;
            final = (16 * (*bg)) + j;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), final);
            if (i == j)
            {
                cout << "-->  ";
            }
            else
            {
                cout << "     ";
            };
            cout << "this color" << endl;
        }
        arrow = getarrow();
        system("color 0F");
        system("CLS");
        if (arrow == 6)
        {
            *t = i;
            i = 100;
        }
        else
        {
            if (arrow <= 1)
            {
                i += arrow;
                if (i == -1)
                {
                    i = 15;
                }
                i = i % 16;
            }
            
        }
        if (i == *bg)
        {
            i += arrow;
            if (i == -1)
            {
                i = 15;
            }
            i = i % 16;
        }

    }
    if (*t == *bg)
    {
        system("color 0F");
        cout << "Bad choise, try again" << endl << "Try again" <<endl;
        cin.ignore();
        choosecolor(t, bg);
    }
}
  
void setcolor()
{
    int text, bg;
    int final;
    choosecolor(&text, &bg);
    final = (16 * bg) + text;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), final);
    system("CLS");
    return;
}

int fileread(char* path)
{
    system("CLS");
    fstream fIn;
    fIn.open(path, ios::in);

    if (fIn.is_open())
    {
        string s;
        while (getline(fIn, s))
        {
            cout << s << endl;
            // Tokenize s here into columns (probably on spaces)
        }
        fIn.close();
        cout << endl << endl << "Press any key to close file";
        cin.ignore();
        return 1;
    }
    else
    {
        //cout << "Error opening file " << errno << endl;
        return 0;
    }
}

void createfile()
{
    system("CLS");
    cout << "Insetr File Name" << endl << endl;
    char filename[255];
    cin.getline(filename, 255);
    ofstream MyFile(filename);
    while (true)
    {
        char c = _getch();
        if (c == 27)
        {
            break;
        }
        cout << c;
        cin.putback(c);
        char line[255];
        cin.getline(line, 255);
        MyFile << line << endl;
    }
    MyFile.close();
    cout << "File is created press any key" << endl;
    cin.ignore();
}

void createdir()
{
    system("CLS");
    char name[255];
    TCHAR namet[255];
    cout << "Insert directory name" << endl << endl;
    cin.getline(name, 255);
    chartot(name, namet);
    if (_tmkdir(namet) != 0)
    {
        cout << endl << "Something went wrong. Try oher name " << endl << endl;
    }    
    cin.ignore();
}

void deletedir(TCHAR* namet)
{
    char name[255];
    ttochar(name, namet);
    //ttochar(dir, FFD.cFileName);
    //cout << dir << endl;
    ///
        /*    
        char cdir[255] = { '\\*' };
        TCHAR cdirect[255];
        GetCurrentDirectory(sizeof(cdirect), cdirect);
        ttochar(cdir, cdirect);
        cout << cdir << endl;
        system("pause");
        */
    ///
    int a = RemoveDirectory(namet);
    int b = remove(name);
    if ((not(a)) && (b != 0))
    {
        int k = _tchdir(namet);
        if (k != 0)
        {
            cout << "                       " << name << "  in not deleted" << endl;
            cin.ignore();
            //cout << "Something went wrong samurai" << endl;
            
        }
        else
        {
            char dir[255] = { '\\*' };
            TCHAR direct[255];
            
            chartot(dir, direct);
            WIN32_FIND_DATA FFD;
            HANDLE hfind;            
            hfind = FindFirstFile(direct, &FFD);
            FindNextFile(hfind, &FFD);
            while (FindNextFile(hfind, &FFD))
            {
                //ttochar(dir, FFD.cFileName);
                //cout << dir << endl;
                //GetCurrentDirectory(sizeof(direct), direct);
                //ttochar(dir, direct);
                //cout << dir << endl;
                deletedir(FFD.cFileName);
            }
            FindClose(hfind);
            GetCurrentDirectory(sizeof(direct), direct);
            ttochar(dir, direct);
            cdback(dir, direct);
            deletedir(namet);            
        }       
    }
    else
    {
        cout << "                       " << name << "  succesfullu deleted" << endl;
        //cin.ignore();
    }
}

void surfing(void)
{
    TCHAR direct[255];
    char dir[255] = { '\0' };
    WIN32_FIND_DATA FFD;
    char file[255];
    HANDLE hfind;
    int k = 1;
    TCHAR choosedir[255];
    char chsdir[255];
    int max;


    //GetCurrentDirectory(sizeof(direct), direct);
    //ttochar(dir, direct);
    system("CLS");
    cout << "Enter your disc name (example D, C or any other thing)" << endl;
    cin >> dir[0];
    system("CLS");
    dir[1] = ':';
    dir[2] = '\\';

    chartot(dir, direct);
    _tchdir(direct);
    max = filelist(dir, direct);
    //cout << max << endl;
    //system("pause");
    flistdraw(dir, direct, k, chsdir, choosedir);
    while (true)
    {
        int c;
        c = getarrow();
        if (c == 1 || c == -1)
        {
            k = change(k, max, c);
            flistdraw(dir, direct, k, chsdir, choosedir);
        }
        if (c == 7)//ESC exit
        {
            c = exitprog(0);
            if (c == 0)
            {
                return;
            }
            else
            {
                flistdraw(dir, direct, k, chsdir, choosedir);
            }
        }
        if (c == 4) //back
        {
            cdback(dir, direct);
            k = 1;
            max = filelist(dir, direct);
            flistdraw(dir, direct, k, chsdir, choosedir);
        }
        if (c == 6) //Enter
        {
            
            
            changedirect(chsdir);
            chartot(chsdir, choosedir);
            adder(dir, direct, chsdir);
            chartot(dir, direct);
            if (k == (max - 1))
            {
                createdir();
                cdback(dir, direct);
                max = filelist(dir, direct);
                flistdraw(dir, direct, k, chsdir, choosedir);
            }
            else if (k == max)
            {
                createfile();
                cdback(dir, direct);
                max = filelist(dir, direct);
                flistdraw(dir, direct, k, chsdir, choosedir); 
            }
            else if(fileread(dir))
            {
                cdback(dir, direct);
                flistdraw(dir, direct, k, chsdir, choosedir);
            }
            else
            {
                _tchdir(direct);
                k = 1;
                max = filelist(dir, direct);
                flistdraw(dir, direct, k, chsdir, choosedir);
            }
                         
        }
        if (c == 9)//delete
        {
            if ((chsdir[0] == '.') && (chsdir[1] == '.'))
            {
                system("CLS");
                cout << "I'S A VERY BAD IDEA" << endl;
                continue;
            }
            else if (k == max)
            {
                cout << "You aren't the sharpest knife in the drawer, are you" << endl;
                continue;
            }
            cout << endl << endl << endl;
            chartot(chsdir, choosedir);
            //_tchdir(choosedir);

            deletedir(choosedir);
            flistdraw(dir, direct, k, chsdir, choosedir);
            max--;
        }
    }


}

void controls()
{
    system("CLS");
    cout << "I don't know why are you here, but ok." << endl << "Lets see how you can interact with programm" << endl << endl;
    cout << "Up/Down keys           --> choose option/file" << endl;
    cout << "Right key/Enter        --> enter option/file" << endl;
    cout << "Left key/Backspace     --> it can be strange (no), but going back" << endl;
    cout << "Delete                 --> delet that folder with everyhing in it" << endl;
    cout << "Esc                    --> exit" << endl << endl;
    cout << "Press any key to go back to menu" << endl;
    cin.ignore();
}

void menu(void)
{   
    int i = 0;
    int arrow;
    while (i != 100)
    {
        cout << "Welcome to file browser by Hk" << endl<<endl;
        for (int j = 0; j < 5; ++j)
        {
            
            if (i == j)
            {
                cout << "-->  ";
            }
            else
            {
                cout << "     ";
            };
            switch (j) {
            case 0:
                cout << "Start Browsing" << endl;
                break;
            case 1:
                cout << "Change Console Color" << endl;
                break;
            case 2:
                cout << "Controls" << endl;
                break;
            case 3:
                cout << "Updates" << endl;
                break;
            case 4:
                cout << "Exit" << endl;
                break;
            }
        }
        arrow = getarrow();
        if (arrow == 6)
        {         
            switch (i) {
            case 0:
                surfing();
                break;
            case 1:
                setcolor();
                break;
            case 2:
                controls();
                break;
            case 3:
                system("CLS");
                cout << "As once said a very bald man  -  KTTC";
                cin.ignore();
                break;
            case 4:
                if (exitprog(1) == 0)
                {
                    return;
                }
                break;
            }
        }
        else
        {
            if (arrow <= 1)
            {
                i += arrow;
                if (i == -1)
                {
                    i = 4;
                }
                i = i % 5;
            }
        }
        system("CLS");

    }
}

int main()
{
    menu();
    
    return 0;
}