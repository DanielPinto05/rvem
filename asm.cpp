#include <fstream>
#include <iostream>
#include <sstream> // used for splitting strings
#include <string>
#include <vector>


std::vector<std::string> parse_file(std::string filepath){
    // given a filepath for an assembly file, return a vector of strings with each string
    // being a line of the program
    // nice because it handles opening and closing of file forus and it tucked away

    std::ifstream file(filepath); // opens the file 

    std::vector<std::string> program; // stores the line-by-line strings as a series of vectors

    if (!file.is_open()){
        std::cerr << "Error opening file.\nExiting assembler program"<<std::endl; 
        return program; 
    }

    std::string line; // read the file line by line 
    while(std::getline(file, line)){ // fill line with the next line of assembly 
        program.push_back(line);  //add the line to the program vector
    }
   
    file.close(); 
    return program; 

}



int main(int argc, char *argv[]){
    //* NEXT GOAL: read the first word by itself

    // check that that a test filepath was given
    if (argc < 2){
        std::cerr<<"No input file specified.\nExiting assembler program."<<std::endl; 
        return 1; 
    }

    std::string filename = argv[1]; // need to convert char* to string
    std::string filepath = "inputs/" + filename;  // argv[1] should 

    std::vector<std::string> program = parse_file(filepath); 
    if (program.size() == 0){
        return 1; 
    }

    // go line by line and print out word by word inside the line. 
    for (const std::string&line: program){
       std::vector<std::string> words;
       std::istringstream stream(line); 
       std::string word; 

       while (stream>>word){
        words.push_back(word); 
       }

       std::string instruction = words[0]; 
       if (instruction == "addi"){
        std::cout<<"Got the instruction!\n"; 
       }

       
    }

    
    return 0; 
}