#include <iostream>
#include <cassert>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include "Hash_chain.h"
#include "Hash_probing.h"
#include "Vector.h"
#include "Occur.h"

using namespace std;
using namespace chrono;

void karpRabin(string, const char[], int, ofstream&);
int pow(int, int, int);
void readFile(ifstream&, Hash_chain<char*>&);
void readFile(ifstream&, Hash_probe<char*>&);
void readFile(ifstream&, Hash_probe<char*>&, Hash_chain<char*>&, ofstream&);
bool checkTitle(char*);
void showMenu();

int sentenceCount = 0;
int RPcount = 0;
int line = 8417;
Occur<char*> occur;
string pattern;

int main(int argc, char** argv){
    int choice, hash;
    Hash_chain<char *> hash_chain(nullptr, 600);
    Hash_probe<char *> hash_probe(nullptr, 600);
    char* word = new char[255], *found;

    ifstream input;
    ofstream output;
    input.exceptions(fstream::failbit | fstream::badbit);
    try{
        input.open(argv[1]);
    }catch(fstream::failure ex){
        cerr << "failed to open file: exception " << ex.what() << endl;
        exit(1);
    }
    output.exceptions(fstream::failbit | fstream::badbit);
    try{
        output.open(argv[2], ios::out);
        streambuf* stream_buffer_cerr = cerr.rdbuf();
        streambuf* stream_buffer_cout = cout.rdbuf();
        streambuf* stream_buffer_output = output.rdbuf();
        cerr.rdbuf(stream_buffer_output); 

        cout << "Enter word for section IX: ";
        cin >> pattern;

        steady_clock::duration linearDuration;
        auto ProgramStart = high_resolution_clock::now();
        auto dataTimeStart = high_resolution_clock::now();

        auto chainTimeStart = high_resolution_clock::now();
        readFile(input, hash_chain);
        auto chainTimeEnd = high_resolution_clock::now();

        auto probeTimeStart = high_resolution_clock::now();
        readFile(input, hash_probe);
        auto probeTimeEnd = high_resolution_clock::now();
        linearDuration = probeTimeEnd-probeTimeStart;

        readFile(input, hash_probe, hash_chain, output);

        auto probeTimeStart2 = high_resolution_clock::now();
        readFile(input, hash_probe);
        auto probeTimeEnd2 = high_resolution_clock::now();
        linearDuration += (probeTimeEnd2-probeTimeStart2);        

        auto dataTimeEnd = high_resolution_clock::now();
        input.close();
        auto chainOptStart = high_resolution_clock::now();
        hash_chain.optimize();
        auto chainOptEnd = high_resolution_clock::now();
        auto chainOptDuration = duration_cast<nanoseconds>(chainOptEnd-chainOptStart);
        auto chainTimeDuration = duration_cast<nanoseconds>(chainTimeEnd-chainTimeStart);
        auto probeDuration = duration_cast<nanoseconds>(linearDuration);
        auto dataDuration = duration_cast<nanoseconds>(dataTimeEnd-dataTimeStart);
        auto ProgramEnd = high_resolution_clock::now();
        auto ProgramDuration = duration_cast<nanoseconds>(ProgramEnd-ProgramStart);

        showMenu();
        cin >> choice;
        while(choice != 0){
            switch(choice){
                case 1:
                    // perform hash look up (Adventures I-VII)
                    cout << "Enter hash index: ";
                    cin >> hash;
                    cerr << "User input in (1): " << hash << endl;
                    found = hash_chain.search(hash);
                    cout << "The word is: " << found << endl;
                    cerr << "The word is: " << found << endl << endl;
                    break;
                case 2:
                    // perform hash look up (Adventures VIII-XII)
                    cout << "Enter hash index: ";
                    cin >> hash;
                    cerr << "User input in (2): " << hash << endl;
                    found = hash_probe.search(hash);
                    cout << "The word is: " << found << endl;
                    cerr << "The word is: " << found << endl << endl;
                    break;
                case 3:
                    // report on RKP Algo run (Adventure IX)
                    cerr << "User chose (3): " << endl;
                    cout << "Number of occurrence of " << pattern << ": " << RPcount << " in IX"<< endl;
                    cerr << "Number of occurrence of " << pattern << ": " << RPcount << " in IX" << endl;
                    break;
                case 4:
                    // print hash table (chaining)
                    hash_chain.print();
                    break;
                case 5:
                    // print hash table (linear probing)
                    hash_probe.print();
                    break;
                case 6:
                    // look up index in hash table (chaining)
                    cout << "Enter word in hash table (chaining) for index" << endl;
                    cin >> word;
                    cerr << "User input in (6): " << word << endl;
                    hash = hash_chain.search(word);
                    cout << "The index for " << word << " is: " << hash << endl;
                    cerr << "The index for " << word << " is: " << hash << endl << endl;
                    break;
                case 7:
                    // look up index in hash table (linear probing)
                    cout << "Enter word in hash table (chaining) for index" << endl;
                    cin >> word;
                    cerr << "User input in (7): " << word << endl;
                    hash = hash_probe.search(word);
                    if(hash == -1){
                        cout << "Word not in hash table" << endl;
                        cerr << "Word not in hash table" << endl << endl;
                    }else{
                        cout << "The index for " << word << " is: " << hash << endl;
                        cerr << "The index for " << word << " is: " << hash << endl << endl;                        
                    }
                    break;
                case 8:
                    // output the number of sentences in the text
                    cerr << "User chose (8): " << endl;
                    cout << "There are " << sentenceCount << " sentences in this text." << endl;
                    cerr << "There are " << sentenceCount << " sentences in this text." << endl << endl;
                    break;
                case 9:
                    // output the most occuring words (top 80)
                    cerr << "User chose (9):" <<endl;
                    occur.printTop(80);
                    break;
                case 10:
                    // output the least occuring words (bottom 80)
                    cerr << "User chose (10):" <<endl;
                    occur.printbottem(80);
                    break;
                case 99:
                    // output everything
                    cerr << "User input (99):\n";
                    cerr << "SYNOPSIS OF PROGRAM:" << endl;
                    cerr << "Linear Probing occupency used: 75%" << endl;
                    cerr << "Hash chaning length optimality was: 228" << endl;
                    cerr << "Hash function used for insertion: r%h.getSize()" << endl;
                    cerr << "Hash fucntion for Rabin-Karp: \n"<<
                    "hash(txt[s+1...s+m]) = (d(hash(txt[s...s+m-1])-txt[s]*h) + txt[s+m]) mod q" << endl;
                    cerr << "Collision resolusion for linear probing was:"
                    <<" Moving item down the list until a null space as reached or resize needed"<< endl;
                    cerr << "h-files were used: yes" << endl;
                    cerr << "Most occuring word was " << occur.getTop() << endl;
                    cerr << "Least occuring word was " << occur.getBottom() << endl;
                    cerr << "Number of sentences in the text was: " << sentenceCount << endl;
                    cerr << "Run time for Hash chaining data collection: " << chainTimeDuration.count() << "ns" << endl;
                    cerr << "Run time for Hash chaining optimization: " << chainOptDuration.count() << "ns" << endl;
                    cerr << "Run time for Hash probing data collection & optimization: " << probeDuration.count() << "ns" << endl;
                    cerr << "Run time for data collection: " << dataDuration.count() << "ns" << endl;
                    cerr << "Run time for over all program: " << ProgramDuration.count() << "ns" << endl << endl;
                    cout << "Information has been published to report.txt" << endl;
                    break;
            }
            cout << endl;
            memset(word, 0, 255);
            cin.ignore();
            showMenu(); 
            cin >> choice;      
        } 
        output.close();
        cerr.rdbuf(stream_buffer_cerr);
    }catch(fstream::failure ex){
        cerr << "File failure in main: " << ex.what() << endl;
    }
    cout << "Program ended. Goodbye!" << endl;
    return 0;
}

