#pragma once
#include <array>

#include <array>
#include <iostream>

template<typename T, size_t Rows, size_t Cols>
class Array2D {
private:
    std::array<std::array<T, Cols>, Rows> data;

public:
    // Default constructor
    Array2D() = default;

    // Constructor with initializer list
    Array2D(std::initializer_list<std::initializer_list<T>> init) {
        size_t row = 0;
        for (const auto& row_list : init) {
            size_t col = 0;
            for (const auto& value : row_list) {
                if (row < Rows && col < Cols) {
                    data[row][col] = value;
                }
                col++;
            }
            row++;
        }
    }

    // Access element
    T& operator()(size_t row, size_t col) {
        return data[row][col];
    }

    // Const access element
    const T& operator()(size_t row, size_t col) const {
        return data[row][col];
    }

    // Get number of rows
    size_t rows() const {
        return Rows;
    }

    // Get number of columns
    size_t cols() const {
        return Cols;
    }

    // Print the array
    void print() const {
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};
