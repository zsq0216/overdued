#include <iostream>
#include <fstream>
#include "FamilyMart.cpp"

// modify this file to test your logics
// TODO 
using namespace std;
int main() {
    FamilyMart *test_mart = new FamilyMart();
    string purchase_file_path = "purchase.txt", sell_file_path = "sell.txt";
    ofstream log_file("log.txt", ios::out);

    log_file << "Today is beginning" << endl;
    test_mart->purchase_file(purchase_file_path);
    test_mart->sell_file(sell_file_path);
    log_file << "This day is over" << endl;
    log_file << "turnover:" << test_mart->show_turnover() << endl;
    
    delete test_mart;
    
    return 0;
}