void readFile(ifstream& infile, Hash_chain<char*>& h){
    Vector<char> str;
    int fsize = 81, ssize = 47, r = 0;
    char* fname = new char[fsize];
    assert(fname!=nullptr);
    char* sname = new char[ssize];
    assert(sname!=nullptr);
    char *tmp = nullptr, *pch;
    char d[] = " \n\'\"\r,;:";

    while(!infile.eof()){
        infile >> fname[0];
        infile.getline(&fname[1], fsize, '\n');
        if(strncmp(fname, "ADVENTURE I. A SCANDAL IN BOHEMIA", 33)==0){
            while(!infile.eof()){

                infile >> sname[0];
                infile.getline(&sname[1], ssize, ' ');
                pch = strtok(sname, d);

                while(pch != nullptr){

                    if(strcmp(pch, "VII.")==0){
                        tmp = nullptr;
                        pch = nullptr;
                        delete [] fname;
                        delete [] sname;
                        str.clear();
                        cout << "I - VII......done" << endl;
                        return; 
                    }

                    for(int i=0; i < strlen(pch); i++){
                        if(pch[i] == '-' && pch[i+1] == '-'){
                            pch[i] = ' ';
                            pch[i+1] = ' ';
                            break;
                        }
                        else if(isalpha(pch[i]) || pch[i] == '-'){
                            str.push(tolower(pch[i]));
                            pch[i] = tolower(pch[i]);
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
                        occur.push(tmp);
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
    delete [] sname;
}

void readFile(ifstream& infile, Hash_probe<char*>& h){
    Vector<char> str;
    int fsize = 81, ssize = 47, r = 0;
    char* sname = new char[ssize];
    assert(sname!=nullptr);
    char *tmp = nullptr, *pch;
    char d[] = " \n\'\"\r,;:";

    while(!infile.eof()){

        infile >> sname[0];
        infile.getline(&sname[1], ssize, ' ');
        pch = strtok(sname, d);

        while(pch != nullptr){
            if(strcmp(pch, "IX.")==0){
                delete [] sname;
                str.clear();
                cout << "VII - IX......done" << endl;
                return;
            }else if(strcmp(pch, "***")==0){
                delete [] sname;
                str.clear();
                cout << "X - END......done" << endl;
                return;
            }

            for(int i=0; i < strlen(pch); i++){
                if(pch[i] == '-' && pch[i+1] == '-'){
                    pch[i] = ' ';
                    pch[i+1] = ' ';
                    break;
                }
                else if(isalpha(pch[i]) || pch[i] == '-'){
                    str.push(tolower(pch[i]));
                    pch[i] = tolower(pch[i]);
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
                occur.push(tmp);
                h.insert(tmp, r%h.getSize());
            }
            
            str.clear();
            r = 0;      
            tmp = nullptr;  
            pch = strtok(nullptr, d);
        }
    }
    delete [] sname;
}

void readFile(ifstream& infile, Hash_probe<char*>& hp, Hash_chain<char*>& hc, ofstream& outfile){
    Vector<char> str;
    int fsize = 81, ssize = 100, r = 0;
    char* sname = new char[ssize];
    assert(sname!=nullptr);
    char *tmp = nullptr, *pch;
    char d[] = " \n\'\"\r,;:";
    bool chain = false, probe = true;
    steady_clock::duration overalltime;
    
    outfile << "Rabin-Karp section: " << endl;
    outfile << "Word is " << pattern << endl;
    cout << "Word for pattern matching: " << pattern << endl;

    while(!infile.eof()){

        infile >> sname[0];
        infile.getline(&sname[1], ssize, '\n');

        high_resolution_clock::time_point RPtimeStart = high_resolution_clock::now();
        karpRabin(pattern, sname, 11, outfile);
        high_resolution_clock::time_point RPtimeEnd = high_resolution_clock::now();
        overalltime = overalltime + (RPtimeEnd-RPtimeStart);
        auto RPDuration = duration_cast<microseconds>(overalltime);

        pch = strtok(sname, d);

        while(pch != nullptr){
            
            if(strcmp(pch, "X.")==0){
                delete [] sname;
                str.clear();
                cerr << "Rabin-Karp Runtime was: " << RPDuration.count() << "ms" << endl << endl;
                cout << "IX - X......done" << endl;
                return;
            }

            for(int i=0; i < strlen(pch); i++){
                if(pch[i] == '-' && pch[i+1] == '-'){
                    pch[i] = ' ';
                    pch[i+1] = ' ';
                    break;
                }
                else if(isalpha(pch[i]) || pch[i] == '-'){
                    str.push(tolower(pch[i]));
                    pch[i] = tolower(pch[i]);
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
                occur.push(tmp);
                if(probe){
                    hp.insert(tmp, r%hp.getSize());
                    chain = true;
                    probe = false;
                }else if(chain){
                    hc.insert(tmp, r%hc.getSize());
                    chain = false;
                    probe = true;  
                } 
            }
            
            str.clear();
            r = 0;      
            tmp = nullptr;  
            pch = strtok(nullptr, d);
        }
    }
    delete [] sname;
}

bool checkTitle(char* check){
    const char* title[] = {"mr.","mrs.","dr.", "prof.", "ms.",
     "jr.", "sr.", "sir.","st.", "hon.", "rev.", "esq.", "messers.", "mmes.", 
     "msgr.", "rt."};
    
    for(int i = 0; i < 16; i++){
        if(strcmp(title[i], check) == 0)
            return true;
    }
    return false;
}

void karpRabin(string pattern, const char inputText[], int primeInput, ofstream& outfile)
{
    int pLen = pattern.size();
    int tLen = strlen(inputText);
    int pHash = 0;
    int tHash = 0;

    if (pLen == 1)
    {
        pHash = toupper(pattern[0]) % primeInput;
        tHash = toupper(inputText[0]) % primeInput;
        }
    else
    {
        for (int i = 0; i < pLen; i++)
        {
            pHash = (pHash * 256 + toupper(pattern[i])) % primeInput;
            tHash = (tHash * 256 + toupper(inputText[i])) % primeInput;
        }
    }


    for (int i = 0; i <= tLen - pLen; i++)
    {
        if (pHash == tHash)
        {
            bool match = true;
            for (int j = 0; j < pLen; j++)
            {
                if (toupper(inputText[i+j]) != toupper(pattern[j]))
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                if ((i == 0 || !isalnum(inputText[i-1])) && !isalnum(inputText[i+pLen]))
                {
                    outfile << "Pattern found at:\n";
                    outfile << "line: " << line << " column:" <<  i << endl;
                    RPcount++;
                }
            }
        }
        if (i < tLen - pLen)
        {
            tHash = ((tHash - toupper(inputText[i]) * pow(256, pLen-1, primeInput)) * 256 + toupper(inputText[i+pLen])) % primeInput;
            if (tHash < 0)
            {
                tHash += primeInput;
            }
        }
    }
    line++;
}

int pow(int x, int n, int prime) 
{
    int result = 1;
    for (int i = 0; i < n; i++) {
        result = (result * x) % prime;
    }
    return result;
}

void showMenu(){
    cout << endl << "Enter for the following: "<< endl;
    cout << "(0) to exit" << endl;
    cout << "(1) to perform hash look up (Adventures I-VII)" << endl;
    cout << "(2) to perform hash look up (Adventures VIII-XII)" << endl;
    cout << "(3) to see RKP report (Adventure IX)" << endl;
    cout << "(4) to print hash table (chaining)" << endl;
    cout << "(5) to print hash table (linear probing)" << endl;
    cout << "(6) to look up index in hash table (chaining)" << endl;
    cout << "(7) to look up index in hash table (linear probing)" << endl;
    cout << "(8) to output the number of sentences in the text" << endl;
    cout << "(9) to output the most occuring words (top 80)" << endl;
    cout << "(10) to output the least occuring words (bottom 80)" << endl;
    cout << "(99) to output everything" << endl;
}