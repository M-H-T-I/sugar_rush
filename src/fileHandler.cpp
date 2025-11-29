#include "fileHandler.hpp"
#include "common.hpp"
#include <fstream>
#include <filesystem>

bool createUser(){

    ofstream file("src/save-data/user-info.txt");

    if(file.is_open()){

        file << "tutorial: " << false << endl;
        file << "1: " << false << endl;
        file << "2: " << false << endl;
        file << "3: " << false << endl;

        file.close();

        return true;

    }else {
        cout << "Error: could not open file for writing." << endl;
        return false;
    }


}

bool deleteUser(){

    if (filesystem::remove("src/save-data/user-info.txt")){

        cout << "File deleted successfully." << endl;
        return true;

    }else {

        cout << "File could not be found." << endl;
        return false;

    }
    

}

bool fetchUserData(string levelStatus[]){

    // opening file
    ifstream file("src/save-data/user-info.txt");

    if (!file.is_open()){

        cout << "Could not open file reading." << endl;
        return false;

    }else {

        string temp;
        int i = 0;

        while(getline(file, temp)){

            size_t pos = temp.find(": ");
            levelStatus[i] = (temp.substr(pos+2));
            i++;

        }

        return true;

    }

}