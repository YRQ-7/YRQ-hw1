#include "algebra.h"
#include <stdio.h>

void input_matrix(Matrix *mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            scanf("%lf", &(mat->data[i][j]));
        }
    }
}

int main() {
    int choice;
    Matrix a, b, result;
    int rows, cols;
    double k;

    while (1) {
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1:
                scanf("%d %d", &rows, &cols);
                a = create_matrix(rows, cols);
                b = create_matrix(rows, cols);
                input_matrix(&a);
                input_matrix(&b);
                result = add_matrix(a, b);
                if (result.rows != 0) {
                    print_matrix(result);
                }
                break;

            case 2:
                scanf("%d %d", &rows, &cols);
                a = create_matrix(rows, cols);
                b = create_matrix(rows, cols);
                input_matrix(&a);
                input_matrix(&b);
                result = sub_matrix(a, b);
                if (result.rows != 0) {
                    print_matrix(result);
                }
                break;

            case 3:
                scanf("%d %d", &rows, &cols);
                a = create_matrix(rows, cols);
                input_matrix(&a);
                int b_rows, b_cols;
                scanf("%d %d", &b_rows, &b_cols);
                b = create_matrix(b_rows, b_cols);
                input_matrix(&b);
                result = mul_matrix(a, b);
                if (result.rows != 0) {
                    print_matrix(result);
                }
                break;

            case 4:
                scanf("%d %d", &rows, &cols);
                a = create_matrix(rows, cols);
                input_matrix(&a);
                scanf("%lf", &k);
                result = scale_matrix(a, k);
                print_matrix(result);
                break;

            case 5:
                scanf("%d %d", &rows, &cols);
                a = create_matrix(rows, cols);
                input_matrix(&a);
                result = transpose_matrix(a);
                print_matrix(result);
                break;

            case 6:
                scanf("%d", &rows);
                a = create_matrix(rows, rows);
                input_matrix(&a);
                double det = det_matrix(a);
                if (a.rows == a.cols && a.rows != 0) {
                    printf("%.2f\n", det);
                }
                break;

            case 7:
                scanf("%d", &rows);
                a = create_matrix(rows, rows);
                input_matrix(&a);
                result = inv_matrix(a);
                if (result.rows != 0) {
                    print_matrix(result);
                }
                break;

            case 8:
                scanf("%d %d", &rows, &cols);
                a = create_matrix(rows, cols);
                input_matrix(&a);
                int rank = rank_matrix(a);
                printf("%d\n", rank);
                break;

            case 9:
                scanf("%d", &rows);
                a = create_matrix(rows, rows);
                input_matrix(&a);
                double trace = trace_matrix(a);
                if (a.rows == a.cols && a.rows != 0) {
                    printf("%.2f\n", trace);
                }
                break;

            default:
                break;
        }
    }

    return 0;
}