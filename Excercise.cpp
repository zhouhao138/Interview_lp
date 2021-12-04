#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>


#include <unordered_map>

using namespace std;

int Exercise(int argc, char **argv){

    //check_args(argc, argv);

    /* Store input and output files' name */
    char input_filename[80];
    char output_filename[80];
    /* Create file handle for input and output */
    fstream fin;
    fstream fout;

    sprintf(input_filename, "./%s", argv[1]);
    sprintf(output_filename, "./%s", argv[2]);

    fin.open(input_filename, fstream::in);

    //Every symbol infomation
    //symbol_info symbol -> last timestamp, max_gap, total vol, total price, max_price
    unordered_map<string, vector<int>> symbol_info;
    vector<string> symbol_list;

    //read the csv file as a string vector
    vector<string> row;
    string symbol, temp;
    int timestamp, quantity, price;

    while (getline(fin, temp, ',')) {
        timestamp = stoi(temp);

        getline(fin, symbol, ',');

        getline(fin, temp, ',');
        quantity = stoi(temp);

        getline(fin, temp);
        price = stoi(temp);

        if( symbol_info.find( symbol) != symbol_info.end() ){
            symbol_info[symbol][1] = max(int(symbol_info[symbol][1]), timestamp - symbol_info[symbol][0]);
            symbol_info[symbol][0] = timestamp;
            symbol_info[symbol][2] += quantity;
            symbol_info[symbol][3] += price * quantity;
            symbol_info[symbol][4] = max(int(symbol_info[symbol][4]), price);
        }
        else{
            symbol_list.push_back(symbol);
            symbol_info.emplace(symbol, vector<int>{timestamp, 0, quantity, quantity * price, price});
        }
    }

    sort(symbol_list.begin(), symbol_list.end());

    fout.open(output_filename, fstream::out);
    for(auto s: symbol_list){
        fout << s << ',';
        fout << symbol_info[s][1] << ',';
        fout << symbol_info[s][2] << ',';
        fout << symbol_info[s][3] / symbol_info[s][2] << ',';
        fout << symbol_info[s][4] << endl;
    }
    fout.close();
    
    return 1;
}



int main(int argc, char **argv){

    return Exercise(argc, argv);

}
