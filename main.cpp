//Elleson Tran
//Roberts
//Memory with Emojis Project
//Matching Memory Game
//FINAL

#include <iostream>
#include<vector>
#include "m/matrix.h"
#include<curses.h> 

using namespace std;

  //the emojis used
  const string e1 = "🤓";
  const string e2 = "🙈";
  const string e3 = "🍄";
  const string e4 = "🌚";
  const string e5 = "🍣";
  const string e6 = "🏐";
  const string e7 = "🔮";
  const string e8 = "🥪";
  const vector<string> emojis = {e1, e2, e3, e4, e5, e6, e7, e8};

  const string n0 = "0️⃣";
  const string n1 = "1️⃣";
  const string n2 = "2️⃣";
  const string n3 = "3️⃣";
  const vector<string> nums = {n0, n1, n2, n3};

//randomlu generates a board of pairs of emojis
void generateBoard(matrix<string> &hidden){


  bool answer; //if the spot already has an emoji in it, set to true
  int row, col;

  for(int x = 0; x < 2; x++){//puts both pairs of emojis into the matrix
    for(int i = 0; i < emojis.size(); i++){//puts each emoji into a random spot

      do{//does this until it finds an empty spot
        answer = false;
        row = rand()%4;
        col = rand()%4;

        //this loop compares this spot to each emoji
        for(int k = 0; k < emojis.size(); k++){
          if(hidden[row][col] == emojis[k]){//if there is an emoji in the spot
            answer = true;//goes through a do while loop again
          }
        }

      }while(answer == true);//keeps going if there is an emoji in the spot

      //once it finds a spot that doesnt have an emoji, it puts it into the matrix
      
      hidden[row][col] = emojis[i];
      
    }
  }
}

//prints the board with blanks in empty spots and prints emojis in correct spots
void drawBoard(matrix<string> &reveal){
  cout<<endl;
  bool answer; //if there is an emoji in the spot, set to true

  //header
  cout<<"   ";
  for(int x = 0; x < nums.size(); x++){
    cout<<nums[x];
    cout<<"  ";
  }

  //actual board and side bars
  for(int row = 0; row < reveal.numRows(); row++){//goes down each row
    cout<<endl<<nums[row];//row number

    for(int col = 0; col < reveal.numCols(); col++){//goes through each column
      answer = false;

      //checks to see if there is an emoji in the current spot, if so print, if not print a blank
      for(int x = 0; x < emojis.size(); x++){//checks to see if the spot has an emoji
        if(reveal[row][col] == emojis[x]){
          answer = true;
        }
      }
      if(answer == true){//if there is an emoji, it prints it
        cout<<"  ";
        cout<<reveal[row][col];
      }
      if(answer != true){//prints a blank if there was no emoji found
        cout<<"  ";
        cout<<"❓";
      }
    }

    cout<<"  "<<nums[row];//row number
  }
  //bottom
  cout<<endl<<"   ";
  for(int x = 0; x < nums.size(); x++){
    cout<<nums[x];
    cout<<"  ";
  }
}

//collects VALID coordinates
int collectGuess(int &row1, int &col1, int &row2, int &col2, matrix<string> &reveal){
  bool answer; //if the coordinates are out of bounds, set to true
  

  //keeps going until the first coordinate is valid
  do{
    answer = false;

    cout<<endl<<"Input guess row:";
    cin>>row1;
    cout<<"Input guess column:";
    cin>>col1;

    //if either of the inputs are out of bounds
    if(row1 > 3 || row1 < 0 || col1 > 3 || col1 < 0){
      cout<<"!! bad input";
      answer = true;
    }

    //checks to see if the coordinates is already a flipped card
    if(answer != true){
      for(int x = 0; x < emojis.size(); x++){//sees if any emoji is any this spot
        if(reveal[row1][col1] == emojis[x]){
          cout<<"!! bad input";
          answer = true;
        }
      }
    }
    
  }while(answer != false);

  //keeps going until the second coordinate is valid
  do{
    answer = false;

    cout<<endl<<"Input guess row:";
    cin>>row2;
    cout<<"Input guess column:";
    cin>>col2;

    //if either of the inputs are out of bounds
    if(row2 > 3 || row2 < 0 || col2 > 3 || col2 < 0){
      cout<<"!! bad input";
      answer = true;
    }

    //checks to see if the coordinates is already a flipped card
    if(answer != true){
      for(int x = 0; x < emojis.size(); x++){//sees if any emoji is any this spot
        if(reveal[row2][col2] == emojis[x]){
          cout<<"!! bad input";
          answer = true;
        }
      }
    }
  }while(answer != false);
  return row1;
  return col1;
  return row2;
  return col2;
}

//reveals the two coordinates
void revealCurrent2(int row1, int col1, int row2, int col2, matrix<string> &reveal, matrix<string> &hidden){
  //flips the first coordinate
  reveal[row1][col1] = hidden[row1][col1];

  //flips the second coordinate
  reveal[row2][col2] = hidden[row2][col2];
}

//flips the two coordinates back to the blanks
void unmarkCurrent2(int row1, int col1, int row2, int col2, matrix<string> &reveal){

  //unflips the first coordinate
  reveal[row1][col1] = "❓";

  //unflips the second coordinate
  reveal[row2][col2] = "❓";
}

//checks the if the users guess is a match
bool checkMatch(int row1, int col1, int row2, int col2, matrix<string> &reveal){

  bool answer;//if the users guess is a match, set to true

  if(reveal[row1][col1] == reveal[row2][col2]){
    answer = true;
  }
  if(reveal[row1][col1] != reveal[row2][col2]){
    answer = false;
  }

  return answer;
}

int main() {

  srand(time(0));
  
  matrix<string> reveal(4,4);
  matrix<string> hidden(4,4);

  int row1, col1, row2, col2;

  bool playAgain;
  char answer;

  //keeps going until the user doesnt want to play again
  do{
    //generates a new board and sets the matches to 8
    int matches = 8;
    generateBoard(hidden);
    do{
      drawBoard(reveal);//prints the users board

      cout<<endl<<"Matches Left to Make: "<<matches;
      collectGuess(row1, col1, row2, col2, reveal);//asks the users guesses

      system("clear");

      revealCurrent2(row1, col1, row2, col2, reveal, hidden);
      drawBoard(reveal);//prints the board with the users flipped guesses

      bool check = checkMatch(row1, col1, row2, col2, reveal);
      //if the users guesses dont match, flips the cards back to blanks
      if(check == false){
        unmarkCurrent2(row1, col1, row2, col2, reveal);
      }
      //if the users guesses do match, it subtracts how many matches are left to make
      if(check == true){
        matches = matches - 1;
      }
      
      string temp;
      cout<<endl<<"Please enter to continue";
      getline(cin, temp);
      cin.ignore();

    }while(matches != 0);
    cout<<endl<<"Do you want to play again? y/n: ";
    cin>>answer;

    //if the player wants to play again, replays the do while
    if(answer == 'y'){
      playAgain = true;
    }
    //if the player doesnt want to play again, stops the do while
    if(answer == 'n'){
      playAgain = false;
    }

  }while(playAgain != false);


}
