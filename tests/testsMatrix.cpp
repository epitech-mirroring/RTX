/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <criterion/criterion.h>
#include "GLSL/Matrix.hpp"

Test(Matrix, Creation_4_4)
{
    auto matrix =
            GLSL::Matrix<4, 4>(0.0,   1.0,  2.0,  3.0,
                               4.0,   5.0,  6.0,  7.0,
                               8.0,   9.0, 10.0, 11.0,
                               12.0, 13.0, 14.0, 15.0);
    for (int i = 0; i < 4; i++) {
        cr_assert_eq(matrix[i][0], i * 4, "i: %d, matrix[i][0]: %f", i, matrix[i][0]);
        cr_assert_eq(matrix[i][1], i * 4 + 1, "i: %d, matrix[i][1]: %f", i, matrix[i][1]);
        cr_assert_eq(matrix[i][2], i * 4 + 2, "i: %d, matrix[i][2]: %f", i, matrix[i][2]);
        cr_assert_eq(matrix[i][3], i * 4 + 3, "i: %d, matrix[i][3]: %f", i, matrix[i][3]);
    }
    printf("Matrix 4x4 creation: OK\n");
}

Test(Matrix, Creation_Not_Squared)
{
    auto matrix =
            GLSL::Matrix<3, 4>(0.0, 1.0, 2.0, 3.0,
                               4.0, 5.0, 6.0, 7.0,
                               8.0, 9.0, 10.0, 11.0);
    for (int i = 0; i < 3; i++) {
        cr_assert_eq(matrix[i][0], i * 4, "i: %d, matrix[i][0]: %f", i, matrix[i][0]);
        cr_assert_eq(matrix[i][1], i * 4 + 1, "i: %d, matrix[i][1]: %f", i, matrix[i][1]);
        cr_assert_eq(matrix[i][2], i * 4 + 2, "i: %d, matrix[i][2]: %f", i, matrix[i][2]);
        cr_assert_eq(matrix[i][3], i * 4 + 3, "i: %d, matrix[i][3]: %f", i, matrix[i][3]);
    }
    printf("Matrix 3x4 creation: OK\n");
}

Test(Matrix, Default_Creation)
{
    auto matrix = GLSL::Matrix<4, 4>();
    for (int i = 0; i < 4; i++) {
        cr_assert_eq(matrix[i][0], 0.0, "i: %d, matrix[i][0]: %f", i, matrix[i][0]);
        cr_assert_eq(matrix[i][1], 0.0, "i: %d, matrix[i][1]: %f", i, matrix[i][1]);
        cr_assert_eq(matrix[i][2], 0.0, "i: %d, matrix[i][2]: %f", i, matrix[i][2]);
        cr_assert_eq(matrix[i][3], 0.0, "i: %d, matrix[i][3]: %f", i, matrix[i][3]);
    }
    printf("Matrix default creation: OK\n");
}

Test(Matrix, Determinant)
{
    auto notSquared = GLSL::Matrix<3, 4>();
    auto oneByOne = GLSL::Matrix<1, 1>(1.0);
    auto twoByTwo = GLSL::Matrix<2, 2>(1.0, 2.0,
                                            3.0, 4.0);
    auto threeByThree = GLSL::Matrix<3, 3>(1.0, 2.0, 3.0,
                                                4.0, 5.0, 6.0,
                                                7.0, 8.0, 9.0);
    auto fourByFour = GLSL::Matrix<4, 4>(1.0, 2.0, 3.0, 4.0,
                                            5.0, 6.0, 7.0, 8.0,
                                            9.0, 10.0, 11.0, 12.0,
                                            13.0, 14.0, 15.0, 16.0);
    auto fiveByFive = GLSL::Matrix<5, 5>();

    cr_assert_eq(notSquared.GetDeterminant(), 0.0, "Determinant for non squared matrix %i but should be 0", notSquared.GetDeterminant());
    printf("Determinant for non squared matrix: OK\n");
    cr_assert_eq(oneByOne.GetDeterminant(), 1.0, "Determinant for 1x1 matrix %i but should be itself (here 1)", oneByOne.GetDeterminant());
    printf("Determinant for 1x1 matrix: OK\n");
    cr_assert_eq(twoByTwo.GetDeterminant(), -2.0, "Determinant for 2x2 matrix %i but should be a*d - b*c (here 1*4 - 2*3 = -2)", twoByTwo.GetDeterminant());
    printf("Determinant for 2x2 matrix: OK\n");
    cr_assert_eq(threeByThree.GetDeterminant(), 0.0, "Determinant for 3x3 matrix %i but should be (a*e*i + b*f*g + c*d*h) - (c*e*g + b*d*i + a*f*h) (here 1*5*9 + 2*6*7 + 3*4*8 - 3*5*7 - 2*4*9 - 1*6*8 = 0)", threeByThree.GetDeterminant());
    printf("Determinant for 3x3 matrix: OK\n");
    cr_assert_eq(fourByFour.GetDeterminant(), 0.0, "Determinant for 4x4 matrix %i but should be 0", fourByFour.GetDeterminant());
    printf("Determinant for 4x4 matrix: OK\n");
    cr_assert_throw(fiveByFive.GetDeterminant(), std::runtime_error);
}

