//
//  main.cpp
//  playingCard
//
//  Created by Tenzin Tashi on 6/27/19.
//  Copyright © 2019 Tenzin Tashi. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstdlib> //rand & srand function
#include <ctime> //time function
#include <iomanip> //setw funcion
#include <cctype>
#include <cwchar> // for unicode character
#include <cmath>
using namespace std;

//function prototype
string gatherPlayerCard(string *);
string gatherHouseCard(string *);
string * distributeCard(string [], string );
string * arrayFinalFunction(string * );
int returnIntValue( string []);
void sortIntValue(int []);
bool winGame(int [], int []);




// class to get a rank of a playing card
class Rank{
private:
    string RankArray[13] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
public:
    string getRank(int);
};
string Rank::getRank(int x){
    return RankArray[x];
}

// class to get a suit of a playing card
class Suit{
private:
    //uni-code for club, diamond, heart, and spade respectively
    string SuitArray[4] = {"\u2663","\u2662","\u2661","\u2660"};
public:
    string getSuit(int);
};
string Suit::getSuit(int x){
    return SuitArray[x];
}


// custom data type of both rank and suit
struct Card {
    string Xrank[6];
    string Xsuit[6];
};


// class to generate a random card
class GenCard{
private:
    Rank rank;
    Suit suit;
    Card card;
    string cardRS[6];
    int x,y;
public:
    GenCard(); // default constructor
    string * printCard();
};
GenCard::GenCard(){
    srand( (unsigned) time( NULL ) );
    for(int i = 0; i<6;i++){
        x = rand();
        y = rand();
        card.Xrank[i] = rank.getRank(x % 13);
        card.Xsuit[i] = suit.getSuit(y % 4);
        cardRS[i] = card.Xrank[i] + card.Xsuit[i];
    }
}
string * GenCard::printCard(){
    return cardRS;
}
class MenuCollection{
public:
    void MainMenu();
    void PlayMenu();
    void CreditMenu();
    void BuyCoinMenu();
    void GameMenu();
    void PlayGame();
    void EndGame();
};
struct MenuOpt {
    string Menu1;
    string Menu2;
    string Menu3;
    string Menu4;
    string Menu5;
};


// Global variable
string * Player;
string playerName;
bool fold = false;
MenuOpt displayMain;
int coin =0;
#define SIZE 15
int space = 24;
int bet =0;


