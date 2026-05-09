/**************************************
 * To calculate the joint angles of a robotic arm, you need a highly optimized matrix math library.
1. Create a `Matrix` class with dynamic memory allocation for a 2D array of `double` (using `double** data`), along with `rows` and `cols` as integers.
2. Implement a parameterised constructor with default arguments (`Matrix(int r = 3, int c = 3)`).
3. Implement a **Deep Copy Constructor** to prevent shallow copy issues when matrices are passed by value.
4. Overload the binary `+` operator using a member function to add two matrices. Throw a string exception `"DimensionMismatch"` if rows/cols don't align.
5. Overload the `<<` operator using a **Friend Function** to easily print the matrix to the console.
6. Write the Destructor to safely deallocate the 2D array.
****************************************/

#include <iostream>
using namespace std;

class Matrix{
    private:
        int rows, cols;
        double** data = new double*[rows];
    public:
        Matrix(int r=3 , int c = 3): rows(r), cols(c){
            for(int i = 0; i < rows; ++i)
                data[i] = new double[cols];

        }

        Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
            data = new double*[rows];
            for (int i = 0; i < rows; ++i) {
                data[i] = new double[cols];
                for (int j = 0; j < cols; j++)
                    data[i][j] = other.data[i][j];
            }
        }

        void setData(){
            for(int i = 0 ; i < rows ; i++){
                for(int j = 0 ; j < cols ; j++){
                        cout<<"Enter element ("<<i+1<<", "<<j+1<<"): ";
                        cin>>data[i][j];
                }
            }
        }

        Matrix& operator + (const Matrix& matrix){
            if(this->rows != matrix.rows || this->cols != matrix.cols)
                throw "Dimensions Mismatch!";

            Matrix temp( matrix.rows, matrix.cols);
            for(int i = 0 ; i < rows ; i++){
                for(int j = 0 ; j < cols ; j++){
                        temp.data[i][j] = this->data[i][j] + matrix.data[i][j] ; 
                }
            }
            return temp;
        }

        friend ostream& operator << (ostream& , const Matrix&);

        ~Matrix(){
            for(int i = 0; i < rows; ++i)
                delete data[i] ;
            delete[] data;
            cout<<"> Destroyed matrix data!\n";
        }

};

ostream& operator << (ostream& stream , const Matrix& matrix){
    for(int i = 0 ; i < matrix.rows ; i++){
        for(int j = 0 ; j < matrix.cols ; j++){
            stream << matrix.data[i][j] <<" ";
        }

        cout << endl;
    }
    
    return stream;
}

int main(){
    Matrix matrix1(2,3), matrix2;
    matrix1.setData();
    matrix2.setData();

    try{
        Matrix matrix3 = matrix1 + matrix2;
        cout << matrix3;
    }
    catch(const char* e){
        cout<<e<<endl;
    }


    return 0;
}