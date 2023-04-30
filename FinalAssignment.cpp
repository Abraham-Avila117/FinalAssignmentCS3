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

static int sentenceCount = 0;

int main(int argc, char** argv){

    Hash_chain<char *> hash_chain;
    ifstream input;
    ofstream output;
    input.open(argv[1]);

    readFile(input, hash_chain);
    hash_chain.print();
    /*
    FinalAssignment tasks:
    object for main will be hash
    1. (Abraham) Hash table comprising of Open hasing with chaining (I-VI) 
        1a. Count the number of occurences of the words/strings in the section 

        1b. Answer (b) and (c) in assignment spec  

    2. (Arie) Linear probing (VII-XII)
        2a. Count the number of occurences of the words/strings in the section

        2b. Answer question (a), (c), and (d) in assignment spec

    3. (Connor) In IX, user must be prompt to do a word search, and use the Rabin-Karp pattern
        matching and Horner's rule for the rolling hash. Display the word count and positions 
        of the word from the user. This covers (f) in the assignment spec

    4. Word ranking the top 80 words by occurences (most and least). Capitalization does not matter
        and Double hyphen "--" must be removed. All outputs are streamed to a file from command 
        line argument. This covers (g) and (h) assignment spec

    5. Develope the main driver program function that is menu driven (0) to terminate and (99) 
        to output everything. This will take in a command line argument of the input file and 
        output file.
    
    6. Develope sentence counting function. Be sure to clearly define what is a sentence and 
        consult team if definition works. This covers (i) in the assignment spec

    7. Demo presenter when assignment is turned in and is responsible for turning in the 
        assignment. This task will be responsible for testing edge cases or errors and 
        addressing them (debugger). 
    
    For each task, these must be reported:
        1. Did you use a .h file to achive the tasks? (e) in spec
        2. Make sure to label your section when outputing to the file
        3. Everything will be output lower case except for Section title 
        4. report runtime in nansec (exception: task 6). (j) in spec
    
    Note: will consult with sherine about (k) in spec
    */
    return 0;
}

void readFile(ifstream& infile, Hash_chain<char*>& h){

    Vector<char> vector;
    Vector<char*> sentence;
    int size = 81, r = 0, max = 0;
    char* fname = new char[size], *str;
    assert(fname!=nullptr);

        try{
        while(!infile.eof())
        {
            infile >> fname[0];
            infile.getline(&fname[1], size, '\n');  
            if(strncmp(fname, "ADVENTURE I. A SCANDAL IN BOHEMIA", 33)==0){

                // go until start of sentence
                memset(fname, '\0', size);
                do{     
                    infile >> fname[0];
                    infile.getline(&fname[1], size);
                }while(fname[0]!='T');

                // insert to hash table and count sentences
                while(!infile.eof()){
                    for(int i = 0; i < strlen(fname); i++){
                        if(i+1 == strlen(fname)){
                            if(vector.isEmpty())
                                continue;
                            str = vector.getList();
                            h.insert(str, r%h.getSize());
                            r = 0;
                            vector.clear();
                            str = nullptr;
                            break;
                        }  
                        else if(fname[i] == '-' && fname[i+1] == '-'){
                            fname[i] = ' ';
                            fname[i+1] = ' ';
                        }
                        else if(fname[i] >= 65 && fname[i] <= 90 || fname[i] >= 97 && fname[i] <= 122 || fname[i] == '-'){
                            fname[i] = tolower(fname[i]);
                            vector.push(fname[i]);
                            r += fname[i];
                        }
                        else if(fname[i] == ' ' || fname[i] == ',' || fname[i] == ';' || fname[i] == ':'){
                            if(vector.isEmpty())
                                continue;
                            str = vector.getList();
                            sentence.push(str);
                            h.insert(str, r%h.getSize());
                            if(max < r%h.getSize()) max = r%h.getSize();
                            vector.clear();
                            r = 0;
                            str = nullptr;
                        }
                        else if(fname[i] == '.' || fname[i] == '?' || fname[i] == '!'){
                            str = vector.getList();
                            h.insert(str, r%h.getSize());
                            sentence.push(str);
                            if(!checkTitle(str) && vector.getsize() > 1){
                                sentenceCount++;
                                sentence.clear();
                            }
                            vector.clear();
                            r = 0;
                            str = nullptr;
                        }
                    }
                    memset(fname, '\0', size);
                    infile >> fname[0];
                    infile.getline(&fname[1], size); 

                    if(strncmp(fname, "ADVENTURE VI. THE MAN WITH THE TWISTED LIP", 41)==0)
                        return; 
                }
            }
        }
        sentence.clear();
        vector.clear();
        delete [] fname; 
    }catch(bad_alloc& ex){
        cout << ex.what() << endl;
    }
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