Test(Matrix, Identity)
{
    GLSL::Matrix<4, 4> identity = GLSL::Matrix<4, 4>::Identity();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cr_assert_eq(identity[i][j], i == j ? 1.0 : 0.0, "i: %d, j: %d, identity[i][j]: %f", i, j, identity[i][j]);
        }
    }
    printf("Identity matrix: OK\n");
}

Test(Matrix, Copy) {
    auto matrix = GLSL::Matrix<4, 4>(0.0, 1.0, 2.0, 3.0,
                                                   4.0, 5.0, 6.0, 7.0,
                                                   8.0, 9.0, 10.0, 11.0,
                                                   12.0, 13.0, 14.0, 15.0);
    auto copy = GLSL::Matrix<4, 4>(matrix);
    for (int i = 0; i < 4; i++) {
        cr_assert_eq(copy[i][0], i * 4, "i: %d, copy[i][0]: %f", i, copy[i][0]);
        cr_assert_eq(copy[i][1], i * 4 + 1, "i: %d, copy[i][1]: %f", i, copy[i][1]);
        cr_assert_eq(copy[i][2], i * 4 + 2, "i: %d, copy[i][2]: %f", i, copy[i][2]);
        cr_assert_eq(copy[i][3], i * 4 + 3, "i: %d, copy[i][3]: %f", i, copy[i][3]);
    }
    printf("Matrix copy: OK\n");
    copy[0][0] = 42.0;
    cr_assert_eq(matrix[0][0], 0.0, "Matrix copy is not deep, matrix[0][0]: %f", matrix[0][0]);
    cr_assert_eq(copy[0][0], 42.0, "Matrix copy is not deep, copy[0][0]: %f", copy[0][0]);
    printf("Matrix copy is not deep: OK\n");
}

Test(Matrix, Get_Row) {
    const auto matrix = GLSL::Matrix<4, 4>(0.0, 1.0, 2.0, 3.0,
                                                4.0, 5.0, 6.0, 7.0,
                                                8.0, 9.0, 10.0, 11.0,
                                                12.0, 13.0, 14.0, 15.0);
    GLSL::Vector<4> row = matrix.GetRow(2);
    cr_assert_eq(row[0], 8.0, "row[0]: %f", row[0]);
    cr_assert_eq(row[1], 9.0, "row[1]: %f", row[1]);
    cr_assert_eq(row[2], 10.0, "row[2]: %f", row[2]);
    cr_assert_eq(row[3], 11.0, "row[3]: %f", row[3]);
    printf("Get row: OK\n");
}

Test(Matrix, getRowThrow) {
    const auto matrix = GLSL::Matrix<1, 1>(0.0);
    cr_assert_throw(matrix.GetRow(3), std::out_of_range);
}

Test(Matrix, Get_Column) {
    const auto matrix = GLSL::Matrix<4, 4>(0.0, 1.0, 2.0, 3.0,
                                                4.0, 5.0, 6.0, 7.0,
                                                8.0, 9.0, 10.0, 11.0,
                                                12.0, 13.0, 14.0, 15.0);
    GLSL::Vector<4> column = matrix.GetColumn(2);
    cr_assert_eq(column[0], 2.0, "column[0]: %f", column[0]);
    cr_assert_eq(column[1], 6.0, "column[1]: %f", column[1]);
    cr_assert_eq(column[2], 10.0, "column[2]: %f", column[2]);
    cr_assert_eq(column[3], 14.0, "column[3]: %f", column[3]);
    printf("Get column: OK\n");
}

