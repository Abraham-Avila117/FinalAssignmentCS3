#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <chrono>
#include <cctype>

using namespace std;
using namespace chrono;

void karpRabin(string pattern, const char inputText[], int primeInput);
int pow(int x, int n);
const char* rightLine(string file_path, string start_string, string end_string);
const int MAX = 1000000;


int pow(int x, int n, int prime) 
{
    int result = 1;
    for (int i = 0; i < n; i++) {
        result = (result * x) % prime;
    }
    return result;
}

void karpRabin(string pattern, const char inputText[], int primeInput)
{
    auto start = high_resolution_clock::now();
    int pLen = pattern.size();
    int tLen = strlen(inputText);
    int pHash = 0;
    int tHash = 0;
    int count = 0;

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
                    cout << "Pattern found at index " << i << endl;
                    count++;
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

    auto stop = high_resolution_clock::now();
    auto durationR = duration_cast<microseconds>(stop - start);

    cout << "Karp Rabin:" << endl;
    cout << "Number of occurrences in text is: " << count << endl;
    cout << "Time: " << durationR.count() << " microseconds" << endl << endl;
}

const char* rightLine(string file_path, string start_string, string end_string)
{
    char* content = new char[MAX];
    memset(content, 0, MAX);

    bool found_start_string = false;

    ifstream file(file_path);
    if (!file) {
        return "";
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

    return "";
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
            infile.open("test.txt", ios::in | ios::binary);
            if(infile && run == true)
            {
                const char* result = rightLine(filename, "IX. THE ADVENTURE OF THE ENGINEER'S THUMB", "X. THE ADVENTURE OF THE NOBLE BACHELOR");
                const char* text = rightLine(filename, "*** START OF THIS PROJECT GUTENBERG EBOOK THE ADVENTURES OF SHERLOCK HOLMES ***", "END OF THIS PROJECT GUTENBERG EBOOK THE ADVENTURES OF SHERLOCK HOLMES");

                // infile.seekg(0, infile.end);
                // flen = infile.tellg();
                // infile.seekg(0,infile.beg);

                // //char text[flen];
                // infile.read(text, flen);

                infile.close();

                cout << "File Read Successfully" << endl << endl;

                cout << "Enter a pattern: ";
                cin >> pattern;

                int prime = 17;

                karpRabin(pattern, text, prime);
                cout << "THE ADVENTURE OF THE ENGINEER'S THUMB" << endl;
                karpRabin(pattern, result, prime);

                run = false;
            }
    }  
    return 0;
}