//main function
int main(int argc, const char * argv[]) {
    int option;
    string ArrayUp[SIZE];
    string ArrayHp[SIZE];
    string hP(gatherHouseCard(Player)),uP(gatherPlayerCard(Player));
    
    //cout << "Player Card: "<<endl;
    //cout <<uP<<endl;
    
    //cout << "House Card: "<<endl;
    //cout <<hP<<endl;
    
    string * uPprt = distributeCard(ArrayUp, uP);
    string * hPprt = distributeCard(ArrayHp, hP);
    
    int arrayFinal[3];
    int arrayFinal2[3];
    
    for (int i = 0 ; i< 3; i++){
        arrayFinal[i] = returnIntValue(uPprt+i);
    }
    for (int i = 0 ; i< 3; i++){
        arrayFinal2[i] = returnIntValue(hPprt+i);
    }
    
    sortIntValue(arrayFinal);
    sortIntValue(arrayFinal2);

    MenuCollection mc;
goBackToMain:
    displayMain.Menu1="Play";
    displayMain.Menu2="Credit";
    displayMain.Menu3="Exit";
    mc.MainMenu();
    cin >> option;
    switch (option) {
        case 1:
        buyCoin:
            system("CLS");
            displayMain.Menu1="Start";
            displayMain.Menu2="Buy Coin";
            displayMain.Menu3="Back";
            mc.PlayMenu();
            cin >> option;
            if (option == 1 && coin <=0){
                cout << "You need to Buy Coin before starting the Game!!!"<<endl;
                system("PAUSE");
                goto buyCoin;
            }else if(option == 2){
            buyAgain:
                system("CLS");
                
                displayMain.Menu1="100 \t\t 100 ";
                displayMain.Menu2="500 \t\t 500 ";
                displayMain.Menu3="1000\t\t 1000";
                mc.BuyCoinMenu();
                cin >> option;
                if (option == 0 ){
                    goto buyCoin;
                }else if ( option  == 100 || option == 500 || option == 1000){
                    coin += option;
                }
                goto buyAgain;
            }else if (option == 3){
                goto goBackToMain;
            }else{
                // main code here
                system("CLS");
                displayMain.Menu1="Enter Your Name:";
                displayMain.Menu2="p.s";
                displayMain.Menu3="Each game cost $10";
                mc.GameMenu();
                cin>>playerName;
                coin -= 10;
                bet = 10;
                do{
                system("CLS");
                displayMain.Menu1= playerName +" you got the following card:";
                displayMain.Menu2="What would you like to do?";
                displayMain.Menu3="1) Bet $10   2) Show   3) Fold";
                displayMain.Menu4 = uP;
                
                if (coin <= 0){
                    mc.PlayGame();
                    cout << "You don't have enough money to bet!!! "<<endl;
                    option = 2;
                    system("PAUSE");
                }else{
                    mc.PlayGame();
                    cin >> option;
                }
                if (option == 1){
                    bet += 10;
                    coin -=10;
                }else if( option == 2){
                    system("CLS");
                    displayMain.Menu1= playerName +" you got the following card:";
                    displayMain.Menu4 = uP;
                    displayMain.Menu2 = "House Card is: ";
                    displayMain.Menu3 = hP;
    
   // cout<<displayMain.Menu1<<endl<<displayMain.Menu4<<endl<<displayMain.Menu2<<endl<<displayMain.Menu3<<endl;
                    mc.EndGame();
                    
 
                }else if (option == 3){
                    fold = true;
                    displayMain.Menu2 = "You Folded!!!";

                }
                    
                }while( option == 1 );
                
            }
            break;
        case 2:
        tryAgain:
            system("CLS");
            displayMain.Menu1="Presented By: Tenzin Tashi ";
            displayMain.Menu2="Professor: Doyel Pal";
            displayMain.Menu3="Subject: MAC 125";
            mc.CreditMenu();
            cin >> option;
            if (option == 0){
                goto goBackToMain;
            }else{
                cin.ignore();
                goto tryAgain;
            }
            break;
        case 3:
            system("CLS");
            cout << "Thank you for using our service!!!"<<endl;
            exit(0);
            break;
        default:
            cin.ignore();
            goto goBackToMain;
    }

    if(fold) {
        cout << "you lose $"<<bet<<endl;
    }else if (winGame(arrayFinal, arrayFinal2)){
        cout << "You won $"<<bet<<endl;
        cout << bet;
    }else {
        cout << "You lose $"<<bet<<endl;
    }
    
    return 0;
}
void MenuCollection::EndGame(){
    if (space != 24  && coin >=1000){
        space = 21;
    }else if(coin > 0 && coin < 1000){
        space = 22;
    }
    int unsigned spaceN =55 - displayMain.Menu1.length();
    int unsigned spaceM =61 - displayMain.Menu3.length();
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"*****                   Your Have "<<coin<<" Coin"<<right<<setw((space))<<"*****"<<endl;
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****    "<<displayMain.Menu1<<setw(spaceN)<<"*****"<<endl;
    cout<<setw(5) <<"*****    "<<displayMain.Menu4<<setw(48)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****    "<<displayMain.Menu2<<right<<setw(40)<<"*****"<<endl;
    cout<<setw(5) <<"*****    "<<displayMain.Menu3<<right<<setw(spaceM)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"*****    >>>> Thank You For Playing With Us" <<endl;;
}
void MenuCollection::PlayGame(){
    if (space != 24  && coin >=1000){
        space = 21;
    }else if(coin > 0 && coin < 1000){
        space = 22;
    }
    int unsigned spaceN =55 - displayMain.Menu1.length();
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"*****                   Your Have "<<coin<<" Coin"<<right<<setw((space))<<"*****"<<endl;
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****    "<<displayMain.Menu1<<setw(spaceN)<<"*****"<<endl;
    cout<<setw(5) <<"*****    "<<displayMain.Menu4<<setw(48)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****    "<<displayMain.Menu2<<right<<setw(29)<<"*****"<<endl;
    cout<<setw(5) <<"*****    "<<displayMain.Menu3<<right<<setw(25)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"*****    >>>> ";
}
void MenuCollection::GameMenu(){
    if (space != 24  && coin >=1000){
        space = 21;
    }else if(coin > 0 && coin < 1000){
        space = 22;
    }
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"*****                   Your Have "<<coin<<" Coin"<<right<<setw((space))<<"*****"<<endl;
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****    "<<displayMain.Menu1<<setw(39)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****    "<<displayMain.Menu2<<right<<setw(52)<<"*****"<<endl;
    cout<<setw(5) <<"*****    "<<displayMain.Menu3<<right<<setw(37)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"*****    >>>> ";
}
void MenuCollection::MainMenu(){
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"*****              Welcome to online Sin City              *****"<<endl;
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****   1) "<<displayMain.Menu1<<right<<setw(49)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****   2) "<<displayMain.Menu2<<right<<setw(47)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****   3) "<<displayMain.Menu3<<right<<setw(49)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****   Select the Option(1/2/3):                          *****"<<endl;
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"        >>>> ";
}
void MenuCollection::PlayMenu(){
    if (space != 24  && coin >=1000){
        space = 21;
    }else if(coin > 0 && coin < 1000){
        space = 22;
    }
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"*****                   Your Have "<<coin<<" Coin"<<right<<setw((space))<<"*****"<<endl;
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****   1) "<<displayMain.Menu1<<right<<setw(48)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****   2) "<<displayMain.Menu2<<right<<setw(45)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****   3) "<<displayMain.Menu3<<right<<setw(49)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****   Select the Option(1/2/3):                          *****"<<endl;
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"        >>>> ";
}
void MenuCollection::CreditMenu(){
    
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"*****                App Development Project               *****"<<endl;
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****    "<<displayMain.Menu1<<right<<setw(28)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                                      2*****"<<endl;
    cout<<setw(5) <<"*****    "<<displayMain.Menu2<<right<<setw(35)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****    "<<displayMain.Menu3<<right<<setw(39)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****                                    Copyright \u00A9 2019  *****"<<endl;
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"        Press 0 to go back"<<endl;
    cout<<setw(5) <<"        >>>> ";
}

