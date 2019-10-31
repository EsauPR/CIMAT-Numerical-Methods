#include <cstdio>
#include <cstdlib>

using namespace std;

#define SIZE 2001

int MATRIX[SIZE][SIZE];


void save_matrix(const char * file_name) {
    FILE *fp = fopen(file_name, "w");
    if(fp == NULL) {
        perror("Can't open file to write");
        return;
    }

    fprintf(fp, "%d %d\n", SIZE-1, SIZE-1);

    for (int i = 1; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            fprintf(fp, "%d ", MATRIX[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

int main(int argc, char const *argv[]) {

    int xs[5];
    int xv[5] = {-4, -8, 40, -8, -4 };

    for (int i = 1; i < SIZE; i++) {
        xs[0] = i - 2;
        xs[1] = i - 1;
        xs[2] = i;
        xs[3] = i + 1;
        xs[4] = i + 2;

        for (int j = 0; j < 5; j++) {
            if(xs[j] >= 0 && xs[j] < SIZE ) {
                MATRIX[i][xs[j]] = xv[j];
            }
        }
    }


    save_matrix("A.mtx");

    return 0;
}
