#include "Matrix.h"
int main(){
Matrix A(2);
Matrix B;
A.Input();
A.Print();
B=A;
cout<<endl<<" -----------------------"<<endl;
B.Print();
}