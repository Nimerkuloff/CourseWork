#include "Matrix.h"
Matrix::Matrix() {
    Create();
    itsRows[0] = -1;
    itsCols[0] = -1;
    itsValues[0] = -1;
    itsLength = 1;
}

Matrix::Matrix(int nonZero) {
    Create(nonZero);
    for (int i = 0; i < nonZero; i++) {
        itsRows[i] = itsCols[i] = itsValues[i] = -1;
    }
}

Matrix::Matrix(const Matrix &original) {

    this->itsValues = original.getValues();
    this->itsCols = original.getCols();
    this->itsRows = original.getRows();
    this->itsLength = original.getLength();
    this->itsNumberOfColumns = original.getItsNumberOfColumns();
    this->itsNumberOfRows = original.getItsNumberOfRows();
}

Matrix::~Matrix(){
    delete[] itsCols;
    delete[] itsRows;
    delete[] itsValues;

};


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
                setLength(length - 1);
            }
        }
    }
}

void Matrix::Print()const {
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


    for (int i = 0; i < nonzeros; i++) {
        matr[prows[i]][pcols[i]] = pvalues[i];
    }
    return matr;
}

void Matrix::toSparse(int **arr, int rows, int cols) {

    int size = countNonzeros(arr, rows, cols);
    auto *prows = new int[size];
    auto *pcols = new int[size];
    auto *pvals = new int[size];
    int bigIndex = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] != 0) {
                prows[bigIndex] = i;//like a arr[i]=i;
                pcols[bigIndex] = j;
                pvals[bigIndex] = arr[i][j];
                bigIndex++;
            }
        }
    }
    Matrix::itsValues = pvals;
    Matrix::itsCols = pcols;
    Matrix::itsRows = prows;
    Matrix::itsLength = size;
    Matrix::itsNumberOfRows = rows;
    Matrix::itsNumberOfColumns = cols;

    prows = pcols = pvals = nullptr;
    delete prows;
    delete pcols;
    delete pvals;


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
    return itsLength;
}

int Matrix::getItsNumberOfRows() const {
    return itsNumberOfRows;
}

int Matrix::getItsNumberOfColumns() const {
    return itsNumberOfColumns;
}


//Matrix &Matrix::operator=(const Matrix &right) {
//    if (this == &right) {
//        return *this;
//    }
//    Matrix::Matrix(const Matrix &right);
////    Create(right.itsLength);
////    for (int i = 0; i < itsLength; i++) {
////        itsRows[i] = right.itsRows[i];
////        itsCols[i] = right.itsCols[i];
////        itsValues[i] = right.itsValues[i];
////    }
//    return *this;
//}

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

        this->toSparse(L_Mtx, L_Rows, L_Columns);



        for (int i = 0; i < getItsNumberOfRows(); i++)
            delete L_Mtx[i];
        delete[] L_Mtx;
        for (int i = 0; i < right.getItsNumberOfRows(); i++)
            delete R_Mtx[i];
        delete[] R_Mtx;

        return *this;
    } else {
        cout << "Matrices do not match" << endl;
    }


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
        this->toSparse(L_Mtx, L_Rows, L_Columns);



        for (int i = 0; i < getItsNumberOfRows(); i++)
            delete L_Mtx[i];
        delete[] L_Mtx;
        for (int i = 0; i < right.getItsNumberOfRows(); i++)
            delete R_Mtx[i];
        delete[] R_Mtx;
        return *this;
    } else cout << "Matrices do not match" << endl;


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
        this->toSparse(L_Mtx, L_Rows, L_Columns);



        for (int i = 0; i < getItsNumberOfRows(); i++)
            delete[] L_Mtx[i];
        delete[] L_Mtx;
        for (int i = 0; i < right.getItsNumberOfRows(); i++)
            delete R_Mtx[i];
        delete[] R_Mtx;
        return *this;
    } else cout << "Matrices do not match" << endl;


}


