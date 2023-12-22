#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <limits>

using namespace std;

void enterHTMLLines(const int&, vector<string>&);

void updateTag(const vector<string>&, string&);

void removeBrackets(string&);
void inputTilda(string&);
void inputKeysAndValues(const vector<string>&, map<string, string>&);
void displayValues(const vector<string>&, const map<string, string>&);

int main() {

    int lines, queries;
    vector<string> lines_v;
    vector<string> queries_v;
    map<string, string> m;
    string query;

    cin >> lines >> queries;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    enterHTMLLines(lines, lines_v);

    inputKeysAndValues(lines_v, m);

    for (int i = 0; i < queries; i++) {
        getline(cin, query);
        queries_v.push_back(query);
    }

    displayValues(queries_v, m);

    return 0;
}

void enterHTMLLines(const int& LINES, vector<string>& v) {

    string s;
    int counter = 0;

    while (counter < LINES) {
        getline(cin, s);

        //Remove angle brackets
        removeBrackets(s);

        //Delete empty characters at the end of string
        while (s.back() == ' ') {
            s.pop_back();
        }

        v.push_back(s);
        counter++;

    }

}

void updateTag(const string& LINE, string& active_tag) {

    string temp = "";
    int counter = 0;
    size_t start_index, end_index;

    if (LINE[0] != '/') {

        if (active_tag.length() >= 1) {
            active_tag += ".";
        }

        while ((LINE[counter] != ' ' && LINE[counter] != '>') && counter < LINE.size()) {
            temp = LINE[counter];
            active_tag += temp;
            counter++;
        }

    }

    else {

        start_index = active_tag.find_last_of(".");

        if (start_index != string::npos) {

           end_index = active_tag.size();

           while (start_index < end_index) {
               active_tag.pop_back();
               start_index++;
           }

        }
        else {
            active_tag.clear();
        }

    }

 }

void removeBrackets(string& s) {

    s.erase(s.begin());
    s.erase(s.end() - 1);

}

void insertTilda(string& s) {

    size_t index;

    index = s.find(" ");
    s.replace(index, 1, "~");

}

void inputKeysAndValues(const vector<string>& V, map<string, string>& m) {

    size_t start_index = 0, end_index, index;
    string active_tag = "";
    string attribute_name;
    string attribute_value;
    string key;

    for (size_t i = 0; i < V.size(); i++) {

        key = "";

        //Form correct tag section
        updateTag(V[i], active_tag);

        if (active_tag.size() > 0) {        

            //Try to find " " for first attribute
            start_index = V[i].find(" ");

            while (start_index != string::npos) {

                key = active_tag;

                //Insert tilda symbol in correct position
                key += "~";

                //Move to first character of attribute name            
                start_index++;

                //Find index for the end of the attribute name
                end_index = V[i].find(" ", start_index);

                attribute_name = "";

                //Build attribute name
                while (V[i][start_index] != '=' && V[i][start_index] != ' ') {
                    attribute_name += V[i][start_index];
                    start_index++;
                }

                //Append attribute name to query key
                key += attribute_name;

                //Find opening '"' quotation mark of attribute value
                start_index = V[i].find("\"", start_index);

                //Move starting index to first character
                start_index++;

                //Find closing quotation mark of attribute value
                end_index = V[i].find("\"", start_index);

                //Clear attribute value string
                attribute_value = "";

                while (start_index < end_index) {
                    attribute_value += V[i][start_index];
                    start_index++;
                }

                m.insert(pair<string, string>(key, attribute_value));

                //Attempt to find next attribute
                start_index = V[i].find(" ", end_index);

            }

        }

    }

}

void displayValues(const vector<string>& QUERIES, const map<string, string>& MAP) {

    for (int i = 0; i < QUERIES.size(); i++) {

        if (MAP.count(QUERIES[i]) > 0) {
            cout << MAP.at(QUERIES[i]) << "\n";
        }
        else {
            cout << "Not Found!\n";
        }

    }

}