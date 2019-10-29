#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct sparse_matrix {
    double ** data;
    int row, col;
    int len;

    void init(int r, int c) {
        // initialize row
        row = r;
        // initialize col
        col = c;
        // intialize length to 0
        len = 0;

        data = (double**)malloc(3*sizeof(r));
        for (int i = 0; i < r; i+=3) {
            data[i] = &(data[0] + i);
        }
    }

    void insert(int r, int c, int val) {
        // invalid entry
        if (r > row || c > col) {
            cout << "Wrong entry: " << row << " " << col << " " << val << endl;
        }

        else {
            data.push_back(make_pair(make_pair(r, c), val));
            len++;
        }
    }

    struct sparse_matrix * add(struct sparse_matrix * b) {

        int apos = 0, bpos = 0;
        struct sparse_matrix * result = (struct sparse_matrix *) malloc(sizeof(struct sparse_matrix));
        result->init(row, col);

        // if matrices don't have same dimensions
        if (row != b->row || col != b->col) {
            cout << "Wrong dimensions" << endl;
            return result;
        }

        while (apos < len && bpos < b->len) {
            // if b's row and col is smaller
            if (data[apos].first.first > b->data[bpos].first.first ||
                (data[apos].first.first == b->data[bpos].first.first &&
                data[apos].first.second > b->data[bpos].first.second))

            {

                // insert smaller value into result
                result->insert(b->data[bpos].first.first,
                                b->data[bpos].first.second,
                                b->data[bpos].second);

                bpos++;
            }

            // if a's row and col is smaller
            else if (data[apos].first.first < b->data[bpos].first.first ||
            (data[apos].first.first == b->data[bpos].first.first &&
                data[apos].first.second < b->data[bpos].first.second))

            {

                // insert smaller value into result
                result->insert(data[apos].first.first,
                                data[apos].first.second,
                                data[apos].second);

                apos++;
            }

            else {

                // add the values as row and col is same
                int addedval = data[apos].second + b->data[bpos].second;

                if (addedval != 0)
                    result->insert(data[apos].first.first,
                                    data[apos].first.second,
                                    addedval);
                // then insert
                apos++;
                bpos++;
            }
        }

        // insert remaining elements
        while (apos < len)
            result->insert(data[apos].first.first,
                            data[apos].first.second,
                            data[apos++].second);

        while (bpos < b->len)
            result->insert(b->data[bpos].first.first,
                            b->data[bpos].first.second,
                            b->data[bpos++].second);

        // print result
        result->print();
        return result;
    }

    struct sparse_matrix * transpose() {
        // new matrix with inversed row X col
        struct sparse_matrix * result = (struct sparse_matrix *) malloc(sizeof(struct sparse_matrix));
        result->init(col, row);
        result->data.resize(row);

        // same number of elements
        result->len = len;

        // to count number of elements in each column
        int * count = new int[col + 1];

        // initialize all to 0
        for (int i = 1; i <= col; i++)
            count[i] = 0;

        for (int i = 0; i < len; i++)
            count[data[i].first.second]++;

        int * index = new int[col + 1];

        // to count number of elements having col smaller
        // than particular i

        // as there is no col with value < 1
        index[1] = 0;

        // initialize rest of the indices
        for (int i = 2; i <= col; i++)

            index[i] = index[i - 1] + count[i - 1];

        for (int i = 0; i < len; i++) {

            // insert a data at rpos and increment its value
            int rpos = index[data[i].first.second]++;

            // transpose row=col
            result->data[rpos].first.first = data[i].first.second;

            // transpose col=row
            result->data[rpos].first.second = data[i].first.first;

            // same value
            result->data[rpos].second = data[i].second;
        }

        // the above method ensures
        // sorting of transpose matrix
        // according to row-col value

        delete count;
        delete index;

        return result;
    }

    struct sparse_matrix * multiply(struct sparse_matrix * b) {

        // transpose b to compare row
        // and col values and to add them at the end
        b = b->transpose();
        int apos, bpos;

        // result matrix of dimension row X b.col
        // however b has been transposed, hence row X b.row
        struct sparse_matrix * result = (struct sparse_matrix *) malloc(sizeof(struct sparse_matrix));
        result->init(row, b->row);

        if (col != b->row) {
            // Invalid multiplication
            cout << "Invalid dimensions" << endl;
            return result;
        }

        // iterate over all elements of A
        for (apos = 0; apos < len;) {

            // current row of result matrix
            int r = data[apos].first.first;

            // iterate over all elements of B
            for (bpos = 0; bpos < b->len;) {

                // current column of result matrix
                // data[].first.first used as b is transposed
                int c = b->data[bpos].first.first;

                // temporary pointers created to add all
                // multiplied values to obtain current
                // element of result matrix
                int tempa = apos;
                int tempb = bpos;

                int sum = 0;

                // iterate over all elements with
                // same row and col value
                // to calculate result[r]
                while (tempa < len && data[tempa].first.first == r
                       && tempb < b->len && b->data[tempb].first.first == c) {

                    if (data[tempa].first.second < b->data[tempb].first.second)

                        // skip a
                        tempa++;

                    else if (data[tempa].first.second > b->data[tempb].first.second)

                        // skip b
                        tempb++;
                    else

                        // same col, so multiply and increment
                        sum += data[tempa++].second * b->data[tempb++].second;
                }

                // insert sum obtained in result[r]
                // if its not equal to 0
                if (sum != 0)
                    result->insert(r, c, sum);

                while (bpos < b->len && b->data[bpos].first.first == c)

                    // jump to next column
                    bpos++;
            }

            while (apos < len && data[apos].first.first == r)

                // jump to next row
                apos++;
        }

        result->print();
        return result;
    }

    // printing matrix
    void print() {
        cout << "Dimension: " << row << "x" << col << endl;
        cout << "Sparse Matrix: \nRow Column Value" << endl;

        for (int i = 0; i < len; i++) {
            cout << data[i].first.first << " " << data[i].first.second << " " << data[i].second << endl;
        }
    }

} SparseMatrix;



