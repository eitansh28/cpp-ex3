#include "Matrix.hpp"
#include <string>

using namespace std;

namespace zich{

    int Matrix::sumMat(const Matrix &curr, const Matrix &other){
        int whoIsBigger=0;
        double count1=0;
        double count2=0;
        for(unsigned int i=0;i<curr.row;i++){
            for(unsigned int j=0;j<curr.col;j++){
                count1+=curr.myMatrix.at((i*curr.col)+j);
                count2+=other.myMatrix.at((i*curr.col)+j);
            }
        }
        if(count1>count2){
            whoIsBigger=1;
        }
        if(count1<count2){
            whoIsBigger=2;
        }
        return whoIsBigger;
    }
    
    Matrix::Matrix(const vector<double> &init, int rows, int cols){
        if(rows<0 || cols<0){
            throw invalid_argument{"rows or cols can't be negative"};
        }
        if(init.size()!=rows*cols){
            throw invalid_argument{"cant turn this vec to matrix on this size"};
        }
        this->row=(unsigned int)rows;
        this->col=(unsigned int)cols;
        this->myMatrix=init;
    }
    // Matrix::~Matrix(){

    // }
    Matrix Matrix::operator+(Matrix& first){
        if(this->row!= first.row || this->col!= first.col){
            throw invalid_argument{"Matrixes not in same size"};
        }
        Matrix plus(this->myMatrix,(int)this->row, (int)this->col);
        for(unsigned int i=0;i<first.row;i++){
            for(unsigned int j=0;j<first.col;j++){
                plus.myMatrix.at((i*first.col)+j)+=first.myMatrix.at((i*first.col)+j);//+second.myMatrix.at((i*first.col)+j);
            }
        }return plus;
    }

    Matrix Matrix::operator+=(const Matrix &other){
        if(this->row!= other.row || this->col!= other.col){
            throw invalid_argument{"Matrixes not in same size"};
        }
        for(unsigned int i=0;i<this->row;i++){
            for(unsigned j=0;j<this->col;j++){
                this->myMatrix.at((i*other.col)+j)+=other.myMatrix.at((i*other.col)+j);
            }
        }return *this;
    }
    
    Matrix Matrix::operator+(){
        Matrix copy(this->myMatrix,(int)this->row, (int)this->col);
        return copy;
    }
    
    Matrix Matrix::operator-(Matrix& sec){
        if(this->row!= sec.row || this->col!= sec.col){
            throw invalid_argument{"Matrixes not in same size"};
        }
        Matrix minus(this->myMatrix,(int)this->row, (int)this->col);
        for(unsigned int i=0;i<sec.row;i++){
            for(unsigned int j=0;j<sec.col;j++){
                minus.myMatrix.at((i*sec.col)+j)-=sec.myMatrix.at((i*sec.col)+j);
            }
        }return minus;
    }

    Matrix Matrix::operator-=(const Matrix &other){
        if(this->row!= other.row || this->col!= other.col){
            throw invalid_argument{"Matrixes not in same size"};
        }
        for(unsigned int i=0;i<this->row;i++){
            for(unsigned int j=0;j<this->col;j++){
                this->myMatrix.at((i*other.col)+j)-=other.myMatrix.at((i*other.col)+j);
            }
        }return *this;
    }

    Matrix Matrix::operator-(){
        Matrix minUnar(this->myMatrix,(int)this->row, (int)this->col);
        return minUnar*=(-1);
    }
    
    bool Matrix::operator>(const Matrix &other)const{
        if(other.row!= this->row || other.col!= this->col){
            throw invalid_argument{"Matrixes not in same size"};
        }
        return sumMat(*this,other)==1;
    }
    
    bool Matrix::operator>=(const Matrix &other)const{
        if(other.row!= this->row || other.col!= this->col){
            throw invalid_argument{"Matrixes not in same size"};
        }
        return sumMat(*this,other)==0 || sumMat(*this,other)==1;
    }
    
    bool Matrix::operator<(const Matrix &other)const{
        return !(*this>=other);
    }
    
    bool Matrix::operator<=(const Matrix &other)const{
        return !(*this>other);
    }
    
    bool Matrix::operator==(const Matrix &other){
        if(other.row!= this->row || other.col!= this->col){
            throw invalid_argument{"Matrixes not in same size"};
        }
        bool equ=true;
        for(unsigned int i=0;i<this->row;i++){
            for(unsigned int j=0;j<this->col;j++){
                if(this->myMatrix.at((i*other.col)+j)!=other.myMatrix.at((i*other.col)+j)){
                    equ=false;
                    break;
                }   
            }
        }return equ;
    }
    
    bool operator==(const Matrix &first, const Matrix &second){
        if(first.row!= second.row || first.col!= second.col){
            throw invalid_argument{"Matrixes not in same size"};
        }
        bool equ=true;
        for(unsigned int i=0;i<first.row;i++){
            for(unsigned int j=0;j<first.col;j++){
                if(first.myMatrix.at((i*first.col)+j)!=second.myMatrix.at((i*second.col)+j)){
                    equ=false;
                    break;
                }   
            }
        }return equ;
    }
    bool Matrix::operator!=(const Matrix &other){
        return(!(*this==other));
    }
    