void MenuCollection::BuyCoinMenu(){
    if (space != 24  && coin >=1000){
        space = 21;
    }else if(coin > 0 && coin < 1000){
        space = 22;
    }else if (coin >= 1000){
        space = 21;
    }
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"*****                   Your Have "<<coin<<" Coin"<<right<<setw((space))<<"*****"<<endl;
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"*****     Coin\t\tTotal                                  *****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****    "<<displayMain.Menu1<<right<<setw(39)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****    "<<displayMain.Menu2<<right<<setw(39)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                                      *****"<<endl;
    cout<<setw(5) <<"*****    "<<displayMain.Menu3<<right<<setw(39)<<"*****"<<endl;
    cout<<setw(5) <<"*****                                    Copyright \u00A9 2019  *****"<<endl;
    cout<<setw(5) <<"****************************************************************"<<endl;
    cout<<setw(5) <<"        Press 0 to go back"<<endl;
    cout<<setw(5) <<"        >>>> ";
}

bool winGame(int a[], int b[]){
    //trio
    if (a[0] == a[1] && a[1] == a[2] && b[0] != b[1] && b[1] != b[2]){
        cout << "Trio 1"<<endl;
        return true;
    }else if(a[0] == a[1] && a[1] == a[2]  && b[1] == b[2] && b[0] == b[1]){
        if ( a[0] > b[0]){
            cout << "Trio 2"<<endl;
            return true;
        }
    }else if(a[0] != a[1] && a[1] != a[2]  && b[1] == b[2] && b[0] == b[1]){
        cout << "Trio 3"<<endl;
        return false;
    }
    //stright
    else if ((a[0]+1) == a[1] && (a[1]+1) == a[2] && (b[0]+1) != b[1] && (b[1]+1) != b[2] ){
        cout << "Str 1"<<endl;
        return true;
    }else if((a[0]+1) == a[1] && (a[1]+1) == a[2] && (b[0]+1) == b[1] && (b[1]+1) == b[2]){
        
        if (a[2]>b[2]){
            cout << "Str 2"<<endl;
            return true;
        }
    }else if((a[0]+1) != a[1] && (a[1]+1) != a[2] && (b[0]+1) == b[1] && (b[1]+1) == b[2]){
        cout << "Str 3"<<endl;
        return false;
    }
    //pair
   else if( ((a[0] == a[1]) || (a[1] == a[2])) && ((b[0] != b[1]) && (b[1] != b[2]))  ){
       cout << "Pair 1"<<endl;
        return true;
   }else if ( ((a[0] == a[1]) || (a[1] == a[2])) && ((b[0] == b[1]) || (b[1] == b[2]) )  ){
        if (a[1]>b[1]){
            cout << "Pair 2"<<endl;
            return true;
        }
   }else if ( ((a[0] != a[1]) && (a[1] != a[2])) && ((b[0] == b[1]) || (b[1] == b[2]) )  ){
       cout << "Pair 3"<<endl;
        return false;
   }
    
    //hight card
   else if ( a[2] == b[2]){
        if( a[1] == b[1]){
            if (a[0] > b[0]){
                cout << "HC 1"<<endl;
                return true;
            }
        }else if (a[1] > b[1]){
            cout << "HC 2"<<endl;
            return true;
        }
   }
   else if (a[2] > b[2]){
        cout << "HC 3"<<endl;
        return true;
   }else if (a[2] < b[2]){
       cout << "HC 4"<<endl;
       return false;
   }
    cout << "Final"<<endl;
    return false;
}

