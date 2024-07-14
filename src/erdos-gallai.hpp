#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using Matrix = std::vector<std::vector<int>>;

bool CheckErdosGallai(const std::vector<int>& seq) {
    int n = seq.size();
    int sum = 0;
    for (int k = 1; k <= n; k++) {
        sum += seq[k - 1];
        int left = 0;
        for (int i = 0; i < k; i++) left += seq[i];
        int right = k * (k - 1);
        for (int i = k; i < n; i++) right += std::min(seq[i], k);

        if (left > right) return false;
    }
    return sum % 2 == 0;
}

Matrix StructGraph(std::vector<int> seq) {
    int sz = seq.size();
    int s = 0, p = -1;
    for (int i = 0; i < sz; i++) {
        s += seq[i];
        if (seq[i] > 0) p = std::max(p, i);
    }
    if (s == 0 && p == -1) {
        return Matrix(sz, std::vector<int>(sz, 0));
    }
    int t = p - 1;
    for (int i = 0; i < p - 1; i++) {
        if (seq[i] > seq[i + 1]) {
            t = i;
            break;
        }
    }
    // add: (t, p)
    seq[t]--;
    seq[p]--;
    auto ret = StructGraph(seq);
    if (ret[t][p] == 0) {
        ret[t][p] = 1;
        ret[p][t] = 1;
        return ret;
    }

    int m = -1;
    for (int i = 0; i < sz; i++) {
        if (i == t || i == p) continue;
        if (ret[i][t] == 0) {
            m = i;
            break;
        }
    }

    assert(m >= 0);

    int n = -1;
    for (int i = 0; i < sz; i++) {
        if (ret[i][m] = 1 && ret[i][p] == 0) {
            n = i;
            break;
        }
    }

    assert(n >= 0);

    ret[m][n] = 0;
    ret[n][m] = 0;
    ret[m][t] = 1;
    ret[t][m] = 1;
    ret[m][p] = 1;
    ret[p][m] = 1;

    return ret;
}
