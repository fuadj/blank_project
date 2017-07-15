#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "random.h"

using namespace std;

string promptUserForFile(ifstream & infile, string prompt = "");

string scrambleLine1(string & line);
string scrambleLine2(string & line);
void removeComments(istream &is, ostream &os);

int main() {
    ifstream infile;
    promptUserForFile(infile, "Input file: ");

    removeComments(infile, cout);
    infile.close();
    return 0;
}

string promptUserForFile(ifstream & infile, string prompt) {
    while (true) {
        cout << prompt;
        string filename;
        getline(cin, filename);
        infile.open(filename.c_str());
        if (!infile.fail())
            return filename;
        infile.clear();
        cout << "Unable to open that file. Try again. " << endl;
        if (prompt == "")
            prompt = "Input file: ";
    }
}

string UPPER_CASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string LOWER_CASE = "abcdefghijklmnopqrstuvwxyz";
int ALPHABET_SIZE = UPPER_CASE.size();

void removeComments(istream & is, ostream & os) {
    bool line_comment = false;
    bool multi_line_comment = false;

    int prev_ch;
    int ch;
    bool prev_comment = false;

    prev_ch = is.get();
    if (prev_ch == EOF) return;

    if (prev_ch != '/') {
        os.put((char)prev_ch);
    }

    bool was_inside_comment = false;
    while ((ch = is.get()) != EOF)  {
        was_inside_comment = line_comment || multi_line_comment;
        if (ch == '/') {
            if (prev_ch == '/') {
                if (!multi_line_comment) {
                    line_comment = true;
                }
            } else if (prev_ch == '*') {
                if (multi_line_comment) {
                    multi_line_comment = false;
                }
            }
        } else if (ch == '*' && prev_ch == '/') {
            if (!line_comment) {
                multi_line_comment = true;
            }
        } else if (ch == '\n') {
            line_comment = false;
        }

        //printf("[%c,%d], ", (char)ch, ch);

        if (ch == '/') {
        } else if (!(line_comment || multi_line_comment)) {
            if (prev_ch == '/' && !prev_comment) {
                os.put((char)prev_ch);
            }
            os.put((char)ch);
        }

        prev_comment = was_inside_comment || line_comment || multi_line_comment;
        prev_ch = ch;
    }
}

string scrambleLine1(string &line) {
    ostringstream result;
    istringstream lineStream(line);

    int ch;
    while ((ch = lineStream.get()) != EOF)  {
        if (!isalpha(ch)) {
            result << (char)ch;
            continue;
        }

        int rand_index = randomInteger(0, ALPHABET_SIZE);
        char replacement;
        if (isupper(ch)) {
            replacement = UPPER_CASE[rand_index];
        } else {
            replacement = LOWER_CASE[rand_index];
        }
        result << replacement;
    }

    return result.str();
}

string scrambleLine2(string &line) {
    string result;
    for (int i = 0; i < line.size(); i++) {
        char ch = line[i];
        if (!isalpha(ch)) {
            result += ch;
            continue;
        }

        int rand_index = randomInteger(0, ALPHABET_SIZE);
        char replacement;
        if (isupper(ch)) {
            replacement = UPPER_CASE[rand_index];
        } else {
            replacement = LOWER_CASE[rand_index];
        }
        result += replacement;
    }
    return result;
}
