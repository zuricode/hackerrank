#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <limits>

using namespace std;

bool hasTagAccents(const string&);
bool hasClosingTag(const string&);
bool hasOpeningTag(const string&);
bool hasSpace(const string&);
bool hasAttributeName(const string&);
bool hasAttributeValue(const string&);
bool hasAttributes(const string&);

string obtainTagName(const string&);



int main() {

    int lines, queries;
    string line;
    vector<string> code;

    cin >> lines >> queries;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < lines; i++) {
        getline(cin, line);
        code.push_back(line);
    }

    return 0;
}

bool hasTagAccents(const string& STR) {

    int size = STR.length();

    if (STR[0] == '<' && STR[size - 1] == '>') {
        return true;
    }
    else {
        return false;
    }

}

bool hasClosingTag(const string& STR) {

    if (STR[1] == '/') {
        return true;
    }
    else {
        return false;
    }

}

bool hasOpeningTag(const string& STR) {

    if (!hasClosingTag(STR) && isalnum(STR[1]) && hasSpace(STR)) {
        return true;
    }
    else {
        return false;
    }

}

bool hasSpaces(const string& STR) {

    int space_counter = 0;

    for (int i = 0; i < STR.length(); i++) {
        if (STR[i] == ' ') {
            space_counter++;
        }
    }

    if (space_counter >= 1) {
        return true;
    }
    else {
        return false;
    }

}

bool hasAttributeName(const string& STR) {

    if (hasOpeningTag(STR)) {

        int index = 1;
        int equals_counter = 0,

            //Find first space character
            while (STR[index] != ' ') {
                index++;
            }

        //Find first alphanumeric character after the first space
        while (!isalnum(STR[index])) {
            index++;
        }

        //Find equals character
        while (STR[index] != '=' || index < STR.length()) {
            if (STR[index] == '=') {
                equals_counter++;
            }
        }

        if (equals_counter > 0) {
            return true;
        }
        else {
            return false;
        }

    }

    bool hasAttributeValue(const string & STR) {

        int quotation_counter = 0;
        int index = 1;

        //Find first quotation mark character
        while (STR[index] != '\"' || index < STR.length()) {
            if (STR[index] == '\"') {
                quotation_counter++;
            }
        }

        if (quotation_counter >= 2) {
            return true;
        }
        else {
            return false;
        }

    }

    bool hasAttributes(const string & STR) {

        if (hasOpeningTag(STR)) {

            int index = 1;
            int equals_counter = 0;

            //Find first space character
            while (STR[index] != ' ') {
                index++;
            }

            //Find first alphanumeric character after the first space
            while (!isalnum(STR[index])) {
                index++;
            }

            while (equals_counter == 0 && quotation_counter <= 1 && index < STR.length()) {

                if (STR[index] == '=') {
                    equals_counter++;
                }

                if (STR[index] == '\"') {
                    quotation_counter++;
                }

                index++;
            }

            if (equals_counter >= 1 && quotation_counter >= 2) {
                return true;
            }

        }
        else {
            return false;
        }

    }

    string obtainTagName(const string & STR) {

        int index;
        string tagName = "";

        if (!hasClosingTag(STR)) {
            index = 1;
        }
        else {
            index = 2;
        }

        while (STR[index] != ' ') {
            tagName += STR[index];
        }

        return tagName;

    }
