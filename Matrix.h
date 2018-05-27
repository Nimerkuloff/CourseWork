
#include <iostream>

const int DEFAULT_SIZE = 10;
using namespace std;

class Matrix {
    int itsNumberOfRows;
    int itsNumberOfColumns;

    int *itsRows;
    int *itsCols;
    int *itsValues;
    int itsLength;



public:

    explicit Matrix(int);
    Matrix(const Matrix &original);

    Matrix();

    ~Matrix();

    int* getRows() const;
    int* getCols() const;
    int* getValues() const;
    int getLength() const;
    int getItsNumberOfRows() const;
    int getItsNumberOfColumns() const;

    void setItsNumberOfRows(int itsNumberOfRows);
    void setItsNumberOfColumns(int itsNumberOfColumns);
    void setItsValues(int *itsValues);
    void setItsRows(int *itsRows);
    void setItsCols(int *itsCols);
    void setLength(int length);

    void Create();
    void Create(int nonZeros);

    void Input() ;
    void addElement(int length, int addingRow, int addingCol, int addingValue);
    void Print();
    int ** toNormalMtx() const;


    Matrix &operator=(const Matrix &);

    Matrix &operator+=(const Matrix &);

    Matrix &operator-=(const Matrix &);

    Matrix &operator*=(const Matrix &);

    Matrix &operator/=(const Matrix &);

    Matrix &operator++();

    Matrix &operator--();

    friend Matrix operator+(const Matrix &, const Matrix &);

    friend Matrix operator-(const Matrix &, const Matrix &);

    friend Matrix operator*(const Matrix &, const Matrix &);

    friend Matrix operator==(const Matrix &, const Matrix &);

    friend Matrix operator!=(const Matrix &, const Matrix &);


};
