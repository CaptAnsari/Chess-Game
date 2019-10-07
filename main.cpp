#include <iostream>
#include<windows.h>
#include<conio.h>
#include<math.h>

using namespace std;
void gotoRowCol(int rpos, int cpos);
void L2R(int rs, int cs, int ce);
void T2B(int rs,int cs,int re);
void getinput(int turn);
void printboard(int rs, int cs, int bx, int dim);
bool isinvalid(int ri, int ci,int turn,char board[][8]);
void getindex(int& Sri, int& Sci, int rs, int cs, int bx);
void getRowColbyLeftClick(int &rpos,int &cpos);
void Upboard(char board[][8],int bs, int dim, int rs, int cs);
void getDesindex(int& Dri, int& Dci, int rs, int cs, int bx);
bool isdesinvalid(int Dri,int Dci,int Sri, int Sci,int turn,char board[][8]);
bool forpathH(int Sci,int Dci,int Sri,char board[][8]);
bool forpathD(int Sri,int Dri,int Sci, int Dci, char board[][8]);
bool forpathv(int Sri,int Dri,int Sci,char board[][8]);
void makemove(int Sri,int Sci, int Dri, int Dci, char board[][8]);
int main()
{
    const int dim=8, bx=10, rs=10, cs=10;
    int Sri,Sci,Dri,Dci, turn=0;
    char board[8][8]={'R','N','B','Q','K','B','N','R',
                    'P','P','P','P','P','P','P','P',
                    '.','.','.','.','.','.','.','.',
                    '.','.','.','.','.','.','.','.',
                    '.','.','.','.','.','.','.','.',
                    '.','.','.','.','.','.','.','.',
                    'p','p','p','p','p','p','p','p',
                    'r','n','b','q','k','b','n','r'};

    printboard(rs,cs,bx,dim);
    do
    {
        Upboard(board,bx,dim,rs,cs);
        do
        {
            do
            {
                getinput(turn);
                getindex(Sri,Sci,rs,cs,bx);

            }while(!isinvalid(Sri,Sci,turn,board));
                gotoRowCol(0,10);
        cout<<"Player "<<turn<<"turn : ";
        cout<<"Click on the destin index";
            getDesindex(Dri,Dci,rs,cs,bx);
        }while(!isdesinvalid(Dri,Dci,Sri,Sci,turn,board));
        makemove(Sri,Sci,Dri,Dci,board);
        turn++;
        if (turn==2) turn=0;
    }while(1);


    getch();



}
void makemove(int Sri,int Sci, int Dri, int Dci, char board[][8])
{
    if(board[Dri][Dci]=='.')
    {
        swap(board[Sri][Sci],board[Dri][Dci]);
    }
    else
    {
        board[Dri][Dci]=board[Sri][Sci];
        board[Sri][Sci]='.';
    }
}
bool isdesinvalid(int Dri,int Dci,int Sri, int Sci,int turn,char board[][8])
{
    char pc=board[Dri][Dci];
    if( ((turn==0) && (pc>'A') && (pc<'Z')))
        return false;
    else
        pc=board[Sri][Sci];
        switch (pc)
        {
        case 'r': case 'R':
            if(Sri==Dri || Sci==Dci)
            {
                if(forpathH(Sci,Dci,Sri,board) || forpathv(Sri,Dri,Sci,board))
                    return true;
                else return false;
            }
            else return false;
        case 'B': case 'b':
            if(abs(Sci-Dci)==abs(Sri-Dri))
            {
                if(forpathD(Sri,Dri,Sci,Dci,board)) return true;
                else return false;
            }
            else return false;
        case 'q': case 'Q':
            if(abs(Sci-Dci)==abs(Sri-Dri))
            {
                if(forpathD(Sri,Dri,Sci,Dci,board)) return true;
                else return false;
            }
            if(Sri==Dri || Sci==Dci)
            {
                if(forpathH(Sci,Dci,Sri,board) || forpathv(Sri,Dri,Sci,board))
                return true;
                else return false;
            }
            else return false;
        case 'K': case 'k':
            if((abs(Sci-Dci)==1 && abs(Sri-Dri)==1) || (abs(Sci-Dci)==1 || abs(Sri-Dri)==1))
                return true;
            else return false;
        case 'p': case 'P':
            if(((pc=='P' && Sri==1) && Sci==Dci && (Dri-Sri==1 || Dri-Sri==2)) || ((pc=='p' && Sri==6) && Sci==Dci && (Sri-Dri==1 || Sri-Dri==2)))
                return true;
            if((pc=='P' && Sri!=1) && (Dri-Sri==1) && Sci==Dci && board[Dri][Dci]=='.')
                return true;
            if((pc=='p' && Sri!=6) && (Sri-Dri==1) && Sci==Dci &&  board[Dri][Dci]=='.')
                return true;

            if((pc=='P'  && (Dri-Sri==1) && abs(Dci-Sci)==1 && board[Dri][Dci]!='.'))
                return true;
            if((pc=='p' && (Sri-Dri==1) && abs(Dci-Sci)==1 && board[Dri][Dci]!='.'))
                return true;







            else return false;
        case 'N': case 'n':
            if((abs(Dri-Sri)==2 && abs(Dci-Sci)==1) || (abs(Sri-Dri)==1 && abs(Sci-Dci)==2))
                return true;
            else return false;
        }
}

