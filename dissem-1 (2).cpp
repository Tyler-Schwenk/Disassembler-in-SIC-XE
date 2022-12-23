#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

//function to convert from hex to binary because it couldnt figure out how to do it otherwise
string hexToBin(string hexdec)
{
    long int i = 0;
    string binary;
    while (hexdec[i]) {
 
        switch (hexdec[i]) {
        case '0':
            binary.append("0000");
            break;
        case '1':
            binary.append("0001");
            break;
        case '2':
            binary.append("0010");
            break;
        case '3':
            binary.append("0011");
            break;
        case '4':
            binary.append("0100");
            break;
        case '5':
            binary.append("0101");
            break;
        case '6':
            binary.append("0110");
            break;
        case '7':
            binary.append("0111");
            break;
        case '8':
            binary.append("1000");
            break;
        case '9':
            binary.append("1001");
            break;
        case 'A':
            binary.append("1010");
            break;
        case 'B':
            binary.append("1011");
            break;
        case 'C':
            binary.append("1100");
            break;
        case 'D':
            binary.append("1101");
            break;
        case 'E':
            binary.append("1110");
            break;
        case 'F':
            binary.append("1111");
            break;
        default:
            break;
        }
        i++;
    }
    return binary;
}

int main(int argc, char** argv)
{
    //helpers for opcode conversion
    const static string ops[] = {
        "18", "58", "90", "40", "B4", "28",
        "88", "A0", "24", "64", "9C", "C4",
        "C0", "F4", "3C", "30", "34", "38",
        "48", "00", "68", "50", "70", "08",
        "6C", "74", "04", "D0", "20", "60",
        "98", "C8", "44", "D8", "AC", "4C",
        "A4", "A8", "F0", "EC", "0C", "78",
        "54", "80", "D4", "14", "7C", "E8",
        "84", "10", "1C", "5C", "94", "B0",
        "E0", "F8", "2C", "B8", "DC"
    };                                                             
    const static string mnemonics[] = {
        "ADD", "ADDF", "ADDR", "AND", "CLEAR", "COMP",
        "COMPF", "COMPR", "DIV", "DIVF", "DIVR", "FIX",
        "FLOAT", "HIO", "J", "JEQ", "JGT", "JLT",
        "JSUB", "LDA", "LDB", "LDCH", "LDF", "LDL",
        "LDS", "LDT", "LDX", "LPS", "MUL", "MULF",
        "MULR", "NORM", "OR", "RD", "RMO", "RSUB",
        "SHIFTL", "SHIFTR", "SIO", "SSK", "STA", "STB",
        "STCH", "STF", "STI", "STL","STS", "STSW",
        "STT", "STX", "SUB", "SUBF", "SUBR", "SVC",
        "TD", "TIO", "TIX", "TIXR", "WD"
    };
    const static string formatTwo[] = {
        "90", "4", "A0", "9C", "98", "AC", "A4", "A8", 
        "94", "B0", "B8"
    };

    //exit if no input file is given
    if(argc == 1){
        cout << "missing the input file";
        exit(0);
    }
    ifstream file; 
    file.open(argv[1]);
    //for testing 
    // ifstream file; 
    // file.open("/home/tyler/projects/helloworld/test2.obj");
    string myString;
    string startAdress;
    int i;
    string len;
    int length;
    unsigned opBin;
    string currentSS;
    string curr;
    string finalOp;
    string opHex;
    string opCode;
    string instrHex;
    unsigned instrBin;
    string instrStr;
    bool formTwo;
    string ni;
    int op;
    ofstream outFile("obj_struct.txt");

    //prints out our header for the file
    vector<string> msg {"INSTR           ", "FORMAT          ", "OAT             ", "TAAM            ", "OBJ             "};
    for (const string& word : msg){
        outFile << word;
        }
    outFile << "\n";    

    //begin reading in file and preforming conversion
    if ( file.is_open() ) {  

         while ( file.good() ) {
            file >> myString;
            
            if (myString[0] == 'T'){                    //finds the row of information we wish to translate

                startAdress = myString.substr(1,6);     //this is the given start address
                // len = myString.substr(7,2);
                // istringstream iss(len);                  //this code was used to find the length of the hex insructions based on the length 
                // iss >> hex >> length;                    //given by the T-instruction but our tast code had the wrong length
                // length = length * 2;                //amount of hex values is double the amount of bytes      
                length = myString.length();
                i = 9;

                while (i<length){                           //runs our conversions for each hex code given, 0x000000 at a time
                    curr = myString.substr(i,3);            //take the next 3 digit hex code and store in curr to allow us to see opcode and nixbpe

                    //take the first two digits of curr and apply mask to find opcode
                    opHex = curr.substr(0,2);
                    formTwo = false;
                    for (int m = 0; m < 11; m++){
                        if (opHex == formatTwo[m]){
                            formTwo = true;
                        }
                    }
                    uint16_t current = stoi(opHex,0,16);
                    uint16_t opHexReal = current & 0xFC;
                    stringstream ss;
                    ss << hex << opHexReal;
                    finalOp = ss.str();
                    if (finalOp.length() == 1){
                        finalOp.insert(0,"0");
                    }
                    transform(finalOp.begin(), finalOp.end(),finalOp.begin(), ::toupper);
                    
                    //find correct opcode and output it with additionl spaces
                    for(int k = 0 ; k < 58 ; k++){ 
		                if(ops[k] == finalOp){
                            opCode = mnemonics[k];
			                outFile  << opCode;
		                }
	                }                   
                    outFile << "             ";
                    

                    //determine if instruction is type 2, 3 or 4 based off opcode and e in nixbpe                    
                    if (formTwo){
                        outFile << "2               ";
                    }                    
                    else{
                        instrHex = curr.substr(2,1);
                        instrStr = hexToBin(instrHex);
                        if (instrStr.substr(3,1)=="1"){
                            outFile << "4               ";
                        }
                        else{
                            outFile << "3               ";
                        }
                    }
                    

                    //determine operand addressing type based off n and i in nixbpe
                    if (!formTwo){
                        ni = hexToBin(curr).substr(6,2);
                        if (ni == "11"){
                            outFile << "simple          ";
                        }
                        else if(ni == "10"){
                            outFile << "indirect        ";
                        }
                        else{                       //ni must be "01", as "00" is only used in SIC
                            outFile << "immediate       ";
                        }
                    }

                    //determine target address addressing mode based off b and p in nixbpe
                    if (!formTwo){
                        if (instrStr.substr(1,2) == "10"){
                            if (instrStr.substr(0,1) == "1"){
                                outFile << "base_indexed    ";
                            }else{
                                outFile << "base            ";
                            }
                        }
                        else if (instrStr.substr(1,2) == "01"){
                            if (instrStr.substr(0,1) == "1"){
                                outFile << "pc_indexed      ";
                            }else{
                                outFile << "pc              ";
                            }
                        }
                        else{
                            if (instrStr.substr(0,1) == "1"){
                                outFile << "absolute_indexed";
                            }else{
                                outFile << "absolute        ";
                            }
                        }
                    }

                    //print object code
                    if (formTwo){
                        outFile << "                                " << myString.substr(i,4) << "\n";
                        i+= 4;
                    }
                    if (!formTwo){
                        if (instrStr.substr(3,1)=="1"){
                            outFile << myString.substr(i,8) << "\n";
                            i+= 8;
                        }
                        else{
                            outFile << myString.substr(i,6) << "\n";
                            i+= 6;
                        }               
                    }
                    
                    }
                }            
            }
        }
   outFile << endl;

// for testing code
//    ifstream f("obj_struct.txt");
//     if (f.is_open())
//         cout << f.rdbuf();

   outFile.close();
}