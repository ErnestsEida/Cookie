#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const string TYPE_INT      = "int";
const string TYPE_STRING   = "str";
const string TYPE_BOOLEAN  = "bool";

const vector<string> VARIABLE_TYPES = {TYPE_INT, TYPE_STRING, TYPE_BOOLEAN};

int ROW_COUNT = 0;

struct Variable {
    string type;
    void* value;
};

struct UniversalValue {
    string* str;
    int* integer;
    bool* boolean;
    UniversalValue(int value) {integer = new int(value);}
    UniversalValue(string value) {str = new string(value);}
    UniversalValue(bool value) {boolean = new bool(value);}
    UniversalValue(){
        str = NULL;
        integer = NULL;
        boolean = NULL;
    }
};

map<string, Variable> Variables;

void* GetValueFromString(string type, string value)
{  
    void * result;
    if (type == TYPE_INT) {
        result = new int(stoi(value));
    } else if (type == TYPE_STRING) {
        result = new string(value);
    } else if (type == TYPE_BOOLEAN) {
        result = new bool(false); // THINK OF A WAY TO ASSIGN
    }
    return result;
}

vector<string> SplitLineToWords(string line){
    vector<string> result;
    string temp = "";
    for(int i = 0;i < line.length();i++){
        if (line[i] == ' ' || line[i] == ';'){
            if (temp.length() > 0){
                result.push_back(temp);
                temp = "";
            }
        } else {
            temp = temp + line[i];
        }
    }
    return result;
}

bool IsVariable(string type){
    return find(VARIABLE_TYPES.begin(), VARIABLE_TYPES.end(), type) != VARIABLE_TYPES.end();
}

bool AddVariable(vector<string> words){
    if (!IsVariable(words[0])) return false;
    else {
        Variable var;
        var.type = words[0];
        var.value = GetValueFromString(words[0], words[3]);
        Variables.insert(pair<string, Variable>(words[1], var));
        return true;
    }
}

bool AddFunction(vector<string> words){
    return false;
}

bool Define(string line){
    bool defined = false;
    vector<string> words = SplitLineToWords(line);

    defined = AddVariable(words);
    if (!defined) AddFunction(words);

    return defined;
}

int main(int argc, char *argv[]) {
    if (argc == 1){
        cout << "No input file passed!" << endl;
        return 0;
    } else {
        ifstream file(argv[1]);
        if (file.is_open()){
            string line;
            vector<string> words;
            while(!file.eof())
            {
                getline(file, line);
                ROW_COUNT++;
                Define(line);
            }
            file.close();
        } else {
            cout << "Error opening file!" << endl;
        }
    }

    cout << "VARIABLES: " << endl;
    for(int i = 0;i < Variables.size();i++){
        cout << *(int*)Variables["myNum"].value << endl;
    }
    return 0;
}