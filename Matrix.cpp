#include "Matrix.h"


Matrix::Matrix() {
    Create();
    itsRows[0] = -1;
    itsCols[0] = -1;
    itsValues[0] = -1;
}

Matrix::Matrix(int nonZero) {
    Create(nonZero);
    for (int i = 0; i < nonZero; i++) {
        itsRows[i] = itsCols[i] = itsValues[i] = -1;
    }
}

Matrix::Matrix(const Matrix &original) {

    int *itsOldValues = original.getValues();
    int *itsOldCols = original.getCols();
    int *itsOldRows = original.getRows();

    int nonZeros = getLength();
    Create(nonZeros);

    setItsValues(itsOldValues);
    setItsRows(itsOldRows);
    setItsCols(itsOldCols);
}

Matrix::~Matrix() = default;

void Matrix::Create() {
    itsValues = new int[1];
    itsRows = new int[1];
    itsCols = new int[1];
}

void Matrix::Create(int nonZeros) {
    itsValues = new int[nonZeros];
    itsRows = new int[nonZeros];
    itsCols = new int[nonZeros];
    for (int i = 0; i < nonZeros; i++) {
        itsValues[i] = itsCols[i] = itsRows[i] = -1;
        itsLength = nonZeros;
    }
}

void Matrix::addElement(int length, int addingRow, int addingCol, int addingValue) {


    if (length == 1) {
        int *workingRows = getRows();
        int *workingCols = getCols();
        int *workingValues = getValues();
        workingRows[0] = addingRow;
        workingCols[0] = addingCol;
        workingValues[0] = addingValue;
        workingCols = workingRows = workingValues = nullptr;
        delete[] workingCols;
        delete[]  workingRows;
        delete[]  workingValues;

    }
    if (length > 1) {
        int *pRows;
        int *pCols;
        int *pValues;
        pRows = getRows();
        pCols = getCols();
        pValues = getValues();
        int *pnewRows;// pointers for new arrays
        int *pnewCols;
        int *pnewValues;

        // allocate a bigger array
        pnewRows = new int[length];
        pnewCols = new int[length];
        pnewValues = new int[length];

        // copy old values
        for (int i = 0; i < length - 1; i++) {
            pnewRows[i] = pRows[i];
            pnewCols[i] = pCols[i];
            pnewValues[i] = pValues[i];
        }
        // initialize remainder
        pnewRows[length - 1] = addingRow;
        pnewCols[length - 1] = addingCol;
        pnewValues[length - 1] = addingValue;

        // delete the old arrays
        pRows = pCols = pValues = nullptr;
        delete[]  pRows;
        delete[]  pCols;
        delete[]  pValues;

        // reassign the new array
        setItsRows(pnewRows);
        setItsCols(pnewCols);
        setItsValues(pnewValues);
        pnewCols = pnewRows = pnewValues = nullptr;
        delete[]  pnewCols;
        delete[]  pnewRows;
        delete[]  pnewValues;
    }
}

void Matrix::Input() {
    int Rows, Cols;
    int Value;
    int length = 1;
    cout << "Rows?" << endl;
    cin >> Rows;
    setItsNumberOfRows(Rows);
    cout << "Cols?" << endl;
    cin >> Cols;
    setItsNumberOfColumns(Cols);
    cout << "Enter values" << endl;
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            cout << "[" << i << "] ";
            cout << "[" << j << "] = ";
            cin >> Value;
            cout << endl;
            if (Value != 0) {
                addElement(length, i, j, Value);
                length++;
                setLength(length);
            }
        }
    }
}

void Matrix::Print() {
    int *pRows;
    int *pCols;
    int *pValues;
    pRows = getRows();
    pCols = getCols();
    pValues = getValues();
    int rowsNumber = getItsNumberOfRows();
    int colsNumber = getItsNumberOfColumns();


    int bigIter = 0;
    for (int i = 0; i < rowsNumber; i++) {
        cout << endl;
        for (int j = 0; j < colsNumber; j++) {
            if (i == pRows[bigIter] && j == pCols[bigIter]) {
                cout << pValues[bigIter] << " ";
                bigIter++;
            } else {
                cout << "0 ";
            }
        }


    }
}