Test(Matrix, getColumnThrow) {
    const auto matrix = GLSL::Matrix<1, 1>(0.0);
    cr_assert_throw(matrix.GetColumn(3), std::out_of_range);
}

Test(Matrix, Get_Inverse) {
    auto matrix = GLSL::Matrix<2, 2>(4.0, 3.0,
                                        1.0, 1.0);

    GLSL::Matrix<2, 2> inverse = matrix.GetInverse();
    cr_assert_eq(inverse[0][0], 1.0, "inverse[0][0]: %f", inverse[0][0]);
    cr_assert_eq(inverse[0][1], -3.0, "inverse[0][1]: %f", inverse[0][1]);
    cr_assert_eq(inverse[1][0], -1.0, "inverse[1][0]: %f", inverse[1][0]);
    cr_assert_eq(inverse[1][1], 4.0, "inverse[1][1]: %f", inverse[1][1]);
    printf("Get inverse 2x2: OK\n");
    GLSL::Matrix<2, 2> identity = matrix * inverse;
    cr_assert((identity == GLSL::Matrix<2, 2>::Identity()), "2x2_Matrix * inverse != identity");
    printf("2x2_Matrix * inverse == identity: OK\n");

    // 3x3 matrix
    auto matrix3 = GLSL::Matrix<3, 3>(1.0, 2.0, -1.0,
                                            2.0, 1.0, 2.0,
                                            -1.0, 2.0, 1.0);

    GLSL::Matrix<3, 3> inverse3 = matrix3.GetInverse();
    cr_assert_eq(inverse3[0][0], 3.0/16.0, "inverse[0][0]: %f", inverse3[0][0]);
    cr_assert_eq(inverse3[0][1], 1.0/4.0, "inverse[0][1]: %f", inverse3[0][1]);
    cr_assert_eq(inverse3[0][2], -5.0/16.0, "inverse[0][2]: %f", inverse3[0][2]);
    cr_assert_eq(inverse3[1][0], 1.0/4.0, "inverse[1][0]: %f", inverse3[1][0]);
    cr_assert_eq(inverse3[1][1], 0.0, "inverse[1][1]: %f", inverse3[1][1]);
    cr_assert_eq(inverse3[1][2], 1.0/4.0, "inverse[1][2]: %f", inverse3[1][2]);
    cr_assert_eq(inverse3[2][0], -5.0/16.0, "inverse[2][0]: %f", inverse3[2][0]);
    cr_assert_eq(inverse3[2][1], 1.0/4.0, "inverse[2][1]: %f", inverse3[2][1]);
    cr_assert_eq(inverse3[2][2], 3.0/16.0, "inverse[2][2]: %f", inverse3[2][2]);
    printf("Get inverse 3x3: OK\n");
    GLSL::Matrix<3, 3> identity3 = matrix3 * inverse3;
    cr_assert((identity3 == GLSL::Matrix<3, 3>::Identity()), "3x3_Matrix * inverse != identity");
    printf("3x3_Matrix * inverse == identity: OK\n");

    // 4x4 matrix
    auto matrix4 = GLSL::Matrix<4, 4>(1.0, 1.0, 1.0, -1.0,
                                            1.0, 1.0, -1.0, 1.0,
                                            1.0, -1.0, 1.0, 1.0,
                                            -1.0, 1.0, 1.0, 1.0);

    GLSL::Matrix<4, 4> inverse4 = matrix4.GetInverse();
    cr_assert_eq(inverse4[0][0], 1.0/4.0, "inverse[0][0]: %f", inverse4[0][0]);
    cr_assert_eq(inverse4[0][1], 1.0/4.0, "inverse[0][1]: %f", inverse4[0][1]);
    cr_assert_eq(inverse4[0][2], 1.0/4.0, "inverse[0][2]: %f", inverse4[0][2]);
    cr_assert_eq(inverse4[0][3], -1.0/4.0, "inverse[0][3]: %f", inverse4[0][3]);
    cr_assert_eq(inverse4[1][0], 1.0/4.0, "inverse[1][0]: %f", inverse4[1][0]);
    cr_assert_eq(inverse4[1][1], 1.0/4.0, "inverse[1][1]: %f", inverse4[1][1]);
    cr_assert_eq(inverse4[1][2], -1.0/4.0, "inverse[1][2]: %f", inverse4[1][2]);
    cr_assert_eq(inverse4[1][3], 1.0/4.0, "inverse[1][3]: %f", inverse4[1][3]);
    cr_assert_eq(inverse4[2][0], 1.0/4.0, "inverse[2][0]: %f", inverse4[2][0]);
    cr_assert_eq(inverse4[2][1], -1.0/4.0, "inverse[2][1]: %f", inverse4[2][1]);
    cr_assert_eq(inverse4[2][2], 1.0/4.0, "inverse[2][2]: %f", inverse4[2][2]);
    cr_assert_eq(inverse4[2][3], 1.0/4.0, "inverse[2][3]: %f", inverse4[2][3]);
    cr_assert_eq(inverse4[3][0], -1.0/4.0, "inverse[3][0]: %f", inverse4[3][0]);
    cr_assert_eq(inverse4[3][1], 1.0/4.0, "inverse[3][1]: %f", inverse4[3][1]);
    cr_assert_eq(inverse4[3][2], 1.0/4.0, "inverse[3][2]: %f", inverse4[3][2]);
    cr_assert_eq(inverse4[3][3], 1.0/4.0, "inverse[3][3]: %f", inverse4[3][3]);
    printf("Get inverse 4x4: OK\n");
    GLSL::Matrix<4, 4> identity4 = matrix4 * inverse4;
    cr_assert((identity4 == GLSL::Matrix<4, 4>::Identity()), "4x4_Matrix * inverse != identity");
}

