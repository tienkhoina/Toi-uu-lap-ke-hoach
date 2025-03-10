#include <bits/stdc++.h>
using namespace std;

int X[13]; // X[i] là điểm tiếp theo của điểm i trên lộ trình
int C[13][13];
int Y[6]; // Y[i] là điểm bắt đầu của xe thứ i
int d[13]; // d[i] là lượng hàng tại điểm i
int load[6]; // load[i] là lượng hàng trên xe i
int visited[13]; // đánh dấu điểm i đã được đi qua
int segment = 0; // số đoạn đã đi
int nbR = 0; // số xe được sử dụng để tạo lộ trình
int minf = 99999; // giá trị tối thiểu của lộ trình
int f = 0;
int Cmin = 9999;
int N, K, Q;

int checkX(int v, int k) {
    if (v > 0 && visited[v] == 1) return 0;
    if (load[k] + d[v] > Q) return 0;
    return 1;
}

void TryX(int s, int k) {
    if (s == 0) {
        if (k < K) {
            TryX(Y[k + 1], k + 1);
        }
        return;
    }
    for (int v = 0; v <= N; v++) {
            if (checkX(v, k) == 1) {
                X[s] = v;
                visited[v] = 1;
                load[k] += d[v];
                segment++;
                f += C[s][v];
                if (v > 0) {
                    if (f + (N + nbR - segment) * Cmin < minf) {
                        TryX(v, k);
                    }
                } else {
                    if (k == K) {
                        if (segment == N + nbR) minf = min(minf, f);
                    } else {
                        if (f + (N + nbR - segment) * Cmin < minf) {
                            TryX(Y[k + 1], k + 1);
                        }
                    }
                }
                visited[v] = 0;
                load[k] -= d[v];
                segment--;
                f -= C[s][v];
            }
        }
    }
int checkY(int v, int k) {
    if (v == 0) return 1;
    if (visited[v] == 1) return 0;
    if (load[k] + d[v] > Q) return 0;
    return 1;
}

void TryY(int k) {
    int s = 0;
    if (Y[k - 1] > 0) s = Y[k - 1] + 1;
    for (int v = s; v <= N; v++) {
        if (checkY(v, k) == 1) {
            Y[k] = v;
            if (v > 0) segment++;
            visited[v] = 1;
            load[k] += d[v];
            f += C[0][v];
            if (k < K) TryY(k + 1);
            else {
                nbR = segment;
                TryX(Y[1], 1);
            }
            if (v > 0) segment--;
            visited[v] = 0;
            load[k] -= d[v];
            f -= C[0][v];
        }
    }
}

int main() {
    cin >> N >> K >> Q;
    Y[0]=0;
    for (int i = 1; i <= N; i++) cin >> d[i];
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            cin >> C[i][j];
            if(C[i][j]!=0) Cmin = min(Cmin, C[i][j]);
        }
    }
    for (int i = 1; i <= N; i++) {
        visited[i] = 0;
    }
    for (int i = 1; i <= K; i++) {
        load[i] = 0;
    }
    TryY(1);
    cout << minf;
}