int **Matrix::toNormalMtx() const {
    int rowsLen, colsLen, nonzeros;
    int *prows, *pcols, *pvalues;

    nonzeros = getLength();
    prows = getRows();
    pcols = getCols();
    pvalues = getValues();

    rowsLen = getItsNumberOfRows();
    colsLen = getItsNumberOfColumns();

    int **matr;
    matr = new int *[rowsLen];
    for (int i = 0; i < rowsLen; i++)
        matr[i] = new int[colsLen];

    for (int i = 0; i < rowsLen; i++) {
        for (int j = 0; j < colsLen; j++) {
            matr[i][j] = 0;
        }
    }


    for (int i = 0; i < nonzeros;) {
        matr[*(prows + i)][*(pcols + i)] = pvalues[*(pvalues + i)];
    }
    return matr;
}

void Matrix::setItsRows(int *itsRows) {
    Matrix::itsRows = itsRows;
}

void Matrix::setItsCols(int *itsCols) {
    Matrix::itsCols = itsCols;
}

void Matrix::setItsValues(int *itsValues) {
    Matrix::itsValues = itsValues;
}

void Matrix::setItsNumberOfRows(int itsNumberOfRows) {
    Matrix::itsNumberOfRows = itsNumberOfRows;
}

void Matrix::setItsNumberOfColumns(int itsNumberOfColumns) {
    Matrix::itsNumberOfColumns = itsNumberOfColumns;
}

void Matrix::setLength(int length) {
    Matrix::itsLength = length;
}


int *Matrix::getRows() const {
    return itsRows;
}

int *Matrix::getCols() const {
    return itsCols;
}

int *Matrix::getValues() const {
    return itsValues;
}

int Matrix::getLength() const {
    int *check = getValues();
    return sizeof(check) / sizeof(check[0]);
}

int Matrix::getItsNumberOfRows() const {
    return itsNumberOfRows;
}

int Matrix::getItsNumberOfColumns() const {
    return itsNumberOfColumns;
}


Matrix &Matrix::operator=(const Matrix &right) {
    if (this == &right) {
        return *this;
    }
    Create(right.itsLength);
    for (int i = 0; i < itsLength; i++) {
        itsRows[i] = right.itsRows[i];
        itsCols[i] = right.itsCols[i];
        itsValues[i] = right.itsValues[i];
    }
    return *this;
}

//
Matrix &Matrix::operator+=(const Matrix &right) {
    if (this == &right) {
        return *this;
    }

    int **R_Mtx = right.toNormalMtx();
    int R_Rows = right.getItsNumberOfRows();
    int R_Columns = right.getItsNumberOfColumns();

    int **L_Mtx = this->toNormalMtx();//??
    int L_Rows = this->getItsNumberOfRows();
    int L_Columns = this->getItsNumberOfColumns();

    if ((L_Rows == R_Rows) && (L_Columns == R_Columns)) {
        for (int i = 0; i < L_Rows; i++) {
            for (int j = 0; j < L_Columns; j++) {
                L_Mtx[i][j] += R_Mtx[i][j];
            }
        }

    } else {
        cout << "Matrices do not match" << endl;
    }

    L_Mtx = R_Mtx = nullptr;
    for (int i = 0; i < getItsNumberOfRows(); i++)
        delete L_Mtx[i];
    delete[] L_Mtx;
    for (int i = 0; i < right.getItsNumberOfRows(); i++)
        delete R_Mtx[i];
    delete[] R_Mtx;

    return *this;
}