Test(Matrix, Get_Inverse_Not_Invertible) {
    auto matrix = GLSL::Matrix<4, 4>(1.0, 2.0, 3.0, 4.0,
                                        5.0, 6.0, 7.0, 8.0,
                                        9.0, 10.0, 11.0, 12.0,
                                        13.0, 14.0, 15.0, 16.0);
    matrix[0][0] = 0.0;
    cr_assert_throw(matrix.GetInverse(), std::runtime_error);
    printf("Get inverse not invertible: OK\n");
}

Test(Matrix, Set_Row) {
    auto matrix = GLSL::Matrix<4, 4>(0.0, 1.0, 2.0, 3.0,
                                        4.0, 5.0, 6.0, 7.0,
                                        8.0, 9.0, 10.0, 11.0,
                                        12.0, 13.0, 14.0, 15.0);
    const auto row = GLSL::Vector<4>(42.0, 42.0, 42.0, 42.0);
    matrix.SetRow(2, row);
    cr_assert_eq(matrix[2][0], 42.0, "matrix[2][0]: %f", matrix[2][0]);
    cr_assert_eq(matrix[2][1], 42.0, "matrix[2][1]: %f", matrix[2][1]);
    cr_assert_eq(matrix[2][2], 42.0, "matrix[2][2]: %f", matrix[2][2]);
    cr_assert_eq(matrix[2][3], 42.0, "matrix[2][3]: %f", matrix[2][3]);
    printf("Set row: OK\n");
}

Test(Matrix, Set_Row_Throw)
{
    auto matrix = GLSL::Matrix<1, 1>(0.0);
    auto row = GLSL::Vector<1>(0.0);
    cr_assert_throw(matrix.SetRow(3, row), std::out_of_range);

}

Test(Matrix, Set_Column) {
    auto matrix = GLSL::Matrix<4, 4>(0.0, 1.0, 2.0, 3.0,
                                        4.0, 5.0, 6.0, 7.0,
                                        8.0, 9.0, 10.0, 11.0,
                                        12.0, 13.0, 14.0, 15.0);
    const auto column = GLSL::Vector<4>(42.0, 42.0, 42.0, 42.0);
    matrix.SetColumn(2, column);
    cr_assert_eq(matrix[0][2], 42.0, "matrix[0][2]: %f", matrix[0][2]);
    cr_assert_eq(matrix[1][2], 42.0, "matrix[1][2]: %f", matrix[1][2]);
    cr_assert_eq(matrix[2][2], 42.0, "matrix[2][2]: %f", matrix[2][2]);
    cr_assert_eq(matrix[3][2], 42.0, "matrix[3][2]: %f", matrix[3][2]);
    printf("Set column: OK\n");
}

