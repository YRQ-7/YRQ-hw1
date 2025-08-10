#include "algebra.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EPS 1e-9

Matrix create_matrix(int rows, int cols)
{
    Matrix m;
    if (rows <= 0 || rows > MAX_MATRIX_SIZE || cols <= 0 || cols > MAX_MATRIX_SIZE) {
        m.rows = 0;
        m.cols = 0;
        return m;
    }
    
    m.rows = rows;
    m.cols = cols;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m.data[i][j] = 0.0;
        }
    }
    
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    
    Matrix result = create_matrix(a.rows, a.cols);
    
    // 矩阵加法
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    
    return result;
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    
    Matrix result = create_matrix(a.rows, a.cols);
    
    // 矩阵减法
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    
    return result;
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    if (a.cols != b.rows) {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }
    
    Matrix result = create_matrix(a.rows, b.cols);
    
    // 矩阵乘法
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            result.data[i][j] = 0;  // 初始化
            for (int k = 0; k < a.cols; k++) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    
    return result;
}

Matrix scale_matrix(Matrix a, double k)
{
    Matrix result = create_matrix(a.rows, a.cols);
    
    // 矩阵数乘
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] * k;
        }
    }
    
    return result;
}

Matrix transpose_matrix(Matrix a)
{
    Matrix result = create_matrix(a.cols, a.rows);
    
    // 矩阵转置
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[j][i] = a.data[i][j];
        }
    }
    
    return result;
}

// 辅助函数
static double determinant(Matrix a, int n) {
    double det = 0;
    Matrix submat = create_matrix(n - 1, n - 1);
    
    if (n == 1)
        return a.data[0][0];
    
    int sign = 1;
    for (int f = 0; f < n; f++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j != f) {
                    submat.data[subi][subj] = a.data[i][j];
                    subj++;
                }
            }
            subi++;
        }
        det += sign * a.data[0][f] * determinant(submat, n - 1);
        sign = -sign;
    }
    return det;
}

double det_matrix(Matrix a)
{
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    
    if (a.rows == 0) return 0;
    
    return determinant(a, a.rows);
}

Matrix inv_matrix(Matrix a)
{
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }
    
    int n = a.rows;
    if (n == 0) return create_matrix(0, 0);
    
    double det = det_matrix(a);
    if (fabs(det) < EPS) {
        printf("Error: The matrix is singular.\n");
        return create_matrix(0, 0);
    }
    
    Matrix adj = create_matrix(n, n);
    Matrix submat = create_matrix(n - 1, n - 1);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int subi = 0, subj = 0;
            for (int row = 0; row < n; row++) {
                for (int col = 0; col < n; col++) {
                    if (row != i && col != j) {
                        submat.data[subi][subj] = a.data[row][col];
                        subj++;
                        if (subj == n - 1) {
                            subj = 0;
                            subi++;
                        }
                    }
                }
            }
            
            adj.data[i][j] = pow(-1, i + j) * determinant(submat, n - 1);
        }
    }
    
    Matrix inv = transpose_matrix(adj);
    inv = scale_matrix(inv, 1.0 / det);
    
    return inv;
}

int rank_matrix(Matrix a)
{
    int rows = a.rows;
    int cols = a.cols;
    if (rows == 0 || cols == 0) return 0;
    
    double mat[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mat[i][j] = a.data[i][j];
        }
    }
    
    int rank = 0;
    int row = 0;
    
    for (int col = 0; col < cols && row < rows; col++) {
        int pivot_row = -1;
        for (int i = row; i < rows; i++) {
            if (fabs(mat[i][col]) > EPS) {
                pivot_row = i;
                break;
            }
        }
        
        if (pivot_row == -1) {
            continue; 
        }
        
        // 交换行
        if (pivot_row != row) {
            for (int j = col; j < cols; j++) {
                double temp = mat[row][j];
                mat[row][j] = mat[pivot_row][j];
                mat[pivot_row][j] = temp;
            }
        }
        
        // 消去下方元素
        for (int i = row + 1; i < rows; i++) {
            double factor = mat[i][col] / mat[row][col];
            for (int j = col; j < cols; j++) {
                mat[i][j] -= factor * mat[row][j];
            }
        }
        
        row++;
        rank++;
    }
    
    return rank;
}

double trace_matrix(Matrix a)
{
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return 0.0;
    }
    
    // 计算迹
    double trace = 0.0;
    for (int i = 0; i < a.rows; i++) {
        trace += a.data[i][i];
    }
    
    return trace;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}
