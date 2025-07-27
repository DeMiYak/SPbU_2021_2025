#include "Parser.h"

/// ����������� ������ ���������������:
/// 
/// ��� ������� ��������:
/// 1. �������� �� ��, ��� � ������ ���������� �������� ���������� �� ���������� ��������.
/// 2. � ������ ���������� ����� ���������, � ����� ������ / ������� ���� ������.
/// 3. ���� �� ���� ������ ������ ����� � ������ ����� ��������.
/// 
/// ������� ������� try... catch ����� �� Parser.cpp � ��������� ������� std::exception � ������ 44 ������ � IO_hometask.cpp
/// �� ����� �� ������ throw ������ try... catch ����.


dataframe Parser::Parse()
{
    ifstream in(filename);
    if (!in.is_open()) {
        throw runtime_error("File not found: " + filename);
    }
    vector<string> headers;
    vector<vector<double>> data;
    errorIndex = { 1, 1 };
    headerSize = 0;
    HeaderParsing(in, headers);
    DataParsing(in, data);
    return make_pair(headers, data);
}

void Parser::HeaderParsing(ifstream& in, vector<string>& headers)
{
    string vs;
    getline(in, vs);
    istringstream iss(vs);
    while (getline(iss, vs, delim)) {
        if (vs == "") {
            //vs = "col" + to_string(count);
            headers.clear();
            throw invalid_argument("Column name is empty in file: " + filename + "\nError occurred at row "
                + to_string(errorIndex.first) + " column " + to_string(errorIndex.second));
        }  
        errorIndex.second++;
        headers.push_back(vs);
    }
    errorIndex.first++;
    errorIndex.second = 1;
    headerSize = headers.size();
}

void Parser::DataParsing(ifstream& in, vector<vector<double>>& data)
{
    string vs;
    while (getline(in, vs)) {
        int count = 0;
        vector<double> values;
        istringstream iss(vs);
        double val;
        while (iss >> val) {
            count++;
            values.push_back(val);
            if (iss.peek() == delim) {
                iss.ignore();
            }
            if (count > headerSize) {
                break;
            }
            errorIndex.second++;
        }
        if (!iss.eof() && iss.fail()) {
            data.clear();
            throw invalid_argument("Failed to read the data from file: " + filename + "\nError occurred at row " 
                + to_string(errorIndex.first) + " column " + to_string(errorIndex.second));
        }
        if (count != headerSize) {
            data.clear();
            throw length_error("Error: incoherent header and data column sizes. Header "
                + to_string(headerSize) + " columns and Data " + to_string(count) + " columns" 
                + "\nError occurred at row "
                + to_string(errorIndex.first) + " column " + to_string(errorIndex.second));
        }
        errorIndex.first++;
        errorIndex.second = 1;
        data.push_back(values);
    }
}
