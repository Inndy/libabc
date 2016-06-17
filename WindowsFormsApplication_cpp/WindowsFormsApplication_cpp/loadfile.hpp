//#include "matrix.hpp"

#include <fstream>
#include <cstring>
#include <vector>
#include "util.hpp"

#ifndef loadfile_hpp
#define loadfile_hpp

#define MAX_SINGLE_ELEMENT_LENGTH 500

using std::cout;
using std::cerr;
using std::string;
using std::vector;
using std::fstream;
const char NUMBER_CHAR_LIST[] = {'0','1','2','3','4','5','6','7','8','9','.','-'};
bool isNumberChar(char ch);

class LoadFile{
public:
    LoadFile() {}
    LoadFile(const char * address)
    {
        this->address = new char[strlen(address)];
        strcpy(this->address, address);
    }
    ~LoadFile()
    {
//        delete address;
    }
    char * getAddress()
    {
        return address;
    }
    //load matrix file to a matrix array
    Matrix<double> ** load_matrix(int & m_count)
    {
        Matrix<double> ** matrices;
        //check address
        if (strlen(address) == 0) {
            fatal("Empty address captured");
        }
        //filestream initialize
        fstream filestream;
        filestream.open(address, std::ios::in);
        char * temp = new char[MAX_SINGLE_ELEMENT_LENGTH];
    //=======================
        /* read how many matrices in this file */
        //filestream.getline(temp,MAX_SINGLE_ELEMENT_LENGTH,'\n');
		int matrix_count;
		filestream >> matrix_count;
    //=======================
        /* build matrices array */
        matrices = new Matrix<double> *[matrix_count];
        m_count = matrix_count;
    //=======================
        /* read matrix
         * the following loop read one matrix a time
         */
        for (int index = 0; index < matrix_count; index ++) {
            // read and check the 'M' that stand for a matrix
			filestream >> temp;
			cout << "temp" << temp << endl;
            if (!(temp[0] == 'M' || temp[0] == 'm')) {
                fatal("Finding non-matrix element in matrix file");
            }
			int row, column;
            // read the row and column information abount the current matrix
			filestream >> row; filestream >> column;
            // construct current matrix
            matrices[index] = new Matrix<double>(row,column);
            // read the matrix, read one row a time
            for(int row_flag = 0; row_flag < row; row_flag++){
				for (int col_flag = 0; col_flag < column; col_flag++) {
					double element_temp;
					filestream >> element_temp;
					matrices[index]->cell(row_flag, col_flag) = element_temp;
				}
                
            }
        }
        return matrices;
    }
    
    myVecD ** load_vector(int & v_count){
        myVecD ** vectors;
        //check address
        if (strlen(address) == 0) {
            fatal("Empty address captured");
        }
        //filestream initialize
        fstream filestream;
        filestream.open(address, std::ios::in);
        char * temp = new char[MAX_SINGLE_ELEMENT_LENGTH];
        //=======================
        /* read how many matrices in this file */
        filestream.getline(temp,MAX_SINGLE_ELEMENT_LENGTH,'\n');
        v_count = atoi(temp);
		cout << "temp read form file" <<v_count <<endl;
        //=======================
        /* build vector<double> array */
        vectors = new myVecD * [v_count];
        
        
        for (int index = 0; index < v_count; index ++) {
            // read and check the 'V' that stand for a matrix
            filestream.getline(temp, MAX_SINGLE_ELEMENT_LENGTH, '\n');
            
            if (!(temp[0] == 'V' || temp[0] == 'v')) {
                fatal("Finding non-vector element in vector file");
            }
            // read the row and column information abount the current matrix
            filestream.getline(temp, MAX_SINGLE_ELEMENT_LENGTH, '\n');
            int length = atoi(temp);
            // construct current vector
            vectors[index] = new myVecD(length);
            double tmp;
            for (int flag = 0; flag < length; flag++) {
                filestream >> tmp;
                (*vectors[index])[flag] = tmp;
            }
            filestream.getline(temp, MAX_SINGLE_ELEMENT_LENGTH,'\n');
        }
        return vectors;
        
    }
    

    void test()
    {
        Matrix<int> one(3, 3);
        one.one();
        cout << "one: " << one.str() << endl;
        char * add = new char[10];

        cout << "strlen" << strlen(add) << endl;
        delete [] add;
    }
private:
    char * address;
};

bool isNumberChar(char ch)
{
    for(int index = 0; index < 12; index++) {
        if(ch == NUMBER_CHAR_LIST[index])
            return true;
    }
    return false;
}

#endif