    Matrix& Matrix::operator++(){
        for(unsigned int i=0;i<this->row;i++){
            for(unsigned int j=0;j<this->col;j++){
                (this->myMatrix.at((i*this->col)+j))++;
            }
        }return *this;
    }
    
    Matrix Matrix::operator++(int){
        Matrix copy(this->myMatrix,(int)this->row, (int)this->col);
        for(unsigned int i=0;i<this->row;i++){
            for(unsigned int j=0;j<this->col;j++){
                (this->myMatrix.at((i*this->col)+j))++;
            }
        }return copy;
    }

    Matrix& Matrix::operator--(){
        for(unsigned int i=0;i<this->row;i++){
            for(unsigned int j=0;j<this->col;j++){
                (this->myMatrix.at((i*this->col)+j))--;
            }
        }return *this;
    }
    
    Matrix Matrix::operator--(int){
        Matrix copy(this->myMatrix,(int)this->row, (int)this->col);
        for(unsigned int i=0;i<this->row;i++){
            for(unsigned int j=0;j<this->col;j++){
                (this->myMatrix.at((i*this->col)+j))--;
            }
        }return copy;
    }

    
    Matrix Matrix::operator*(const Matrix &other){
        if(this->col != other.row){
            throw invalid_argument{"can't mult that matrixes"};
        }
        vector<double>vect(this->row*other.col,0);
        for(unsigned int i=0;i<this->row;i++){
            for(unsigned int j=0;j<other.col;j++){
                for(unsigned int k=0;k<this->col;k++){
                    vect.at(i*(other.col)+j)+=(this->myMatrix.at(i*(this->col)+k)*other.myMatrix.at(k*(other.col)+j));
                }
            }
        }
        Matrix mult(vect,(int)this->row, (int)other.col);
        return mult;
    }
    
    Matrix Matrix::operator*=(const Matrix &other){
        *this=(*this*other);
        return *this;
    }
    
    Matrix& Matrix::operator*=(double num){
        for(unsigned int i=0;i<this->row;i++){
            for(unsigned int j=0;j<this->col;j++){
                if(this->myMatrix.at((i*this->col)+j)!=0){
                    (this->myMatrix.at((i*this->col)+j))*=num;
                }  
            }
        }return *this;
    }
    
    Matrix Matrix::operator*(double num){
        Matrix mult(this->myMatrix,(int)this->row, (int)this->col);
        for(unsigned int i=0;i<mult.row;i++){
            for(unsigned int j=0;j<mult.col;j++){
                if(mult.myMatrix.at((i*mult.col)+j)!=0){
                    (mult.myMatrix.at((i*mult.col)+j))*=num;
                }  
            }
        }return mult;
    }
    Matrix operator*(double num ,Matrix &mat){
        Matrix multScalar(mat.myMatrix,(int)mat.row,(int)mat.col);
        for(unsigned int i=0;i<mat.row;i++){
            for(unsigned int j=0;j<mat.col;j++){
                (multScalar.myMatrix.at((i*mat.col)+j))*=num;
            }
        }return multScalar;
    }
    
    ostream& operator<<(std::ostream& output, const Matrix& m){
        for(unsigned int i=0;i<m.row;i++){
            output<<"[";
            for(unsigned int j=0;j<m.col;j++){
                output<<m.myMatrix.at(i*(m.col)+j);
                if(j<m.col-1){
                    output<<" ";
                }
            }
        output<<"]";
        if(i!=m.row-1){
            output<<endl;
        }
        }return output;
    }


    istream& operator>> (std::istream& input , Matrix& m){
    char singelchar = 0;
    string allInput;
    while (singelchar != '\n'){
        singelchar = input.get();
        allInput += singelchar;
    }
    vector<double>init;
    unsigned int countrow=0;
    unsigned int countcol=0;
    unsigned int j=0;
    for(unsigned int i=0;i<(int)allInput.length();i++){
        if(allInput[i]=='[' && (allInput[i+1]<48 || allInput[i+1]>57)){
            throw invalid_argument("wrong input");
        }
        if(allInput[i]==',' && allInput[i+1]!=' '){
            throw invalid_argument("wrong input");
        }
        if(allInput[i]==']' && (allInput[i+1]!=',' && allInput[i+1]!='\n')){
            throw invalid_argument("wrong input");
        }
        if(allInput[i]==']'){
            countrow++;
        }       
    }
    for(unsigned int i=1;i<(int)allInput.length();i++){
        if(allInput[i]!=']' && allInput[i]!=' '){
            countcol++;
        }
        if(allInput[i]==']'){
            break;
        }
    }
    unsigned long pos = 1;
    unsigned int i = 0;  
    string token1;
    
    while (( pos = allInput.find (" ")) != std::string::npos)  
    {  
    token1 = allInput.substr(0, pos);
    if(token1!="]" || token1!="," ){
        m.myMatrix.at(i)=24.4;
    }   
    allInput.erase(0, pos + 1);  /* erase() function store the current positon and move to next token. */   
    }  
        m.row=countrow;
        m.col=countcol;
        return input;
    }
}
    

