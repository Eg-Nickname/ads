#ifndef MATRIX_GRAPH
#define MATRIX_GRAPH

#include <cstdint>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>
template <typename VV, typename EV>
class MatrixGraph {
    std::unordered_map<uint32_t, uint32_t> vertex_index_map{};
    std::unordered_map<uint32_t, uint32_t> index_vertex_map{};

    std::vector<std::vector<bool>> matrix{};

    std::unordered_map<std::pair<uint32_t, uint32_t>, EV> egde_value_map{};

    public:
    bool adjacent(uint32_t x, uint32_t y) {
        uint32_t x_idx = vertex_index_map[x];
        uint32_t y_idx = vertex_index_map[x];
        return matrix[x_idx][y_idx];
    }

    std::vector<uint32_t> neighbours(uint32_t x) {}

    void addVertex(uint32_t x) {
        if (vertex_index_map.contains(x)) {
            return;
        }
        vertex_index_map[x] = matrix.size();
        index_vertex_map[vertex_index_map[x]] = x;

        for (auto& r : matrix) {
            r.push_back(false);
        }
        matrix.push_back(std::vector<bool>(matrix[0].size(), false));
    }

    void removeVertex(uint32_t x) {
        uint32_t x_idx = vertex_index_map[x];
        vertex_index_map.erase(x);
        uint32_t swap_element = index_vertex_map[matrix.size() - 1];
        vertex_index_map[swap_element] = x_idx;
        index_vertex_map.erase(index_vertex_map[matrix.size() - 1]);
        index_vertex_map[x_idx] = swap_element;
        std::swap(matrix[x_idx], matrix[matrix.size() - 1]);
        matrix.pop_back();
    }

    void addEdge(uint32_t x, uint32_t y) {}

    void removeEdge(uint32_t x, uint32_t y) {}

    VV getVertexValue(uint32_t x) {}

    void setVertexValue(uint32_t x, VV v) {}

    EV getEdgeValue(uint32_t x, uint32_t y) {}

    void setEdgeValue(uint32_t x, uint32_t y, EV v) {}
};

#endif