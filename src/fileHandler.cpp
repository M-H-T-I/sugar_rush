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

        for (int r = 0; r < 8; r++){

            int i = 0;
            getline(file, temp);

            if(temp == "") return false;

            for(int c = 0; c < 8; c++){

                while ( i < temp.length() && !isNumeric(temp[i])) i++;
                store[r][c] = (temp[i]) - '0';
                i++;
                
            }

        }

        // reading score
        getline(file, temp);
        int coloPos = temp.find(':');
        string scoreStr = temp.substr(coloPos + 1);
        int value = stoi(scoreStr);
        score = value;

        // reading moves
        getline(file, temp);
        int colPos = temp.find(':');
        string movesStr = temp.substr(colPos + 1);
        value = stoi(movesStr);

        moves = value;        

        return true;
    }   


}

bool writeSave(string path, int grid[][8], int score, int moves){

    ofstream wfile(path);

    if(!wfile.is_open()){
    
        cout << "Error: Could not open file for write." << endl; 
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

        cout<<"Files saved successfully!";

        wfile.close();

        return true;
    }

    
}

bool deleteSave(const string path){
    cout<<"File deleted!";
    return filesystem::remove(path);
}