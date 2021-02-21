#include<iostream>
using namespace std;

class chessBoard {
    int n, *X, solution_number;

    public:
        chessBoard(int n) {
            this -> n = n;
            X = new int[n];
            solution_number = 0;
        }
        int place(int, int);
        void n_queens(int);
        void display();
};

void chessBoard::display() {
    cout << "\nSolution #" << solution_number << ":\n" << endl;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++)
            X[j] == i ? cout << "Q" << " " : cout  << "_ ";
        cout << endl;
    }
    cout << endl;
}

int chessBoard::place(int k, int i) {
    for (int j = 0;j < k;j++) {
        if ((X[j] == i) || (abs(X[j] - i) == abs(j - k)))   // queens placed on same column / diagonal?
            return 0;
    }
    return 1;
}

void chessBoard::n_queens(int k) {
    for (int i = 0;i < n;i++) {
        if (place(k, i)) {      // bounding function satisfied?
            X[k] = i;
            if (k == n - 1) {      // array filled with n elements?
                solution_number++;
                display();
                return;
            } else n_queens(k + 1);
        }
    }
}

int main() {
    int n = 0;
    cout << "\nN-Queen's Problem\n\n";
    while (n < 4) {
        cout << "Enter number of queens (> 3): ";
        cin >> n;
    }
    chessBoard c(n);
    c.n_queens(0);
    return 0;
}