bool forpathH(int Sci,int Dci,int Sri,char board[][8])
{
    int start, End;
    if(Sci<Dci)
    {
        for(int i=Sci+1;i<Dci;i++)
        {
            if(board[Sri][i]=='.') continue;
            else return false;
        }
    }
    else
    {
        for(int i=Dci+1;i<Sci;i++)
        {
            if(board[Sri][i]=='.') continue;
            else return false;
        }
    }

    return true;
}
bool forpathv(int Sri,int Dri,int Sci,char board[][8])
{
    int start, End;
    if(Sri<Dri)
    {
        for(int i=Sri+1;i<Dri;i++)
            {
                if(board[i][Sci]=='.') continue;
                else return false;
            }
    }
    else
    {
        for(int i=Dri+1;i<Sri;i--)
            {
                if(board[i][Sci]=='.') continue;
                else return false;
            }
        }
    return true;
}
bool forpathD(int Sri,int Dri,int Sci, int Dci, char board[][8])
{
    if(Sri<Dri && Sci<Dci)
    {
        for(int i=1; i<Dri-Sri;i++)
        {
            if(board[Sri+i][Sci+i]=='.') continue;
            else return false;
        }
    }
    if(Sri>Dri && Sci>Dci)
    {
        for(int i=1; i<Sri-Dri;i++)
        {
            if(board[Dri+i][Dci+i]=='.') continue;
            else return false;
        }
    }
    if(Sri<Dri && Sci>Dci)
    {
        for(int i=1; i<Dri-Sri;i++)
        {
            if(board[Sri+i][Sci-i]=='.') continue;
            else return false;
        }
    }
    if(Sri>Dri && Sci<Dci)
    {
        for(int i=1; i<Sri-Dri;i++)
        {
            if(board[Sri-i][Sci+i]=='.') continue;
            else return false;
        }
    }
    return true;
}

void getindex(int& Sri, int& Sci, int rs, int cs, int bx)
{
    getRowColbyLeftClick(Sri,Sci);
    Sri=(Sri-rs)/bx;
    Sci=(Sci-cs)/bx;
}
void getDesindex(int& Dri, int& Dci, int rs, int cs, int bx)
{
    getRowColbyLeftClick(Dri,Dci);
    Dri=(Dri-rs)/bx;
    Dci=(Dci-cs)/bx;
}
void printboard(int rs, int cs, int bx, int dim)
{
     for(int i=0;i<=dim;i++)
    {
        L2R(rs+bx*i,cs,rs+dim*bx);
        T2B(rs,cs+bx*i,cs+dim*bx);
    }
}
void L2R(int rs, int cs, int ce)
{
    for(cs; cs<ce; cs++)
    {
        gotoRowCol(rs, cs);
        char sym=-37;
        cout<<sym;

    }
}
void T2B(int rs,int cs,int re)
{
    for(rs; rs<re; rs++)
    {
        gotoRowCol(rs,cs);
        char sym=-37;
        cout<<sym;
    }
}
void Upboard(char board[][8],int bx, int dim, int rs, int cs)
{
    for(int i=0; i<dim;i++)
    {
        for(int j=0; j<dim;j++)
        {
            gotoRowCol(rs+bx/2+i*bx,cs+bx/2+j*bx);
            cout<<board[i][j];
        }
        cout<<endl;
    }
}
void getinput(int turn)
{
    gotoRowCol(0,10);
    cout<<"Player "<<turn<<"turn : ";
    cout<<"Click on the source index";
}
bool isinvalid(int ri, int ci,int turn,char board[][8])
{
    char pc=board[ri][ci];
    if( ((turn==0) && (pc>'A') && (pc<'Z')) ||((turn==1) && (pc>'a') && (pc<'z')))
        return true;
    return false;
}
void gotoRowCol(int rpos, int cpos)
{
 int xpos=cpos, ypos = rpos;
 COORD scrn;

 HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

 scrn.X = xpos; scrn.Y = ypos;

 SetConsoleCursorPosition(hOuput,scrn);
}
void getRowColbyLeftClick(int &rpos,int &cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if(InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    }
    while(true);
}
