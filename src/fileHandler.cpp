#include "fileHandler.hpp"
#include <fstream>
#include <filesystem>

bool isNumeric(char character){
    return character >= '0' && character <= '9';
}

bool readSaveFile(string path, int store[][8], int& score, int& moves){

    ifstream file(path);
    

    if (!file.is_open()){

        cout << "Error: File did not open for read." << endl;
        return false;


    }else{

        string temp = "";

            // ---------- READ GRID ----------
    int r = 0;

    if (!getline(file, temp) || temp.empty()) return false;

    while (!temp.empty() && temp[0] == '[') {

        if (r >= 8) return false;  // too many rows

        int c = 0;
        int i = 0;

        while (i < (int)temp.size() && temp[i] != ']') {

            // skipPING sara non-digits
            while (i < (int)temp.size() && !isdigit(temp[i])) i++;
            if (i >= (int)temp.size() || temp[i] == ']') break;

            if (c >= 8) return false; // too many columns

            store[r][c] = temp[i] - '0';
            i++;
            c++;
        }

        if (c != 8) return false; // not enough columns

        r++;

        if (!getline(file, temp) || temp.empty()) return false;

        }

        if (r != 8) return false; // not 8 rows

        // reading score
        if(!getline(file, temp)) return false;
        if(temp.empty()) return false;
        
        int coloPos = temp.find(':');
        if (coloPos == -1) return false; // 
        string scoreStr = temp.substr(coloPos + 1);

            // validate scoreStr contains only digits
        if (scoreStr.empty()) return false;

        for (char ch : scoreStr) {
            if (!isNumeric(ch)) return false;
        }


        int value = stoi(scoreStr);
        score = value;

        // reading moves
        getline(file, temp);
        int colPos = temp.find(':');
        if (colPos == -1) return false;
        string movesStr = temp.substr(colPos + 1);

        if(movesStr.empty())return false;
        for(char ch: movesStr){

            if(!isNumeric(ch)){
                return false;
            }

        }

        value = stoi(movesStr);

        moves = value;        
        //

        return true;
        
    }   


}

bool writeSave(string path, int grid[][8], int score, int moves){

    ofstream wfile(path);

    if(!wfile.is_open()){
    
        cout << "Error: Could not open file for write." << endl;
        cout << "Path does not exist" << endl; 
        return false;

    }else{

        // first the grid
        for (int r = 0; r < 8; r++){

            wfile << '[';
            for (int c = 0; c < 8-1; c++){

                wfile << grid[r][c] << ",";

            }   

            wfile << grid[r][1];

            wfile <<']' << endl;

        }

        //score
        wfile << "score:" << score << endl;

        //moves;
        wfile << "moves:" << moves << endl;

        cout<<"Files saved successfully!" << endl;

        wfile.close();

        return true;
    }

    
}

bool deleteSave(const string path){
    cout<<"File deleted!" << endl;
    return filesystem::remove(path);
}