Matrix &Matrix::operator-=(const Matrix &right) {
    if (this == &right) {
        return *this;
    }

    int **R_Mtx = right.toNormalMtx();
    int R_Rows = right.getItsNumberOfRows();
    int R_Columns = right.getItsNumberOfColumns();

    int **L_Mtx = this->toNormalMtx();//??
    int L_Rows = this->getItsNumberOfRows();
    int L_Columns = this->getItsNumberOfColumns();

    if ((L_Rows == R_Rows) && (L_Columns == R_Columns)) {
        for (int i = 0; i < L_Rows; i++) {
            for (int j = 0; j < L_Columns; j++) {
                L_Mtx[i][j] -= R_Mtx[i][j];
            }
        }
    } else cout << "Matrices do not match" << endl;
    L_Mtx = R_Mtx = nullptr;
    for (int i = 0; i < getItsNumberOfRows(); i++)
        delete L_Mtx[i];
    delete[] L_Mtx;
    for (int i = 0; i < right.getItsNumberOfRows(); i++)
        delete R_Mtx[i];
    delete[] R_Mtx;
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &right) {
    if (this == &right) {
        return *this;
    }

    int **R_Mtx = right.toNormalMtx();
    int R_Rows = right.getItsNumberOfRows();
    int R_Columns = right.getItsNumberOfColumns();

    int **L_Mtx = this->toNormalMtx();//??
    int L_Rows = this->getItsNumberOfRows();
    int L_Columns = this->getItsNumberOfColumns();

    if ((L_Rows == R_Rows) && (L_Columns == R_Columns)) {
        for (int i = 0; i < L_Rows; i++) {
            for (int j = 0; j < L_Columns; j++) {
                L_Mtx[i][j] *= R_Mtx[i][j];
            }
        }
    } else cout << "Matrices do not match" << endl;
    L_Mtx = R_Mtx = nullptr;
    for (int i = 0; i < getItsNumberOfRows(); i++)
        delete L_Mtx[i];
    delete[] L_Mtx;
    for (int i = 0; i < right.getItsNumberOfRows(); i++)
        delete R_Mtx[i];
    delete[] R_Mtx;
    return *this;
}

Matrix &Matrix::operator/=(const Matrix &right) {
    if (this == &right) {
        return *this;
    }

    int **R_Mtx = right.toNormalMtx();
    int R_Rows = right.getItsNumberOfRows();
    int R_Columns = right.getItsNumberOfColumns();

    int **L_Mtx = this->toNormalMtx();//??
    int L_Rows = this->getItsNumberOfRows();
    int L_Columns = this->getItsNumberOfColumns();

    if ((L_Rows == R_Rows) && (L_Columns == R_Columns)) {
        for (int i = 0; i < L_Rows; i++) {
            for (int j = 0; j < L_Columns; j++) {
                L_Mtx[i][j] /= R_Mtx[i][j];
            }
        }
    } else cout << "Matrices do not match" << endl;
    L_Mtx = nullptr;
    for (int i = 0; i < getItsNumberOfRows(); i++)
        delete L_Mtx[i];
    delete[] L_Mtx;
    R_Mtx = nullptr;
    for (int i = 0; i < right.getItsNumberOfRows(); i++)
        delete R_Mtx[i];
    delete[] R_Mtx;

    return *this;
}

Matrix &Matrix::operator++() {

    int **L_Mtx = this->toNormalMtx();
    for (int i = 0; i < getItsNumberOfRows(); i++) {
        for (int j = 0; j < getItsNumberOfColumns(); j++) {
            ++L_Mtx[i][j];
        }
    }
    L_Mtx = nullptr;
    for (int i = 0; i < getItsNumberOfRows(); i++)
        delete L_Mtx[i];
    delete[] L_Mtx;

    return *this;
}

Matrix &Matrix::operator--() {
    int **L_Mtx = this->toNormalMtx();
    for (int i = 0; i < getItsNumberOfRows(); i++) {
        for (int j = 0; j < getItsNumberOfColumns(); j++) {
            --L_Mtx[i][j];
        }
    }
    L_Mtx = nullptr;
    for (int i = 0; i < getItsNumberOfRows(); i++)
        delete L_Mtx[i];
    delete[] L_Mtx;

    return *this;
}

Matrix operator+(const Matrix &a, const Matrix &b) {
    Matrix c(a);

    int **aMtx = a.toNormalMtx();
    int **bMtx = b.toNormalMtx();
    int **cMtx = c.toNormalMtx();
    int Rows1 = a.getItsNumberOfRows();
    int Columns1 = a.getItsNumberOfColumns();
    int Rows2 = b.getItsNumberOfRows();
    int Columns2 = b.getItsNumberOfColumns();
    if ((Rows1 == Rows2) && (Columns1 == Columns2)) {
        for (int i = 0; i < Columns1; i++) {
            for (int j = 0; j < Rows1; j++) {
                cMtx[i][j] = aMtx[i][j] + bMtx[i][j];
            }
        }
    } else cout << "Matrices do not match" << endl;
    return c;
}

