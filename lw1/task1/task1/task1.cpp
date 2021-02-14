﻿#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <algorithm>
#include <optional>

using namespace std;

struct Args
{
    string inputFileName;
    string outputFileName;
    string searched;
    string replaced;
};

void CopyAndReplace(ifstream& in, ofstream& out, string searched, string replaced);
bool IsBlankLine(string str);
string StrReplace(string line, string searched, string replaced);


optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 4 && argc != 5)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage: task1.exe <input file> <output file> <search string> <replace string>\n";
        return nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    args.searched = argv[3];
    args.replaced = argc == 4 ? "" :argv[4];
    return args;
}

int main(int argc, char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }
    ifstream in;
    ofstream out;
    in.open(args->inputFileName);

    if (!in.is_open())
    {
        cout << "Failed to open " << args->inputFileName << " for reading" << endl;
        return 1;
    }
    out.open(args->outputFileName);

    if (!out.is_open())
    {
        cout << "Failed to open " << args->outputFileName << " for writing" << endl;
        return 1;
    }

    string searched = args->searched;
    string replaced = args->replaced;

    CopyAndReplace(in, out, searched, replaced);
    return 0;
}

void CopyAndReplace(ifstream& in, ofstream& out, string searched, string replaced)
{
    string line;
    while (getline(in, line))
    {
        string lineAfterReplace = line;
        if (!IsBlankLine(line) && !replaced.empty())
        {
            lineAfterReplace = StrReplace(line, searched, replaced);
        }
        out << lineAfterReplace << endl;
    }
}

string StrReplace(string line, string searched, string replaced)
{
    const int searchedLength = searched.length();
    const int replacedLength = replaced.length();
    string lineAfterReplace = line;
    int posOfSearched = lineAfterReplace.find(searched);
    while (posOfSearched != -1)
    {
        lineAfterReplace.replace(posOfSearched, searchedLength, replaced);
        posOfSearched = lineAfterReplace.find(searched, posOfSearched + replacedLength);
    }
    return lineAfterReplace;
}

bool IsSpace(char ch)
{
    return ch == ' ';
}

bool IsBlankLine(string str)
{
    return str.empty() || all_of(str.begin(), str.end(), IsSpace);
}