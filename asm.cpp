#include <fstream>
#include <iostream>
#include <sstream> // used for std::stringstream and std::ostringstream
#include <iomanip> // used for std::setw() and std::setfill
#include <string>
#include <vector>
#include <cstdint> //! used for uint32_t type - NEED TO CHANGE WHOLE THING TO <cstdint>
#include <unordered_map> // used for converting register names
#include <algorithm> // for replace
#include <iomanip> // for std::hex - however it seemed to work without it.


/*
* Parse the input.s file and return a vector of strings, each string a line of the program
* @param filepath relative filepath to file
* @return vector of strings, each string is a line of the program.
*/
std::vector<std::string> parse_file(const std::string& filepath){

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

/*
* Convert RISC-V register in conventional names as strings to bit patterns
* @param reg std::string of the register name.
* @return std::uint32_t, the corresponding register number
*/
std::uint32_t reg_to_bits(const std::string& reg){
    static const std::unordered_map<std::string, std::uint32_t> table = {
        {"zero", 0b00000}, 
        {"ra", 0b00001}, 
        {"sp", 0b00010}, 
        {"gp", 0b00011},
        {"tp", 0b00100},
        {"t0", 0b00101},
        {"t1", 0b00110},
        {"t2", 0b00111},
        {"s0", 0b01000}, 
        {"s1", 0b01001},
        {"a0", 0b01010},
        {"a1", 0b01011},
        {"a2", 0b01100},
        {"a3", 0b01101},
        {"a4", 0b01110},
        {"a5", 0b01111},
        {"a6", 0b10000}, 
        {"a7", 0b10001}, 
        {"s2", 0b10010}, 
        {"s3", 0b10011},
        {"s4", 0b10100},
        {"s5", 0b10101},
        {"s6", 0b10110},
        {"s7", 0b10111},
        {"s8", 0b11000}, 
        {"s9", 0b11001},
        {"s10", 0b11010},
        {"s11", 0b11011},
        {"t3", 0b11100},
        {"t4", 0b11101},
        {"t5", 0b11110},
        {"t6", 0b11111}};
    auto op = table.find(reg);
    //some error from GPT that I don't know about
    if (op == table.end()) {
        throw std::invalid_argument("Unknown register value.");
    }
    return op->second; // second gives the actual value of the key-value pair

}


/*
* Convert immediate string to bits
* @param imm std::string immediate value
* @return std::uint32_t
*/
std::uint32_t imm_to_bits(const std::string& imm){
    // convert immediates of all types (decimal, hex, and binary) to uint32_t. '
    // for now, it just does decimal
    std::uint32_t result = stoi(imm);
    // have some error handling? maybe
    return result;  
    
}

/*
* Convert std::uint32_t to a formatted string ready to be written.
* @param input std::uint32_t, the instruction machine-code
* @return std::string in the 0xABCD1234 format to be written to output file.
*/
std::string hexify(std::uint32_t input){
    std::ostringstream out; 
    out<<"0x";
    out<<std::hex<<std::uppercase; //set some formatting
    out<<std::setw(8)<<std::setfill('0'); //sets width and the filler character
    out<<input; 
    return out.str();  
}

/*
* Write an instruction to inputs/file_name
* @param instruction std::string with the hex-formatted instruction
* @param out_filepath std::string which filepath to which the instruction will be added to.
*/
bool write_out(std::string instruction, std::string out_filepath){
    std::ofstream output(out_filepath, std::ios::app); // open in append mode, so that stuff doesn't get overwritten
    if (!output) return false; // there was some problem reading the file
    output << instruction<<std::endl; 
    // we don't even need output.close(), as the file automatically closes when we go out of scope.
    return static_cast<bool>(output); // will be true if things went well.
}


int main(int argc, char *argv[]){
    // check that that a test filepath was given
    // unit testing reg_to_bit

    if (argc < 2){
        std::cerr<<"Correct format is ./asm input.s output.txt.\nExiting assembler program."<<std::endl; 
        return 1; 
    }

    std::string filename = argv[1]; // need to convert char* to string
    std::string in_filepath = "inputs/" + filename + ".s";  // argv[1] should 

    std::vector<std::string> program = parse_file(in_filepath); 
    if (program.size() == 0){ // this is the case where nothing got loaded into the program vector
        return 1; 
    }


    //* before writing the new instructions, clear the file if it exists
    std::string out_filepath = "inputs/" + filename + ".txt";
    std::ofstream my_file(out_filepath);
    my_file<<""; //basically empty?
    my_file.close(); 

    //* main loop - going line-by-line of the program
    for (std::string& line: program){

        std::vector<std::string> words; // vector of words in a given instruction
        std::string word; 
        // first let's put the line into a vector of words
        std::replace(line.begin(), line.end(), ',', ' '); // replace the commas with spaces 
        std::istringstream my_stream(line);// how does this stuff actually work? 
        // even more basic question: What is a stream and what is << ? maybe questions for later
        while (my_stream>>word){
            words.push_back(word); 
        }

        std::string instr = words[0]; 
        std::string finished_instruction; 
        std::uint32_t  opcode {}; 

        if (instr=="addi"){ //* addi rd, rs, imm12
            // the rd and rs registers need to be turned into bits
            // then the imm12 needs to be turned into bits
            // then concatenate all
            std::uint32_t rd = reg_to_bits(words[1]); 
            std::uint32_t rs = reg_to_bits(words[2]); 
            std::uint32_t imm12 = imm_to_bits(words[3]); 
            opcode = imm12 <<20 | rs<<15 | 0b000 <<12 | rd<<7| 0b0010011;
            finished_instruction = hexify(opcode); 
        }

        else if (instr=="add"){

        }

        else if (instr == "and"){

        }


        else if (instr == "or"){

        }


        else if (instr == "sll"){

        }


        else if (instr == "srl"){

        }

        
        else if (instr == "beq"){

        }

        std::cout<<finished_instruction<<"\n";
        write_out(finished_instruction, out_filepath); //! note t1.txt is hardcoded


        }
    
    return 0; 
}