//Encoding
int returnIntValue( string a[]){
    int loop = 3;
    for (int Index = 0 ; Index< loop; Index++){
        if(a[Index] == "2"){
            return 0;
        }else if(a[Index] == "3"){
            return 1;
        }else if(a[Index] == "4"){
            return 2;
        }else if(a[Index] == "5"){
            return 3;
        }else if(a[Index] == "6"){
            return 4;
        }else if(a[Index] == "7"){
            return 5;
        }else if(a[Index] == "8"){
            return 6;
        }else if(a[Index] == "9"){
            return 7;
        }else if(a[Index] == "1"){
            return 8;
        }else if(a[Index] == "J"){
            return 9;
        }else if(a[Index] == "Q"){
            return 10;
        }else if(a[Index] == "K"){
            return 11;
        }else if(a[Index] == "A"){
            return 12;
        }else{
            continue;
            loop++;
        }
    }
    exit(0);
}
//sortting
void sortIntValue(int a[]){
    for (int i = 0; i<3; i++){
        int min = a[i];
        for (int j =i+1; j<=2; j++){
            if (min > a[j]){
                int temp = min;
                min = a[j];
                a[j] = temp;
                a[i] = min;
            }
        }
    }
}

string * distributeCard(string ArrayUp[], string uP){
    int j = 0;
    for (int i = 0 ; i< uP.length(); ){
        int next = i +1;
        if( uP[i] == '1' ){
            ArrayUp[j] = uP[i];
            j++;
            ArrayUp[j] = uP[next];
            i +=5;
        }else {
            ArrayUp[j] = uP[i];
            i +=4;
        }
        j++;
    }
    return ArrayUp;
}
string gatherPlayerCard(string * ptr){
    GenCard generateCard;
    string uP("");
    ptr = generateCard.printCard();
    for (int i = 0; i < 3; i++){
        uP += * (ptr+i);
    }
    return uP;
}
string gatherHouseCard(string * ptr){
    GenCard generateCard;
    string hP("");
    ptr = generateCard.printCard();
    for (int i = 3; i < 6; i++){
        hP += * (ptr+i);
    }
    return hP;
}
