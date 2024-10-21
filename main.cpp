#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <random>

// constant definitions 
const int DIMENSIONS = 100;         // 增加维度到100
//const int NUM_POINTS = 1000000;     // 100万个数据点
//const int NUM_QUERIES = 1000;       // 1000个查询点

const int NUM_POINTS = 100;     // 100万个数据点
const int NUM_QUERIES = 10;       // 1000个查询点

const int K = 50;                   // 找出50个最近邻


// 数据生成函数 generate the data
void generateData(const std::string& filename) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 100.0);

    std::ofstream file(filename);
    for (int i = 0; i < NUM_POINTS; ++i) {
        for (int j = 0; j < DIMENSIONS; ++j) {
            file << dis(gen);
            if (j < DIMENSIONS - 1) file << ",";
        }
        file << "\n";
    }
    file.close();
}
 
// 生成查询点 generate query points
std::vector<std::vector<double>> generateQueryPoints() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 100.0);

    std::vector<std::vector<double>> queryPoints(NUM_QUERIES, std::vector<double>(DIMENSIONS));
    for (int i = 0; i < NUM_QUERIES; ++i) {
        for (int j = 0; j < DIMENSIONS; ++j) {
            queryPoints[i][j] = dis(gen);
        }
    }
    return queryPoints;
}

double enhancedDistance(const std::vector<double>& a, const std::vector<double>& b) {
    double sum = 0.0;
    double weight;

    // add diff weight
    for (int i = 0; i < DIMENSIONS; ++i) {
        weight = 1.0 + sin(i * M_PI / DIMENSIONS); // Periodic weight
        double diff = a[i] - b[i];
        sum += weight * (diff * diff);

        // non-linear transformation
        if (i % 2 == 0) {
            sum += weight * std::fabs(std::sin(diff));
        }
        else {
            sum += weight * std::fabs(std::cos(diff));
        }
    }
    return std::sqrt(sum);
}

void loadData(const std::string& filename, std::vector<std::vector<double>>& data) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::vector<double> point;
        std::stringstream ss(line);
        std::string value;
        while (std::getline(ss, value, ',')) {
            point.push_back(std::stod(value));
        }
        data.push_back(point);
    }
    file.close();
}

// Batch knn proces__sing
struct KNNResult {
    std::vector<int> indices;
    std::vector<double> distances;
};

std::vector<KNNResult> batchKNN(const std::vector<std::vector<double>>& data,
    const std::vector<std::vector<double>>& queryPoints,
    int k) {
    std::vector<KNNResult> results(queryPoints.size());

    // 串行处理每个查询点 
    // Each query point is processed serially
    for (int q = 0; q < queryPoints.size(); ++q) {
        std::vector<std::pair<double, int>> distances;
        distances.reserve(data.size());

        // 计算与所有点的距离 
        // Calculate the distance from all points
        for (int i = 0; i < data.size(); ++i) {
            double dist = enhancedDistance(data[i], queryPoints[q]);
            distances.push_back({ dist, i });
        }

        // 部分排序，只获取前k个 
        // Partial sorting, where only the top k are taken
        std::partial_sort(distances.begin(),
            distances.begin() + k,
            distances.end());

        // 保存结果
        // Saving the results
        results[q].indices.resize(k);
        results[q].distances.resize(k);
        for (int i = 0; i < k; ++i) {
            results[q].indices[i] = distances[i].second;
            results[q].distances[i] = distances[i].first;
        }
    }

    return results;
}

int main() {
    // 生成数据
    std::string filename = "knn_large_data.txt";
    generateData(filename);

    // 加载数据
    std::vector<std::vector<double>> data;
    std::cout << "Loading data..." << std::endl;
    loadData(filename, data);

    // 生成查询点
    std::vector<std::vector<double>> queryPoints = generateQueryPoints();

    // 计时开始
    auto start = std::chrono::high_resolution_clock::now();

    // 执行批量KNN
    std::vector<KNNResult> results = batchKNN(data, queryPoints, K);

    // 计时结束
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // 输出结果
    std::cout << "Proces__sing time: " << duration.count() << " ms" << std::endl;

    // 输出部分结果示例
    std::cout << "\nFirst query point results:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "Index: " << results[0].indices[i]
            << " Distance: " << results[0].distances[i] << std::endl;
    }

    return 0;
}