# include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

// Compute Euclidean distance between two points
double dist(const Point& a, const Point& b) {
    return hypot(a.x - b.x, a.y - b.y);
}

// Weight function: returns the perimeter of the triangle (can be replaced)
double weight(const Point& a, const Point& b, const Point& c) {
    return dist(a, b) + dist(b, c) + dist(c, a);
}

// Optimal Polygon Triangulation using DP
double minTriangulation(const vector<Point>& polygon) {
    int n = polygon.size();
    vector<vector<double>> dp(n, vector<double>(n, 0.0));

    // gap is the distance between i and j
    for (int gap = 2; gap < n; ++gap) {
        for (int i = 0; i + gap < n; ++i) {
            int j = i + gap;
            dp[i][j] = numeric_limits<double>::infinity();
            for (int k = i + 1; k < j; ++k) {
                double cost = dp[i][k] + dp[k][j] +
                              weight(polygon[i], polygon[k], polygon[j]);
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    // Example convex polygon (square)
    vector<Point> polygon = {
        {0, 0},
        {1, 0},
        {1, 1},
        {0, 1}
    };

    double result = minTriangulation(polygon);
    cout << "Minimum triangulation cost: " << result << endl;

    return 0;
}
