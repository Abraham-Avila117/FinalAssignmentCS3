#include <iostream>
#include <cassert>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include "Hash_chain.h"
#include "Vector.h"

using namespace std;
using namespace chrono;

void readFile(ifstream&, ofstream&, Hash_chain<char*>&);
bool checkTitle(char*);
void showMenu();

int sentenceCount = 0;
const char* adventure[] = {"VII.", "IX", "XII.", "***"};

struct Occur{
    char* word;
    int rank = 0;
    Occur* next;
};


int main(int argc, char** argv){

    Hash_chain<char *> hash_chain(nullptr, 1069);
    ifstream input;
    ofstream output;
    input.open(argv[1]);

    readFile(input, output, hash_chain);

    hash_chain.print();
    // hash_chain.printIdx(541);

    return 0;
}

void readFile(ifstream& infile, ofstream& outfile, Hash_chain<char*>& h){
    Vector<char> str;
    int fsize = 81, ssize = 47, r = 0;
    char* fname = new char[fsize];
    char* sname = new char[ssize];
    char *tmp = nullptr, *pch;
    char d[] = " \n\'\",;:";

    while(!infile.eof()){
        infile >> fname[0];
        infile.getline(&fname[1], fsize, '\n');
        if(strncmp(fname, "ADVENTURE I. A SCANDAL IN BOHEMIA", 33)==0){
            while(!infile.eof()){

                infile >> sname[0];
                infile.getline(&sname[1], ssize, ' ');
                pch = strtok(sname, d);

                while(pch != nullptr){

                    if(strcmp(pch, "***")==0){
                        cout << "we did it!!!" << endl;
                        return; 
                    }

                    for(int i=0; i < strlen(pch); i++){
                        if(pch[i] == '-' && pch[i+1] == '-'){
                            pch[i] = ' ';
                            pch[i+1] = ' ';
                        }
                        else if(pch[i] >= 65 && pch[i] <= 90 || pch[i] >= 97 && pch[i] <= 122 || pch[i] == '-'){
                            str.push(tolower(pch[i]));
                            r += tolower(pch[i]);
                        }
                        else if(pch[i] == '.' || pch[i] == '?' || pch[i] == '!'){
                            if(!checkTitle(pch) && str.getsize() > 1){
                                sentenceCount++;
                                break;
                            }
                        }
                    }
                    tmp = str.getList();
                    if(strcmp(tmp, "\0")!=0){
                        h.insertCharArray(tmp, r%h.getSize());
                    }
                    str.clear();
                    r = 0;      
                    tmp = nullptr;  
                    pch = strtok(nullptr, d);
                }
            }
        }
    }
    delete [] fname;
    delete [] sname;
}

bool checkTitle(char* check){
    const char* title[] = {"mr","mrs","dr", "prof", "ms",
     "jr", "sr", "st", "hon", "rev", "esq", "messers", "mmes", 
     "msgr", "rt"};
    
    for(int i = 0; i < 16; i++){
        if(title[i] == check)
            return true;
    }
    return false;
}

void showMenu(){
    cout << "Enter for the following: "<< endl;
    cout << "(0) to exit" << endl;
    cout << "(1) to perform hash look up (Adventures I-VII)" << endl;
    cout << "(2) to perform hash look up (Adventures VIII-XII)" << endl;
    cout << "(3) to search for a word (Adventure IX)" << endl;
    cout << "(4) to print hash table (chaining)" << endl;
    cout << "(5) to print hash table (linear probing)" << endl;
    cout << "(6) to look up index in hash table (chaining)" << endl;
    cout << "(7) to look up index in hash table (linear probing)" << endl;
    cout << "(8) to output the number of sentences in the text" << endl;
    cout << "(9) to output the most occuring words (top 80)" << endl;
    cout << "(10) to output the least occuring words (bottom 80)" << endl;
    cout << "(99) to output everything" << endl;

}