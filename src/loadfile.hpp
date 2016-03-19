//#include "matrix.hpp"

#include <fstream>
#include <cstring>
#include <vector>

#define MAX_SINGLE_ELEMENT_LENGTH 500

using namespace std;
const char NUMBER_CHAR_LIST[] = {'0','1','2','3','4','5','6','7','8','9','.','-'};
bool isNumberChar(char ch);

class LoadFile{
public:
    LoadFile(){}
    LoadFile(const char * address){
        this->address = new char[strlen(address)];
        strcpy(this->address, address);
    }
    ~LoadFile(){
        delete address;
    }
    char * getAddress(){
        return address;
    }
    //load matrix file to a matrix array
    Matrix<double> ** load_matrix(){
        Matrix<double> ** matrices;
        //check address
        if (strlen(address) == 0) {
            fatal("Empty address captured");
        }
        //filestream initialize
        fstream filestream;
        filestream.open(address, ios::in);
        char * temp = new char[MAX_SINGLE_ELEMENT_LENGTH];
    //=======================
        /* read how many matrices in this file */
        filestream.getline(temp,MAX_SINGLE_ELEMENT_LENGTH,'\n');
        int matrix_count = atoi(temp);
    //=======================
        /* build matrices array */
        matrices = new Matrix<double> *[matrix_count];
    //=======================
        /* read matrix
         * the following loop read one matrix a time
         */
        for (int index = 0; index < matrix_count; index ++) {
            // read and check the 'M' that stand for a matrix
            filestream.getline(temp, MAX_SINGLE_ELEMENT_LENGTH, '\n');

            if (!(temp[0] == 'M' || temp[0] == 'm')) {
                fatal("Finding non-matrix element in matrix file");
            }
            // read the row and column information abount the current matrix
            filestream.getline(temp, MAX_SINGLE_ELEMENT_LENGTH, ' ');
            int row = atoi(temp);
            filestream.getline(temp, MAX_SINGLE_ELEMENT_LENGTH, '\n');
            int column = atoi(temp);
            // construct current matrix
            matrices[index] = new Matrix<double>(row,column);
            // read the matrix, read one row a time
            for(int row_flag = 0; row_flag < row; row_flag++){
                filestream.getline(temp, MAX_SINGLE_ELEMENT_LENGTH,'\n');
                bool flag = false;//new data avaliable when true
                vector<char> v;
                int column_flag = 0;
                for (int count = 0; count < strlen(temp)+1; count ++) {
                    if(isNumberChar(temp[count])){
                        flag = true;
                        v.push_back(temp[count]);
                    }
                    if(((!isNumberChar(temp[count])) || count == strlen(temp)) && flag){
                        flag = false;
                        char tempb[v.size()+1];
                        for (int convert_index = 0; convert_index < v.size(); convert_index++) {
                            tempb[convert_index] = v[convert_index];
                        }
                        tempb[v.size()] = '\0';
                        matrices[index]->cell(row_flag,column_flag) = atof(tempb);
                        column_flag++;
                        v.clear();
                    }
                }
            }
        }
        
        delete temp;
        return matrices;
    }
    
    void test(){
        auto one = Matrix<int>::one(3, 3);
        cout << "one: " << one->str() << endl;
        char * add = new char[10];
        
        cout << "strlen" << strlen(add) << endl;
        delete add;
        delete one;
    }
private:
    char * address;
};

bool isNumberChar(char ch){
    for(int index = 0; index < 12; index++){
        if(ch == NUMBER_CHAR_LIST[index])
            return true;
    }
    return false;
}