Test(Matrix, Set_Column_Throw)
{
    auto matrix = GLSL::Matrix<1, 1>(0.0);
    auto column = GLSL::Vector<1>(0.0);
    cr_assert_throw(matrix.SetColumn(3, column), std::out_of_range);
}

Test(Matrix, equalOperator)
{
    auto matrix1 = GLSL::Matrix<4, 4>();
    auto matrix2 = GLSL::Matrix<4, 4>(0.0, 1.0, 2.0, 3.0,
                                        4.0, 5.0, 6.0, 7.0,
                                        8.0, 9.0, 10.0, 11.0,
                                        12.0, 13.0, 14.0, 15.0);
    matrix1 = matrix2;
    for (int i = 0; i < 4; i++) {
        cr_assert_eq(matrix1[i][0], i * 4, "i: %d, matrix1[i][0]: %f", i, matrix1[i][0]);
        cr_assert_eq(matrix1[i][1], i * 4 + 1, "i: %d, matrix1[i][1]: %f", i, matrix1[i][1]);
        cr_assert_eq(matrix1[i][2], i * 4 + 2, "i: %d, matrix1[i][2]: %f", i, matrix1[i][2]);
        cr_assert_eq(matrix1[i][3], i * 4 + 3, "i: %d, matrix1[i][3]: %f", i, matrix1[i][3]);
    }
}

Test(Matrix, Addition) {
    const auto matrix1 = GLSL::Matrix<4, 4>(0.0, 1.0, 2.0, 3.0,
                                                4.0, 5.0, 6.0, 7.0,
                                                8.0, 9.0, 10.0, 11.0,
                                                12.0, 13.0, 14.0, 15.0);
    const auto matrix2 = GLSL::Matrix<4, 4>(15.0, 14.0, 13.0, 12.0,
                                                11.0, 10.0, 9.0, 8.0,
                                                7.0, 6.0, 5.0, 4.0,
                                                3.0, 2.0, 1.0, 0.0);
    GLSL::Matrix<4, 4> result = matrix1 + matrix2;
    for (int i = 0; i < 4; i++) {
        cr_assert_eq(result[i][0], 15.0, "i: %d, result[i][0]: %f", i, result[i][0]);
        cr_assert_eq(result[i][1], 15.0, "i: %d, result[i][1]: %f", i, result[i][1]);
        cr_assert_eq(result[i][2], 15.0, "i: %d, result[i][2]: %f", i, result[i][2]);
        cr_assert_eq(result[i][3], 15.0, "i: %d, result[i][3]: %f", i, result[i][3]);
    }
    printf("Addition: OK\n");
}

Test(Matrix, Substraction) {
    const auto matrix1 = GLSL::Matrix<4, 4>(0.0, 1.0, 2.0, 3.0,
                                                4.0, 5.0, 6.0, 7.0,
                                                8.0, 9.0, 10.0, 11.0,
                                                12.0, 13.0, 14.0, 15.0);
    const auto matrix2 = GLSL::Matrix<4, 4>(15.0, 16.0, 17.0, 18.0,
                                                19.0, 20.0, 21.0, 22.0,
                                                23.0, 24.0, 25.0, 26.0,
                                                27.0, 28.0, 29.0, 30.0);
    GLSL::Matrix<4, 4> result = matrix1 - matrix2;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cr_assert_eq(result[i][j], -15.0, "result[%d][%d]: %f", i, j, result[i][j]);
        }
    }
    printf("Substraction: OK\n");
}

