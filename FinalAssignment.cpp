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

void readFile(ifstream&, Hash_chain<char*>&);
bool checkTitle(char*);

int sentenceCount = 0;
const char* adventure[] = {"VII.", "IX", "XII.", "***"};

struct Occur{
    char* word;
    int rank = 0;
    Occur* next;
};

int main(int argc, char** argv){

    Occur* occur = new Occur[255];
    Hash_chain<char *> hash_chain;
    ifstream input;
    ofstream output;
    input.open(argv[1]);

    readFile(input, hash_chain);
    hash_chain.print();
    // hash_chain.printIdx(541);

    return 0;
}

void readFile(ifstream& infile, Hash_chain<char*>& h){
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
                        if(pch[i] >= 65 && pch[i] <= 90 || pch[i] >= 97 && pch[i] <= 122 || pch[i] == '-'){
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