#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

int HornerRule(int n, int primeInput);
void karpRabin(string pattern, const char inputText[], int primeInput);

void karpRabin(string pattern, const char inputText[], int primeInput)
{
    int pLen = pattern.size();
    int tLen = strlen(inputText);
    int pHash = 0;
    int tHash = 0;
    int count = 0;
    int i, j;

    // Prompt user for word to search
    // cout << "Enter word to search: ";
    // cin >> pattern;

    // Calculate pattern hash value
    for(i=0; i < pLen; i++)
    {
        pHash = (pHash*256 + pattern[i]) % primeInput;
        tHash = (tHash*256 + inputText[i]) % primeInput;
    }

    // Perform Rabin-Karp pattern matching
    for(i=0; i <= tLen-pLen; i++)
    {
        if(pHash == tHash)
        {
            for(j=0; j<pLen; j++)
            {
                if(inputText[i+j] != pattern[j])
                {
                    break;
                }
            }

            if(j == pLen)
            {
                count++;
                cout << "Found at position " << i << endl;
            }
        }
        if(i<tLen-pLen)
        {
            tHash = (256*(tHash - inputText[i]*HornerRule(pLen-1, primeInput)) + inputText[i+pLen]) % primeInput;

            if(tHash < 0)
            {
                tHash = (tHash + primeInput);
            }
        }

    }
    cout << "Number of occurrences in text is: " << count << endl;
}

int HornerRule(int n, int primeInput) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result = (result * 256) % primeInput;
    }
    return result;
}

int main()
{
    bool run = true;
    string file = "test.txt";
    ifstream infile;
    int primeInput = 101;
    string word;
    long int len;

    int words =1; //will not count first word so initial value is 1
    char ch;
    infile.seekg(0,ios::beg); //bring position of file pointer to begining of file

    infile.open(file);
 

    while(infile)
            {
                infile.get(ch);
                if(ch==' '||ch=='\n')
                words++;
            } 
    cout << "Length of file: " << words << endl;


    while(run)
    {
        //infile.open(file);
        if(infile.is_open())
        {
            int words =1; //will not count first word so initial value is 1
            char ch;
            infile.seekg(0,ios::beg); //bring position of file pointer to begining of file
 
            // while(infile)
            // {
            //     infile.get(ch);
            //     if(ch==' '||ch=='\n')
            //     words++;
            // } 
            // cout << "Length of file: " << words << endl;

 
            char inputText[len];

            infile.read(inputText, len);

            cout << "File read successfully" << endl;

                cout << "Enter word: ";
                cin >> word;


            if(infile)
            {
                karpRabin(word, inputText, primeInput);
                break;
            }
            run = false;
            infile.close();
            break;

        }
    }
    // cout << "Length of file: " << words << endl;
    return 0;
}