Matrix &Matrix::operator++() {

    int **L_Mtx = this->toNormalMtx();
    for (int i = 0; i < getItsNumberOfRows(); i++) {
        for (int j = 0; j < getItsNumberOfColumns(); j++) {
            ++L_Mtx[i][j];
        }
    }


    this->toSparse(L_Mtx, getItsNumberOfRows(), getItsNumberOfColumns());



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


    this->toSparse(L_Mtx, getItsNumberOfRows(), getItsNumberOfColumns());


    // L_Mtx = nullptr;
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
        c.toSparse(cMtx, Rows1, Columns1);
        return c;
    } else cout << "Matrices do not match" << endl;

}

Matrix operator-(const Matrix &a, const Matrix &b) {
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
                cMtx[i][j] = aMtx[i][j] - bMtx[i][j];
            }
        }
        c.toSparse(cMtx, Rows1, Columns1);
        return c;
    } else cout << "Matrices do not match" << endl;


}

Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix c;
    c = a;
    int **aMtx = a.toNormalMtx();
    int **bMtx = b.toNormalMtx();
    int **cMtx = c.toNormalMtx();
    int Rows1 = a.getItsNumberOfRows();
    int Columns1 = a.getItsNumberOfColumns();
    int Rows2 = b.getItsNumberOfRows();
    if (Columns1 == Rows2) {
        for (int i = 0; i < Rows2; i++) {
            for (int j = 0; j < Columns1; j++) {
                cMtx[i][j] = 0;
                for (int k = 0; k < Rows1; k++) {
                    cMtx[i][j] += aMtx[i][k] * bMtx[k][j];
                }
            }
        }
        c.toSparse(cMtx, Rows2, Columns1);
        return c;
    } else cout << "Matrices do not match" << endl;

}

int operator==(const Matrix &a, const Matrix &b) {
    int **aMtx = a.toNormalMtx();
    int **bMtx = b.toNormalMtx();

    int Rows1 = a.getItsNumberOfRows();
    int Columns1 = a.getItsNumberOfColumns();
    int Rows2 = b.getItsNumberOfRows();
    int Columns2 = b.getItsNumberOfColumns();

    int k = 0;
    if ((Columns1 == Columns2) && (Rows1 == Rows2)) {
        for (int i = 0; i < Rows1; i++) {
            for (int j = 0; j < Columns1; j++) {
                if (aMtx[i][j] != bMtx[i][j]) k++;
            }
        }
    }
    if (k == 0) {
        cout << "Matrices are equal" << endl;
        return 1;
    } else {
        return 0;
    }
}

int operator!=(const Matrix &a, const Matrix &b) {
    int **aMtx = a.toNormalMtx();
    int **bMtx = b.toNormalMtx();

    int Rows1 = a.getItsNumberOfRows();
    int Columns1 = a.getItsNumberOfColumns();
    int Rows2 = b.getItsNumberOfRows();
    int Columns2 = b.getItsNumberOfColumns();

    int k = 0;
    if ((Columns1 == Columns2) && (Rows1 == Rows2)) {
        for (int i = 0; i < Rows1; i++) {
            for (int j = 0; j < Columns1; j++) {
                if (aMtx[i][j] != bMtx[i][j]) k++;
            }
        }
    }
    if (k == 0) {
        cout << "Matrices are equal" << endl;
        return 0;
    } else {
        return 1;
        cout << "Matrices are equal" << endl;
    }
}

ostream &operator<<(ostream &out, const Matrix &matrix) {
    int *pRows;
    int *pCols;
    int *pValues;
    pRows = matrix.getRows();
    pCols = matrix.getCols();
    pValues = matrix.getValues();
    int rowsNumber = matrix.getItsNumberOfRows();
    int colsNumber = matrix.getItsNumberOfColumns();


    int bigIter = 0;
    for (int i = 0; i < rowsNumber; i++) {
        cout << endl;
        for (int j = 0; j < colsNumber; j++) {
            if (i == pRows[bigIter] && j == pCols[bigIter]) {
                out << pValues[bigIter] << " ";
                bigIter++;
            } else {
                out << "0 ";
            }
        }
    }

    return out;
}