//Matrix operator-(const Matrix &a, const Matrix &b) {
//    Matrix c(a);
//    int Lines1 = a.getNumberOfLines();
//    int Columns1 = a.getNumberOfColumns();
//    int Lines2 = b.getNumberOfLines();
//    int Columns2 = b.getNumberOfColumns();
//    if ((Lines1 == Lines2) && (Columns1 == Columns2)) {
//        for (int i = 0; i < Columns1; i++) {
//            for (int j = 0; j < Lines1; j++) {
//                c.ptrSomeMatrix[i][j] = a.ptrSomeMatrix[i][j] - b.ptrSomeMatrix[i][j];
//            }
//        }
//    } else cout << "Matrices do not match" << endl;
//    return c;
//}
//
//Matrix operator*(const Matrix &a, const Matrix &b) {
//    int Lines1 = a.getNumberOfLines();
//    int Columns1 = a.getNumberOfColumns();
//    int Lines2 = b.getNumberOfLines();
//    int Columns2 = b.getNumberOfColumns();
//    Matrix c(Lines1, Columns2);
//    if (Columns1 == Lines2) {
//        for (int i = 0; i < Columns2; i++)
//            for (int j = 0; j < Lines1; j++) {
//                c.ptrSomeMatrix[i][j] = 0;
//                for (int k = 0; k < Columns1; k++)
//                    c.ptrSomeMatrix[i][j] += a.ptrSomeMatrix[i][k] * b.ptrSomeMatrix[k][j];
//            }
//    } else cout << "Matrices do not match" << endl;
//    return c;
//}

//Matrix operator==(const Matrix &a, const Matrix &b) {
//    int Lines1 = a.getNumberOfLines();
//    int Columns1 = a.getNumberOfColumns();
//    int Lines2 = b.getNumberOfLines();
//    int Columns2 = b.getNumberOfColumns();
//    int k = 0;
//    if ((Columns1 == Columns2) && (Lines1 == Lines2)) {
//        for (int i = 0; i < Columns1; i++) {
//            for (int j = 0; j < Lines1; j++) {
//                if (a.ptrSomeMatrix[i][j] != b.ptrSomeMatrix[i][j]) k++;
//            }
//        }
//        if (k) {
//            cout << "Matrices are not equal to each other" << endl;
//            return 0;
//        } else {
//            cout << "Matrices are equal" << endl;
//            return 1;
//        }
//    } else {
//        cout << "Matrices are not equal to each other" << endl;
//        return 0;
//    }
//}
//
// Matrix operator!=(const Matrix &a, const Matrix &b) {
//    int Lines1 = a.getNumberOfLines();
//    int Columns1 = a.getNumberOfColumns();
//    int Lines2 = b.getNumberOfLines();
//    int Columns2 = b.getNumberOfColumns();
//    int k = 0;
//    if ((Columns1 == Columns2) && (Lines1 == Lines2)) {
//        for (int i = 0; i < Columns1; i++) {
//            for (int j = 0; j < Lines1; j++) {
//                if (a.ptrSomeMatrix[i][j] != b.ptrSomeMatrix[i][j]) k++;
//            }
//        }
//        if (k) {
//            cout << "Matrices are not equal to each other" << endl;
//            return 1;
//        } else {
//            cout << "Matrices are equal" << endl;
//            return 0;
//        }
//    } else {
//        cout << "Matrices are not equal to each other" << endl;
//        return 1;
//    }
//}
Matrix::toSparse(int **arr, int rows, int cols) {
    Matrix A();
    int size = countNonzeros(arr, rows, cols);
    int *prows = new int[size];
    int *pcols = new int[size];
    int *pvals = new int[size];
    int bigIndex = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] != 0) {
                prows[*(prows + bigIndex)] = i;//like a arr[i]=i;
                pcols[*(prows + bigIndex)] = j;
                pvals[*(prows + bigIndex)] = arr[i][j];
            }
        }
    }
    A().setItsValues(pvals);
    A().setItsCols(pcols);
    A().setItsRows(prows);
    A().setLength(size);
    A().setItsNumberOfRows(rows);
    A().setItsNumberOfColumns(cols);
return A;

}

int Matrix::countNonzeros(int **arr, int rows, int cols) {
    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] != 0) {
                count++;
            }
        }
    }
    return count;
}