// class SparseMatrix {

//     // Maximum number of elements in matrix
//     // int max = 100;

//     // Array representation
//     // of sparse matrix
//     //[][0] represents row
//     //[][1] represents col
//     //[][2] represents value
//     vector<pair<pair<int, int>, double> > data;

//     // dimensions of matrix
//     int row, col;

//     // total number of elements in matrix
//     int len;

//     public: SparseMatrix(int r, int c) {

//         // initialize row
//         row = r;

//         // initialize col
//         col = c;

//         // intialize length to 0
//         len = 0;
//     }

//     // insert elements into sparse matrix
//     public: void insert(int r, int c, int val) {
//         // invalid entry
//         if (r > row || c > col) {
//             cout << "Wrong entry: " << row << " " << col << " " << val << endl;
//         }

//         else {
//             data.push_back(make_pair(make_pair(r, c), val));
//             len++;
//         }
//     }

//     public: SparseMatrix * add(SparseMatrix * b)
//     {

//         int apos = 0, bpos = 0;
//         SparseMatrix * result = new SparseMatrix(row, col);

//         // if matrices don't have same dimensions
//         if (row != b->row || col != b->col) {
//             cout << "Wrong dimensions" << endl;
//             return result;
//         }

//         while (apos < len && bpos < b->len) {
//             // if b's row and col is smaller
//             if (data[apos].first.first > b->data[bpos].first.first ||
//                 (data[apos].first.first == b->data[bpos].first.first &&
//                 data[apos].first.second > b->data[bpos].first.second))

//             {

//                 // insert smaller value into result
//                 result->insert(b->data[bpos].first.first,
//                                 b->data[bpos].first.second,
//                                 b->data[bpos].second);

//                 bpos++;
//             }

//             // if a's row and col is smaller
//             else if (data[apos].first.first < b->data[bpos].first.first ||
//             (data[apos].first.first == b->data[bpos].first.first &&
//                 data[apos].first.second < b->data[bpos].first.second))

//             {

//                 // insert smaller value into result
//                 result->insert(data[apos].first.first,
//                                 data[apos].first.second,
//                                 data[apos].second);

//                 apos++;
//             }

//             else {

//                 // add the values as row and col is same
//                 int addedval = data[apos].second + b->data[bpos].second;

//                 if (addedval != 0)
//                     result->insert(data[apos].first.first,
//                                     data[apos].first.second,
//                                     addedval);
//                 // then insert
//                 apos++;
//                 bpos++;
//             }
//         }

//         // insert remaining elements
//         while (apos < len)
//             result->insert(data[apos].first.first,
//                             data[apos].first.second,
//                             data[apos++].second);

//         while (bpos < b->len)
//             result->insert(b->data[bpos].first.first,
//                             b->data[bpos].first.second,
//                             b->data[bpos++].second);

//         // print result
//         result->print();
//         return result;
//     }

//     public: SparseMatrix * transpose() {

//         // new matrix with inversed row X col
//         SparseMatrix * result = new SparseMatrix(col, row);
//         result->data.resize(row);