Test(Matrix, Multiplication) {
    auto matrix1 = GLSL::Matrix<4, 4>(0.0, 1.0, 2.0, 3.0,
                                        4.0, 5.0, 6.0, 7.0,
                                        8.0, 9.0, 10.0, 11.0,
                                        12.0, 13.0, 14.0, 15.0);
    auto matrix2 = GLSL::Matrix<4, 4>(15.0, 14.0, 13.0, 12.0,
                                        11.0, 10.0, 9.0, 8.0,
                                        7.0, 6.0, 5.0, 4.0,
                                        3.0, 2.0, 1.0, 0.0);
    GLSL::Matrix<4, 4> result = matrix1 * matrix2;
    cr_assert_eq(result[0][0], 34.0, "result[0][0]: %f", result[0][0]);
    cr_assert_eq(result[0][1], 28.0, "result[0][1]: %f", result[0][1]);
    cr_assert_eq(result[0][2], 22.0, "result[0][2]: %f", result[0][2]);
    cr_assert_eq(result[0][3], 16.0, "result[0][3]: %f", result[0][3]);
    cr_assert_eq(result[1][0], 178.0, "result[1][0]: %f", result[1][0]);
    cr_assert_eq(result[1][1], 156.0, "result[1][1]: %f", result[1][1]);
    cr_assert_eq(result[1][2], 134.0, "result[1][2]: %f", result[1][2]);
    cr_assert_eq(result[1][3], 112.0, "result[1][3]: %f", result[1][3]);
    cr_assert_eq(result[2][0], 322.0, "result[2][0]: %f", result[2][0]);
    cr_assert_eq(result[2][1], 284.0, "result[2][1]: %f", result[2][1]);
    cr_assert_eq(result[2][2], 246.0, "result[2][2]: %f", result[2][2]);
    cr_assert_eq(result[2][3], 208.0, "result[2][3]: %f", result[2][3]);
    cr_assert_eq(result[3][0], 466.0, "result[3][0]: %f", result[3][0]);
    cr_assert_eq(result[3][1], 412.0, "result[3][1]: %f", result[3][1]);
    cr_assert_eq(result[3][2], 358.0, "result[3][2]: %f", result[3][2]);
    cr_assert_eq(result[3][3], 304.0, "result[3][3]: %f", result[3][3]);
    printf("Multiplication: OK\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cr_assert_eq(matrix1[i][j], i * 4 + j, "i: %d, j: %d, matrix1[i][j]: %f", i, j, matrix1[i][j]);
            cr_assert_eq(matrix2[i][j], 15.0 - (i * 4 + j), "i: %d, j: %d, matrix2[i][j]: %f", i, j, matrix2[i][j]);
        }
    }
    printf("Matrix not changed: OK\n");
    cr_assert(result != (matrix2 * matrix1), "Matrix multiplication is not commutative");
    printf("Matrix multiplication is not commutative: OK\n");
}

Test(Matrix, Multiplication_Not_Same_Size) {
    auto matrix1 = GLSL::Matrix<4, 4>(0.0, 1.0, 2.0, 3.0,
                                        4.0, 5.0, 6.0, 7.0,
                                        8.0, 9.0, 10.0, 11.0,
                                        12.0, 13.0, 14.0, 15.0);
    auto matrix2 = GLSL::Matrix<4, 3>(15.0, 14.0, 13.0,
                                        11.0, 10.0, 9.0,
                                        7.0, 6.0, 5.0,
                                        3.0, 2.0, 1.0);
    GLSL::Matrix<4, 3> result = matrix1 * matrix2;
    cr_assert_eq(result[0][0], 34.0, "result[0][0]: %f", result[0][0]);
    cr_assert_eq(result[0][1], 28.0, "result[0][1]: %f", result[0][1]);
    cr_assert_eq(result[0][2], 22.0, "result[0][2]: %f", result[0][2]);
    cr_assert_eq(result[1][0], 178.0, "result[1][0]: %f", result[1][0]);
    cr_assert_eq(result[1][1], 156.0, "result[1][1]: %f", result[1][1]);
    cr_assert_eq(result[1][2], 134.0, "result[1][2]: %f", result[1][2]);
    cr_assert_eq(result[2][0], 322.0, "result[2][0]: %f", result[2][0]);
    cr_assert_eq(result[2][1], 284.0, "result[2][1]: %f", result[2][1]);
    cr_assert_eq(result[2][2], 246.0, "result[2][2]: %f", result[2][2]);
    cr_assert_eq(result[3][0], 466.0, "result[3][0]: %f", result[3][0]);
    cr_assert_eq(result[3][1], 412.0, "result[3][1]: %f", result[3][1]);
    cr_assert_eq(result[3][2], 358.0, "result[3][2]: %f", result[3][2]);
    printf("Multiplication not same size: OK\n");
}

