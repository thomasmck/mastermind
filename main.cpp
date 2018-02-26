/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Tom
 *
 * Created on 21 February 2018, 20:17
 * 
 * Idea from http://www.cplusplus.com/forum/lounge/2825/
 * 
 */
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <cstdlib>

using namespace std;

/*
 * 
 */

vector<char> generate_board() {
    int i;
    vector<char> board;
    // Note char uses '' not ""
    vector<char> options = {'a', 'b', 'c', 'd', 'e', 'f'};
    srand( time( NULL ) );
    for( int a = 0; a < 6; a++ ) {
        i = rand() % 6;
        board.push_back(options[i]);
    }
    return board;
}

vector<char> string_to_vector(string str) {

    vector<char> vec;
    for(char& c : str) {
        vec.push_back(c);
    }
    return vec;
}

string vector_to_string(vector<char> vec) {
    string str(vec.begin(), vec.end());
    return str;
}

int exact_matches(vector<char> code, vector<char> guess) {
    int matches = 0;
    // Should make this dynamically work out vector size
    for (int x = 0; x < 6; x++){
        if (code[x] == guess[x]) {
            matches++;
        }
    }
    return matches;
}

int partial_matches(vector<char> code, vector<char> guess) {
    int matches = 0;
    for(char x : code) {
        int matched = 0;
        for (char y : guess) {
            int position = 0;
            if (x == y and matched == 0) {
                guess.erase (guess.begin()+position);
                matches++;
                matched = 1;
            }
            position++;
        }
    }
    return matches;
}

int check_for_winner(int exact) {
    if (exact == 6) return 1;
    else return 0;
}

int main(int argc, char** argv) {
    vector<char> code = generate_board();
    cout << "The codemaker has generated the secret code" <<endl;
    cout << vector_to_string(code) <<endl;
    int winner = 0;
    int turns = 0;
    while ( winner != 1 and turns < 10) {
        turns++;
        cout<<"---------------"<<endl;
        cout<<"Turn "<<turns<<endl;
        cout << "Submit your guess Mastermind, i.e. abcfea" <<endl;
        string x;
        cin>>x;
        vector<char> guess = string_to_vector(x);
        int exact = exact_matches(code, guess);
        cout<<"Number of exact matches: "<<exact<<endl;
        int partial = partial_matches(code, guess);
        cout<<"Number of partial matches: "<<partial<<endl;
        winner = check_for_winner(exact);
    }
    // Track number of turns
    if (winner == 1) cout<<"Congratulations you won in "<<turns<<" turns"<<endl;
    else cout<<"You lose"<<endl;
    return 0;
}

