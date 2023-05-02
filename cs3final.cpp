#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <chrono>

using namespace std;
using namespace chrono;

void karpRabin(string pattern, const char inputText[], int primeInput);
int pow(int x, int n);
char* rightLine(string file_path, string start_string, string end_string);

const int MAX = 1000000;


void karpRabin(string pattern, const char inputText[], int primeInput)
{
    auto start = high_resolution_clock::now();
    int pLen = pattern.size();
    int tLen = strlen(inputText);
    int pHash = 0;
    int tHash = 0;
    int count = 0;

    int i, j;

    for(i=0; i < pLen; i++)
    {
        pHash = (pattern[i]) % primeInput;
        tHash = (inputText[i] % primeInput);
    }

    bool in_word = false;
    string word;
    for(i=0; i < tLen; i++)
    {
        if(isalpha(inputText[i])) {
            in_word = true;
            word += tolower(inputText[i]);
        } else if(in_word) {
            in_word = false;
            if(word.size() >= pLen) {
                bool match = true;
                for(j = 0; j < pLen; j++) {
                    if(word[j] != pattern[j]) {
                        match = false;
                        break;
                    }
                }
                if(match) {
                    count++;
                }
            }
            word.clear();
        }
    }
    auto stop = high_resolution_clock::now();
    auto durationR = duration_cast<microseconds>(stop-start);

    cout << "Karp Rabin:" << endl;
    cout << "Number of occurrences in text is: " << count << endl;
    cout << "Time: " << durationR.count() << " microseconds" << endl << endl;
}

int pow(int x, int n) {
    int result = 1;
    for (int i = 0; i < n; i++) {
        result *= x;
    }
    return result;
}

char* rightLine(string file_path, string start_string, string end_string)
{
    char* content = new char[MAX];
    memset(content, 0, MAX);

    bool found_start_string = false;

    ifstream file(file_path);
    if (!file) {
        return "fail";
    }

    string line;
    while (getline(file, line)) {
        if (found_start_string) {
            if (line.find(end_string) != string::npos) {
                return content;
            } else {
                strcat(content, (line + "\n").c_str());
            }
        } else if (line.find(start_string) != string::npos) {
            found_start_string = true;
        }
    }

    return "fail";
}


int main()
{
    bool run = true;
    string filename = "test.txt";
    string pattern;
    ifstream infile;
    int flen;
    char in;
    while(run)
    {
            infile.open(filename, ios::in | ios::binary);
            if(infile && run == true)
            {
                char* result = rightLine(filename, "IX. THE ADVENTURE OF THE ENGINEER'S THUMB", "X. THE ADVENTURE OF THE NOBLE BACHELOR");

                infile.seekg(0, infile.end);
                flen = infile.tellg();
                infile.seekg(0,infile.beg);

                char text[flen];
                infile.read(text, flen);

                infile.close();

                cout << "File Read Successfully" << endl << endl;

                cout << "Enter a pattern: ";
                cin >> pattern;

                int prime = 17;

                karpRabin(pattern, text, prime);
                karpRabin(pattern, result, prime);

                run = false;
            }
    }  
return 0;
}
