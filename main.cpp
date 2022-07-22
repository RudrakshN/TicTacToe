#include<bits/stdc++.h>
#define COMPUTER 1
#define HUMAN 2
#define SIDE 3
#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'
using namespace std;

//showing instructions in the beggiining of the game foe filling the box
void showinstructions(){
    cout<<"\nChoose a cell numbered from 1 to 9 as below and play\n\n";
    cout<<"\t\t\t\t\t\t 1 | 2 | 3 \n";
    cout<<"\t\t\t\t\t\t-----------\n";
    cout<<"\t\t\t\t\t\t 4 | 5 | 6 \n";
    cout<<"\t\t\t\t\t\t------------\n";
    cout<<"\t\t\t\t\t\t 7 | 8 | 9 \n\n";
    
}
//printing the board at each and every step

void showBoard(char board[][SIDE])
{
printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
printf("\t\t\t-----------\n");
printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
printf("\t\t\t-----------\n");
printf("\t\t\t %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}
//initializing the tictactoe with *
void initialize(char board[][SIDE]){
    for(int i=0;i<SIDE;i++){
        for(int j=0;j<SIDE;j++){
            board[i][j]='*';
        }
    }
}

//checking wether a player wins because of row getting filled

bool rowCrossed(char board[][SIDE]){
    for(int i=0;i<SIDE;i++){
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0]!='*'){
            return true;
        }
    }
    return false;
}

// checking wether a player wins because of coloumn getting filled

bool columnCrossed(char board[][SIDE]){
    for(int i=0;i<SIDE;i++){
        if(board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[0][i]!='*'){
            return true;
        }
    }
    return false;
}

// checking wether a player wins because of diagonal gettinmg filled

bool diagonalCrossed(char board[][SIDE]){
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!='*'){
        return true;
    }
    if(board[0][2]==board[1][1] && board[1][1]==board[2][2] && board[2][0]!='*'){
        return true;
    }
    return false;
}

// checking if the game is over or not

bool gameOver(char board[][SIDE]){
    if(rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board)){
        return true;
    }
    return false;
}
//declaring the winner
void declarewinner(int whoseturn){
    if(whoseturn==COMPUTER) cout<<"COMPUTER has won\n";
    else cout<<"HUMAN has won\n";
}
// playing the tic tac toe game

int minmax(char board[][SIDE],int depth,bool isAI){
    int score=0;
    int bestscore=0;
    if(gameOver(board)==true){
        if(isAI==true){
            return -10;
        }
        if(isAI==false){
            return 10;
        }
    }
    else{
        if(depth<9){
            if(isAI==true){
                bestscore=-999;
                for(int i=0;i<SIDE;i++){
                    for(int j=0;j<SIDE;j++){
                        if(board[i][j]=='*'){
                            board[i][j]=COMPUTERMOVE;
                            score=minmax(board,depth+1,false);
                            board[i][j]='*';
                            if(score>bestscore){
                                bestscore=score;
                            }
                        }
                    }
                }
                return bestscore;
            }
            else{
                bestscore=999;
                for(int i=0;i<SIDE;i++){
                    for(int j=0;j<SIDE;j++){
                        if(board[i][j]=='*'){
                            board[i][j]=HUMANMOVE;
                            score=minmax(board,depth+1,true);
                            board[i][j]='*';
                            if(score<bestscore){
                                bestscore=score;
                            }
                        }
                    }
                }
                return bestscore;
            }
        }
        else{
            return 0;
        }
    }
    
}
int bestmove(char board[][SIDE],int moveIndex){
    int x=-1;int y=-1;
    int bestscore=-999;int score=0;
    for(int i=0;i<SIDE;i++){
        for(int j=0;j<SIDE;j++){
            if(board[i][j]=='*'){
                board[i][j]=COMPUTERMOVE;
                score=minmax(board,moveIndex+1,false);
                board[i][j]='*';
                if(score>bestscore){
                    bestscore=score;
                    x=i;
                    y=j;
                }
            }
        }
    }
    return x*3+y;
}
void playtictactoe(int whoseturn){
    char board[SIDE][SIDE];
    int moveIndex=0;int x=0;int y=0;
    initialize(board);
    showinstructions();
    while(gameOver(board)==false && moveIndex!=SIDE*SIDE){
        int n;
        if(whoseturn==COMPUTER){
            n=bestmove(board,moveIndex);
            x=n/SIDE;
            y=n%SIDE;
            board[x][y]=COMPUTERMOVE;
            cout<<"COMPUTER has put a O in cell "<<n+1<<endl<<endl;
            showBoard(board);
            moveIndex++;
            whoseturn=HUMAN;

        }
        else if(whoseturn==HUMAN){
            cout<<"\nYou can insert in the following positions : ";
            for(int i=0;i<SIDE;i++){
                for(int j=0;j<SIDE;j++){
                    if(board[i][j]=='*'){
                        cout<<((3*i)+j)+1<<" ";
                    }
                }
            }
            cout<<"\n\nEnter the position = ";
            cin>>n;
            n--;
            x=n/SIDE;
            y=n%SIDE;
            if(board[x][y]=='*' && n<9 && n>=0){
                board[x][y]=HUMANMOVE;
            cout<<"\nHUMAN has put a X in cell "<<n+1<<endl;
            showBoard(board);
            moveIndex++;
            whoseturn=COMPUTER;
            }
            else if(board[x][y]!='*' && n<9 && n>=0){
                cout<<"Cant select\n";
            }
            else if(n<0 || n>8){
                cout<<"Invalid position\n";
            }
        }

    }
    if(gameOver(board)==false && moveIndex==SIDE*SIDE){
        cout<<"It's a draw\n";
    }
    else{
        if(whoseturn==HUMAN){
            whoseturn=COMPUTER;
        }
        else if(whoseturn==COMPUTER){
            whoseturn=HUMAN;
        }
        declarewinner(whoseturn);
    }
}
int main(){
    cout<<"\n________________________________________________________________________________________________________________________________\n\n";
    cout<<"\t\t\t\t\t\tTIC-TAC-TOE\n";
    cout<<"________________________________________________________________________________________________________________________________\n\n";
    char cont='y';
    do{
        char choice;
        cout<<"Do you want to start first (y/n) : ?";
        cin>>choice;
        if(choice=='n') playtictactoe(COMPUTER);
        else if(choice=='y') playtictactoe(HUMAN);
        else cout<<"Invalid Choice\n";
        cout<<"Do you want to quit ? (y/n)";
        cin>>cont;
    }while(cont=='n');
    return 0;
}