//         // same number of elements
//         result->len = len;

//         // to count number of elements in each column
//         int * count = new int[col + 1];

//         // initialize all to 0
//         for (int i = 1; i <= col; i++)
//             count[i] = 0;

//         for (int i = 0; i < len; i++)
//             count[data[i].first.second]++;

//         int * index = new int[col + 1];

//         // to count number of elements having col smaller
//         // than particular i

//         // as there is no col with value < 1
//         index[1] = 0;

//         // initialize rest of the indices
//         for (int i = 2; i <= col; i++)

//             index[i] = index[i - 1] + count[i - 1];

//         for (int i = 0; i < len; i++) {

//             // insert a data at rpos and increment its value
//             int rpos = index[data[i].first.second]++;

//             // transpose row=col
//             result->data[rpos].first.first = data[i].first.second;

//             // transpose col=row
//             result->data[rpos].first.second = data[i].first.first;

//             // same value
//             result->data[rpos].second = data[i].second;
//         }

//         // the above method ensures
//         // sorting of transpose matrix
//         // according to row-col value

//         delete count;
//         delete index;

//         return result;
//     }

//     public: SparseMatrix * multiply(SparseMatrix * b) {

//         // transpose b to compare row
//         // and col values and to add them at the end
//         b = b->transpose();
//         int apos, bpos;

//         // result matrix of dimension row X b.col
//         // however b has been transposed, hence row X b.row
//         SparseMatrix * result = new SparseMatrix(row, b->row);

//         if (col != b->row) {
//             // Invalid multiplication
//             cout << "Invalid dimensions" << endl;
//             return result;
//         }

//         // iterate over all elements of A
//         for (apos = 0; apos < len;) {

//             // current row of result matrix
//             int r = data[apos].first.first;

//             // iterate over all elements of B
//             for (bpos = 0; bpos < b->len;) {

//                 // current column of result matrix
//                 // data[].first.first used as b is transposed
//                 int c = b->data[bpos].first.first;

//                 // temporary pointers created to add all
//                 // multiplied values to obtain current
//                 // element of result matrix
//                 int tempa = apos;
//                 int tempb = bpos;

//                 int sum = 0;

//                 // iterate over all elements with
//                 // same row and col value
//                 // to calculate result[r]
//                 while (tempa < len && data[tempa].first.first == r
//                        && tempb < b->len && b->data[tempb].first.first == c) {

//                     if (data[tempa].first.second < b->data[tempb].first.second)

//                         // skip a
//                         tempa++;

//                     else if (data[tempa].first.second > b->data[tempb].first.second)

//                         // skip b
//                         tempb++;
//                     else

//                         // same col, so multiply and increment
//                         sum += data[tempa++].second * b->data[tempb++].second;
//                 }

//                 // insert sum obtained in result[r]
//                 // if its not equal to 0
//                 if (sum != 0)
//                     result->insert(r, c, sum);

//                 while (bpos < b->len && b->data[bpos].first.first == c)

//                     // jump to next column
//                     bpos++;
//             }

//             while (apos < len && data[apos].first.first == r)

//                 // jump to next row
//                 apos++;
//         }

//         result->print();
//         return result;
//     }

//     // printing matrix
//     public: void print() {
//         cout << "Dimension: " << row << "x" << col << endl;
//         cout << "Sparse Matrix: \nRow Column Value" << endl;

//         for (int i = 0; i < len; i++) {
//             cout << data[i].first.first << " " << data[i].first.second << " " << data[i].second << endl;
//         }
//     }
// };

int main(int argc, char const *argv[]) {
    // create two sparse matrices and insert values
    SparseMatrix * a = (SparseMatrix *) malloc(sizeof(SparseMatrix));
    a->init(4, 4);
    SparseMatrix *b = (SparseMatrix *) malloc(sizeof(SparseMatrix));
    b->init(4, 4);

    a->insert(1, 2, 10);
    a->insert(1, 4, 12);
    a->insert(3, 3, 5);
    a->insert(4, 1, 15);
    a->insert(4, 2, 12);

    b->insert(1, 3, 8);
    b->insert(2, 4, 23);
    b->insert(3, 3, 9);
    b->insert(4, 1, 20);
    b->insert(4, 2, 25);

    // Output result
    cout << "Addition: " << endl;
    a->add(b);
    cout << "\nMultiplication: " << endl;
    a->multiply(b);
    cout << "\nTranspose: " << endl;
    SparseMatrix * atranspose = a->transpose();
    atranspose->print();


    // delete a;
    // delete b;
    // delete atranspose;

    return 0;
}
