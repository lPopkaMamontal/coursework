#include <iostream>
#include <vector>

using namespace std;

const double EPSILON = 1e-10;

int gauss(vector<vector<double>>& A, vector<double>& b) {
    int n = A.size();

    for (int i = 0; i < n; i++) {
        int max_row = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(A[j][i]) > abs(A[max_row][i])) {
                max_row = j;
            }
        }

        swap(A[i], A[max_row]);
        swap(b[i], b[max_row]);

        if (abs(A[i][i]) < EPSILON) {
            return -1;
        }

        for (int j = i + 1; j < n; j++) {
            double f = A[j][i] / A[i][i];
            b[j] -= f * b[i];
            for (int k = i + 1; k < n; k++) {
                A[j][k] -= f * A[i][k];
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            double f = A[j][i] / A[i][i];
            b[j] -= f * b[i];
            for (int k = i - 1; k >= 0; k--) {
                A[j][k] -= f * A[i][k];
            }
        }
        b[i] /= A[i][i];
        A[i][i] = 1;
    }

    return 0;
}

int main() {
    vector<vector<double>> A = { {2, 1, -1}, {4, -6, 0}, {-2, 7, 2} };
    vector<double> b = { 8, -2, 11 };

    int res = gauss(A, b);

    if (res == -1) {
        cout << "No unique solution exists." << endl;
    }
    else {
        for (int i = 0; i < A.size(); i++) {
            cout << "x_" << i + 1 << " = " << b[i] << endl;
        }
    }

    return 0;
}
