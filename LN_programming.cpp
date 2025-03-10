#include <bits/stdc++.h>
using namespace std;

void printNumber(double num) {
    if (num == 0)
        cout << "0";
    else
        cout << fixed << setprecision(1) << num;
}


class LN_programming {
public:
    int n, m;
    vector<double> F;
    vector<vector<double>> A;
    vector<double> B;
    vector<vector<double>> Tab;
    vector<double> x;

    LN_programming(int N, vector<double> f, vector<vector<double>> a, vector<double> b)
        : n(N), F(f), A(a), B(b) {
        m = A.size();
        Tab.resize(m + 1, vector<double>(n + 2, 0));
        x.resize(n,0);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                Tab[i][j] = A[i][j];
            }
            Tab[i][n] = 1;
            Tab[i][n + 1] = B[i];
        }

        for (int j = 0; j < n; j++) {
            Tab[m][j] = -F[j];
        }
    }

    bool check_optimal() {
        for (int j = 0; j < n; j++) {
            if (Tab[m][j] < 0) return false;
        }
        return true;
    }

    bool check_unbounded(int pivot_col) {
        for (int i = 0; i < m; i++) {
            if (Tab[i][pivot_col] > 0) return false;
        }
        return true;
    }

    void pivot(int pivot_row, int pivot_col) {
        double pivot_val = Tab[pivot_row][pivot_col];
        for (int j = 0; j <= n + 1; j++) {
            Tab[pivot_row][j] /= pivot_val;
        }

        for (int i = 0; i <= m; i++) {
            if (i != pivot_row) {
                double factor = Tab[i][pivot_col];
                for (int j = 0; j <= n + 1; j++) {
                    Tab[i][j] -= factor * Tab[pivot_row][j];
                }
            }
        }
    }

    double solve() {
        while (!check_optimal()) {
            int pivot_col = min_element(Tab[m].begin(), Tab[m].begin() + n) - Tab[m].begin();

            if (check_unbounded(pivot_col)) {
                return INT_MAX;
            }

            int pivot_row = -1;
            double min_ratio = DBL_MAX;
            for (int i = 0; i < m; i++) {
                if (Tab[i][pivot_col] > 0) {
                    double ratio = Tab[i][n + 1] / Tab[i][pivot_col];
                    if (ratio < min_ratio) {
                        min_ratio = ratio;
                        pivot_row = i;
                    }
                }
            }

            pivot(pivot_row, pivot_col);
        }

        return Tab[m][n + 1];
    }
    void setX(){
       for (int i = 0; i < n; i++) {
        int pivot_row = -1;
        for (int j = 0; j < m; j++) {
            if (Tab[j][i] == 1) {
                if (pivot_row == -1)
                    pivot_row = j;
                else {
                    pivot_row = -1;
                    break;
                }
            } else if (Tab[j][i] != 0) {
                pivot_row = -1;
                break;
            }
        }
        if (pivot_row != -1) {
            x[i] = Tab[pivot_row][n + 1];
        }
    }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    n=n+m;
    vector<double> f(n);
    vector<vector<double>> a;
    a.resize(m,vector<double>(n,0));
    vector<double> b(m);

    for(int i=0; i<n; i++){
        if(i<n-m) cin >> f[i];
        else f[i]=0;
    }
    for(int i=0; i<m; i++){
        for(int j=0; j<n-m; j++) cin >> a[i][j];
        for(int j= n-m ; j<n; j++){
            a[i][j] = (j == n-m+i) ? 1 : 0;
        }

    }
    for(int i=0 ; i< m ; i++) cin >> b[i];

    LN_programming ln(n, f, a, b);
    double result = ln.solve();
    ln.setX();
    if (result != INT_MAX) {
       cout << n-m << endl;
       for(int i = 0; i< n-m; i++){
        printNumber(ln.x[i]);
       }

    }
    else{
        cout << "UNBOUNDED";
    }
    cout << endl;

    for(int i = 0; i< ln.Tab.size(); i++){
        for(int j =0 ; j< ln.Tab[0].size(); j++){
            cout << ln.Tab[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
