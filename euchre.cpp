#include <iostream>
#include <fstream>
#include "Player.hpp"
#include "Card.hpp"
#include "Pack.hpp"
#include <cassert>
#include <sstream>
#include <algorithm>
#include <vector>
#include <array>
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 12){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return 1;
    }
    int ptw = atoi(argv[3]);
    if (ptw < 1 || ptw > 100){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return 1;
    }
    string shuff = argv[2];
    if (shuff != "shuffle" && shuff != "noshuffle"){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return 1;
    }
    string top1 = argv[5];
    string top2 = argv[7];
    string top3 = argv[9];
    string top4 = argv[11];
    if (top1 != "Simple" && top1 != "Human"){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return 1;
    }
    if (top2 != "Simple" && top2 != "Human"){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return 1;
    }
    if (top3 != "Simple" && top3 != "Human"){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;

     return 1;
    }
    if (top4 != "Simple" && top4 != "Human"){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return 1;
    }
     string pack_file = argv[1];
     ifstream fin(pack_file);
    if (!(fin.is_open())) {
        cout << "Error opening " << pack_file << endl;
        return 1;
    }
}