Test(Matrix, Multiplication_With_Vector) {
    const auto matrix = GLSL::Matrix<4, 4>(0.0, 1.0, 2.0, 3.0,
                                                4.0, 5.0, 6.0, 7.0,
                                                8.0, 9.0, 10.0, 11.0,
                                                12.0, 13.0, 14.0, 15.0);
    const auto vector = GLSL::Vector<4>(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> result = matrix * vector;
    cr_assert_eq(result[0], 20.0, "result[0]: %f", result[0]);
    cr_assert_eq(result[1], 60.0, "result[1]: %f", result[1]);
    cr_assert_eq(result[2], 100.0, "result[2]: %f", result[2]);
    cr_assert_eq(result[3], 140.0, "result[3]: %f", result[3]);
    printf("Multiplication with vector: OK\n");
}

Test(Matrix, Opperation_With_Scalars) {
    // Addition
    const auto matrix = GLSL::Matrix<4, 4>(0.0, 1.0, 2.0, 3.0,
                                                4.0, 5.0, 6.0, 7.0,
                                                8.0, 9.0, 10.0, 11.0,
                                                12.0, 13.0, 14.0, 15.0);
    auto result = matrix + 1.0;
    for (int i = 0; i < 4; i++) {
        cr_assert_eq(result[i][0], i * 4 + 1, "i: %d, result[i][0]: %f", i, result[i][0]);
        cr_assert_eq(result[i][1], i * 4 + 2, "i: %d, result[i][1]: %f", i, result[i][1]);
        cr_assert_eq(result[i][2], i * 4 + 3, "i: %d, result[i][2]: %f", i, result[i][2]);
        cr_assert_eq(result[i][3], i * 4 + 4, "i: %d, result[i][3]: %f", i, result[i][3]);
    }
    printf("Addition with scalar: OK\n");

    // Substraction
    result = matrix - 1.0;
    for (int i = 0; i < 4; i++) {
        cr_assert_eq(result[i][0], i * 4 - 1, "i: %d, result[i][0]: %f", i, result[i][0]);
        cr_assert_eq(result[i][1], i * 4, "i: %d, result[i][1]: %f", i, result[i][1]);
        cr_assert_eq(result[i][2], i * 4 + 1, "i: %d, result[i][2]: %f", i, result[i][2]);
        cr_assert_eq(result[i][3], i * 4 + 2, "i: %d, result[i][3]: %f", i, result[i][3]);
    }
    printf("Substraction with scalar: OK\n");

    // Multiplication
    result = matrix * 2.0;
    for (int i = 0; i < 4; i++) {
        cr_assert_eq(result[i][0], i * 8, "i: %d, result[i][0]: %f", i, result[i][0]);
        cr_assert_eq(result[i][1], i * 8 + 2, "i: %d, result[i][1]: %f", i, result[i][1]);
        cr_assert_eq(result[i][2], i * 8 + 4, "i: %d, result[i][2]: %f", i, result[i][2]);
        cr_assert_eq(result[i][3], i * 8 + 6, "i: %d, result[i][3]: %f", i, result[i][3]);
    }
    printf("Multiplication with scalar: OK\n");

    // Division
    result = matrix / 2.0;
    for (int i = 0; i < 4; i++) {
        cr_assert_eq(result[i][0], i * 2, "i: %d, result[i][0]: %f", i, result[i][0]);
        cr_assert_eq(result[i][1], i * 2 + 0.5, "i: %d, result[i][1]: %f", i, result[i][1]);
        cr_assert_eq(result[i][2], i * 2 + 1.0, "i: %d, result[i][2]: %f", i, result[i][2]);
        cr_assert_eq(result[i][3], i * 2 + 1.5, "i: %d, result[i][3]: %f", i, result[i][3]);
    }
    printf("Division with scalar: OK\n");
    printf("Opperation with scalars: OK\n");
}

Test(MatrixFactory, Translation) {
    GLSL::Matrix<4,4> translation = GLSL::MatrixFactory::TranslationMatrix(1.0, 2.0, 3.0);
    cr_assert_eq(translation[0][0], 1.0, "translation[0][0]: %f", translation[0][0]);
    cr_assert_eq(translation[0][1], 0.0, "translation[0][1]: %f", translation[0][1]);
    cr_assert_eq(translation[0][2], 0.0, "translation[0][2]: %f", translation[0][2]);
    cr_assert_eq(translation[0][3], 1.0, "translation[0][3]: %f", translation[0][3]);
    cr_assert_eq(translation[1][0], 0.0, "translation[1][0]: %f", translation[1][0]);
    cr_assert_eq(translation[1][1], 1.0, "translation[1][1]: %f", translation[1][1]);
    cr_assert_eq(translation[1][2], 0.0, "translation[1][2]: %f", translation[1][2]);
    cr_assert_eq(translation[1][3], 2.0, "translation[1][3]: %f", translation[1][3]);
    cr_assert_eq(translation[2][0], 0.0, "translation[2][0]: %f", translation[2][0]);
    cr_assert_eq(translation[2][1], 0.0, "translation[2][1]: %f", translation[2][1]);
    cr_assert_eq(translation[2][2], 1.0, "translation[2][2]: %f", translation[2][2]);
    cr_assert_eq(translation[2][3], 3.0, "translation[2][3]: %f", translation[2][3]);
    cr_assert_eq(translation[3][0], 0.0, "translation[3][0]: %f", translation[3][0]);
    cr_assert_eq(translation[3][1], 0.0, "translation[3][1]: %f", translation[3][1]);
    cr_assert_eq(translation[3][2], 0.0, "translation[3][2]: %f", translation[3][2]);
    cr_assert_eq(translation[3][3], 1.0, "translation[3][3]: %f", translation[3][3]);
    printf("Translation matrix: OK\n");
}

Test(MatrixFactory, Scale) {
    GLSL::Matrix<4,4> scale = GLSL::MatrixFactory::ScaleMatrix(1.0, 2.0, 3.0);
    cr_assert_eq(scale[0][0], 1.0, "scale[0][0]: %f", scale[0][0]);
    cr_assert_eq(scale[0][1], 0.0, "scale[0][1]: %f", scale[0][1]);
    cr_assert_eq(scale[0][2], 0.0, "scale[0][2]: %f", scale[0][2]);
    cr_assert_eq(scale[0][3], 0.0, "scale[0][3]: %f", scale[0][3]);
    cr_assert_eq(scale[1][0], 0.0, "scale[1][0]: %f", scale[1][0]);
    cr_assert_eq(scale[1][1], 2.0, "scale[1][1]: %f", scale[1][1]);
    cr_assert_eq(scale[1][2], 0.0, "scale[1][2]: %f", scale[1][2]);
    cr_assert_eq(scale[1][3], 0.0, "scale[1][3]: %f", scale[1][3]);
    cr_assert_eq(scale[2][0], 0.0, "scale[2][0]: %f", scale[2][0]);
    cr_assert_eq(scale[2][1], 0.0, "scale[2][1]: %f", scale[2][1]);
    cr_assert_eq(scale[2][2], 3.0, "scale[2][2]: %f", scale[2][2]);
    cr_assert_eq(scale[2][3], 0.0, "scale[2][3]: %f", scale[2][3]);
    cr_assert_eq(scale[3][0], 0.0, "scale[3][0]: %f", scale[3][0]);
    cr_assert_eq(scale[3][1], 0.0, "scale[3][1]: %f", scale[3][1]);
    cr_assert_eq(scale[3][2], 0.0, "scale[3][2]: %f", scale[3][2]);
    cr_assert_eq(scale[3][3], 1.0, "scale[3][3]: %f", scale[3][3]);
    printf("Scale matrix: OK\n");
}

Test(Matrix, Operator_Bracket_Throw)
{
    const auto matrix = GLSL::Matrix<1, 1>(0.0);
    cr_assert_throw(matrix[3], std::out_of_range);
}

Test(Matrix, Operator_Bracket_Throw_2)
{
    auto matrix = GLSL::Matrix<1, 1>(0.0);
    cr_assert_throw(matrix[3], std::out_of_range);
}
