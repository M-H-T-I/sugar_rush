#include "fileHandler.hpp"
#include <fstream>
#include <filesystem>

bool isNumeric(char character){
    return character >= '0' && character <= '9';
}

bool readSaveFile(string path, int store[][8], int& score, int& moves, int level){

    ifstream file(path);
    

    if (!file.is_open()){

        cout << "Error: File did not open for read." << endl;
        return false;


    }else{

        string temp = "";
        
        getline(file, temp);

        if(!isdigit(temp[0]) || !((index - 1) == (int)temp[0] - '0')){
            return false;
        }

        cout << index -1 << endl;
        cout << temp[0] << endl;

        for (int r = 0; r < 8; r++){
            int i = 0;
            getline(file, temp);
            char bracket=temp[0];
            int lengthoftemp=temp.length();
            if(lengthoftemp!=17)return false;
            if(temp == "") return false;
            int num=0;
            for(int c = 0; c < 8; c++){
                
                while ( i < temp.length() && !isNumeric(temp[i])) i++;
                
                if(num<c){
                    store[r][c]=rand()%5+1;
                }
                    
                else{
                    store[r][c] = (temp[i]) - '0';
                }
                num++;
                i++;
                
            }
           

        }

        // reading score
        getline(file, temp);
        int coloPos = temp.find(':');
        if(coloPos!=5)return false;
        string scoreStr = temp.substr(coloPos + 1);
        for(char ch : scoreStr){
            if(!isdigit(ch)) return false;
        }
        int value = stoi(scoreStr);
        score = value;

        // reading moves
        getline(file, temp);
        int colPos = temp.find(':');
        
        if(coloPos!=5)return false;
        string movesStr = temp.substr(colPos + 1);
        
        value = stoi(movesStr);

        moves = value;        

        return true;
    }   


}

bool writeSave(string path, int grid[][8], int score, int moves){

    ofstream wfile(path);

    if(!(wfile.is_open())){
    
        cout << "Error: Could not open file for write." << endl; 
        return false;

    }else{


        wfile << index - 1 << endl;

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

        std::cout<<"Files saved successfully!";

        wfile.close();

        return true;
    }

    
}

bool deleteSave(const string path){
    std::cout<<"File deleted!";
    return filesystem::remove(path);
}
bool savemute(bool muteMusic){
    ofstream mfile("src/save-data/mute.txt");

    if(!(mfile.is_open())){
    
        cout << "Error: Could not open file for write." << endl; 
        return false;

    }else{

        // first the grid
        if(muteMusic){
            mfile << "1" << endl;
        }else{
            mfile << "0" << endl;
        }

        mfile.close();

        return true;
    }
}
bool readmute(bool& muteMusic){

    ifstream mfile("src/save-data/mute.txt");
    

    if (!mfile.is_open()){

        cout << "Error: File did not open for read." << endl;
        return false; 
    }else{

        string temp = "";
        getline(mfile, temp);
        if(temp=="1"){
            muteMusic=true;
        }else if(temp=="0"){
            muteMusic=false;
        }else{
            return false;
        }
        return true;
    }
}

bool readLevel(int& index){


    ifstream file(path);

    if(!file.is_open()){

        cout << "error cold not open file" << endl;
        return false;

    }else {
        string level = "";
        
        if(!getline(file, level) || !isdigit(level[0])){
            return false;
        }

        switch ((int)(level[0] -'0'))
        {
        case 1:
            index = 2;
            break;

        case 2:
            index = 3;
            break;

        case 3:
            index = 4;
            break;

        default:
            return false;
            break;
        }

        return true;

    }

}