/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include "GLSL/Vector.hpp"

static bool cmp_double(double a, double b)
{
    return std::abs(a - b) < 0.0001;
}

Test(Vector, constructor)
{
    GLSL::Vector<3> vec;
    cr_assert_eq(vec[0], 0);
    cr_assert_eq(vec[1], 0);
    cr_assert_eq(vec[2], 0);
}

Test(Vector, constructor_values)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    cr_assert_eq(vec[0], 1.0);
    cr_assert_eq(vec[1], 2.0);
    cr_assert_eq(vec[2], 3.0);
}

Test(Vector, copy_constructor)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2(vec);
    cr_assert_eq(vec2[0], vec[0]);
    cr_assert_eq(vec2[1], vec[1]);
    cr_assert_eq(vec2[2], vec[2]);
}

Test(Vector, length)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    cr_assert_eq(cmp_double(vec.length(), 3.74165738677), true);
}

Test(Vector, dot)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2(4.0, 5.0, 6.0);
    cr_assert_eq(cmp_double(vec.dot(vec2), 32.0), true);
}

Test(Vector, operator_brackets)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    cr_assert_eq(vec[0], 1.0);
    cr_assert_eq(vec[1], 2.0);
    cr_assert_eq(vec[2], 3.0);
}

Test(Vector, operator_brackets_const)
{
    const GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    cr_assert_eq(vec[0], 1.0);
    cr_assert_eq(vec[1], 2.0);
    cr_assert_eq(vec[2], 3.0);
}

Test(Vector, operator_equal)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2(1.0, 2.0, 3.0);
    cr_assert_eq(vec, vec2);
}

Test(Vector, operator_not_equal)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2(1.0, 2.0, 4.0);
    cr_assert_neq(vec, vec2);
}

Test(Vector, operator_plus)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2(4.0, 5.0, 6.0);
    GLSL::Vector<3> vec3 = vec + vec2;
    cr_assert_eq(vec3[0], 5.0);
    cr_assert_eq(vec3[1], 7.0);
    cr_assert_eq(vec3[2], 9.0);
}

Test(Vector, operator_minus)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2(4.0, 5.0, 6.0);
    GLSL::Vector<3> vec3 = vec - vec2;
    cr_assert_eq(vec3[0], -3.0);
    cr_assert_eq(vec3[1], -3.0);
    cr_assert_eq(vec3[2], -3.0);
}

Test(Vector, operator_multiply)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2(4.0, 5.0, 6.0);
    GLSL::Vector<3> vec3 = vec * vec2;
    cr_assert_eq(vec3[0], -3.0);
    cr_assert_eq(vec3[1], 6.0);
    cr_assert_eq(vec3[2], -3.0);
}

Test(Vector, operator_divide)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2(4.0, 5.0, 6.0);
    GLSL::Vector<3> vec3 = vec / vec2;
    cr_assert_eq(vec3[0], 0.25);
    cr_assert_eq(vec3[1], 0.4);
    cr_assert_eq(vec3[2], 0.5);
}

Test(Vector, operator_divide_zero)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2(0.0, 0.0, 0.0);
    cr_assert_throw(vec / vec2, std::invalid_argument);
}

Test(Vector, operator_multiply_scalar)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec * 2;
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 6.0);
}

Test(Vector, operator_divide_scalar)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec / 2;
    cr_assert_eq(vec2[0], 0.5);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.5);
}

Test(Vector, operator_plus_equal)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2(4.0, 5.0, 6.0);
    vec += vec2;
    cr_assert_eq(vec[0], 5.0);
    cr_assert_eq(vec[1], 7.0);
    cr_assert_eq(vec[2], 9.0);
}

Test(Vector, operator_minus_equal)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2(4.0, 5.0, 6.0);
    vec -= vec2;
    cr_assert_eq(vec[0], -3.0);
    cr_assert_eq(vec[1], -3.0);
    cr_assert_eq(vec[2], -3.0);
}

Test(Vector, operator_multiply_equal)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2(4.0, 5.0, 6.0);
    vec *= vec2;
    cr_assert(cmp_double(vec[0], -3.0));
    cr_assert(cmp_double(vec[1], 6.0));
    cr_assert(cmp_double(vec[2], -3.0));
}

Test(Vector, operator_divide_equal)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2(4.0, 5.0, 6.0);
    vec /= vec2;
    cr_assert_eq(vec[0], 0.25);
    cr_assert_eq(vec[1], 0.4);
    cr_assert_eq(vec[2], 0.5);
}

Test(Vector, operator_multiply_scalar_equal)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    vec *= 2;
    cr_assert_eq(vec[0], 2.0);
    cr_assert_eq(vec[1], 4.0);
    cr_assert_eq(vec[2], 6.0);
}

Test(Vector, operator_divide_scalar_equal)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    vec /= 2.0;
    cr_assert(cmp_double(vec[0], 0.5));
    cr_assert(cmp_double(vec[1], 1.0));
    cr_assert(cmp_double(vec[2], 1.5));
}

Test(Vector, Normalize) {
    const GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> r = vec.normalize();
    cr_assert_eq(cmp_double(r.length(), 1.0), true);
    cr_assert_eq(cmp_double(r[0], 0.267261), true);
    cr_assert_eq(cmp_double(r[1], 0.534522), true);
    cr_assert_eq(cmp_double(r[2], 0.801784), true);
}

Test(Vector, x)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    const double x = vec.x()[0];
    cr_assert_eq(x, 1.0);
}

Test(Vector, y)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    double y = vec.y()[0];
    cr_assert_eq(y, 2.0);
}

Test(Vector, z)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    double z = vec.z()[0];
    cr_assert_eq(z, 3.0);
}

Test(Vector, w)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    double w = vec.w()[0];
    cr_assert_eq(w, 4.0);
}

Test(Vector, xx)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<2> vec2 = vec.xx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
}

Test(Vector, xy)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<2> vec2 = vec.xy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
}

Test(Vector, xz)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<2> vec2 = vec.xz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
}

Test(Vector, xw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.xw();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
}

Test(Vector, yx)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<2> vec2 = vec.yx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
}

Test(Vector, yy)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<2> vec2 = vec.yy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
}

Test(Vector, yz)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<2> vec2 = vec.yz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
}

Test(Vector, yw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.yw();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
}

Test(Vector, zx)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<2> vec2 = vec.zx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
}

Test(Vector, zy)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<2> vec2 = vec.zy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
}

Test(Vector, zz)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<2> vec2 = vec.zz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
}

Test(Vector, zw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.zw();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
}

Test(Vector, xxx)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.xxx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, xxy)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.xxy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, xxz)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.xxz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, xxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.xxw();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, xyx)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.xyx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, xyy)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.xyy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, xyz)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.xyz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, xyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.xyw();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, xzx)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.xzx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, xzy)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.xzy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, xzz)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.xzz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, xzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.xzw();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, xwx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.xwx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, xwy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.xwy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, xwz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.xwz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, xww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.xww();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, yxx)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.yxx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, yxy)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.yxy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, yxz)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.yxz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, yxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.yxw();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, yyx)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.yyx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, yyy)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.yyy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, yyz)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.yyz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, yyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.yyw();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, yzx)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.yzx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, yzy)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.yzy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, yzz)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.yzz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, yzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.yzw();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, ywx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.ywx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, ywy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.ywy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, ywz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.ywz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, yww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.yww();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, zxx)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.zxx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, zxy)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.zxy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, zxz)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.zxz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, zxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.zxw();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, zyx)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.zyx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, zyy)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.zyy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, zyz)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.zyz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, zyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.zyw();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, zzx)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.zzx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, zzy)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.zzy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, zzz)
{
    GLSL::Vector<3> vec(1.0, 2.0, 3.0);
    GLSL::Vector<3> vec2 = vec.zzz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, zzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.zzw();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, zwx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.zwx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, zwy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.zwy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, zwz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.zwz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, zww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.zww();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, wxx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.wxx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, wxy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.wxy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, wxz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.wxz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, wxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.wxw();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, wyx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.wyx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, wyy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.wyy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, wyz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.wyz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, wyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.wyw();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, wzx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.wzx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, wzy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.wzy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, wzz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.wzz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, wzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.wzw();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, wwx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.wwx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, wwy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.wwy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, wwz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.wwz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, www)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.www();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, xxxx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xxxx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, xxxy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xxxy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, xxxz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xxxz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, xxxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xxxw();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, xxyx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xxyx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, xxyy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xxyy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, xxyz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xxyz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, xxyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xxyw();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, xxzx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xxzx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, xxzy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xxzy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, xxzz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xxzz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, xxzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xxzw();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, xxwx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xxwx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, xxwy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xxwy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, xxwz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xxwz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, xxww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xxww();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, xyxx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xyxx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, xyxy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xyxy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, xyxz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xyxz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, xyxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xyxw();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, xyyx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xyyx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, xyyy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xyyy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, xyyz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xyyz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, xyyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xyyw();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, xyzx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xyzx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, xyzy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xyzy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, xyzz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xyzz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, xyzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xyzw();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, xywx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xywx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, xywy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xywy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, xywz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xywz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, xyww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xyww();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, xzxx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xzxx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, xzxy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xzxy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, xzxz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xzxz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, xzxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xzxw();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, xzyx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xzyx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, xzyy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xzyy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, xzyz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xzyz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, xzyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xzyw();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, xzzx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xzzx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, xzzy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xzzy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, xzzz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xzzz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, xzzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xzzw();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, xzwx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xzwx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, xzwy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xzwy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, xzwz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xzwz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, xzww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xzww();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, xwxx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xwxx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, xwxy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xwxy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, xwxz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xwxz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, xwxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xwxw();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, xwyx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xwyx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, xwyy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xwyy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, xwyz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xwyz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, xwyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xwyw();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, xwzx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xwzx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, xwzy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xwzy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, xwzz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xwzz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, xwzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xwzw();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, xwwx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xwwx();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, xwwy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xwwy();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, xwwz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xwwz();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, xwww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.xwww();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, yxxx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yxxx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, yxxy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yxxy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, yxxz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yxxz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, yxxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yxxw();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, yxyx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yxyx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, yxyy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yxyy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, yxyz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yxyz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, yxyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yxyw();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, yxzx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yxzx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, yxzy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yxzy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, yxzz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yxzz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, yxzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yxzw();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, yxwx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yxwx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, yxwy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yxwy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, yxwz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yxwz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, yxww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yxww();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, yyxx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yyxx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, yyxy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yyxy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, yyxz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yyxz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, yyxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yyxw();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, yyyx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yyyx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, yyyy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yyyy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, yyyz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yyyz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, yyyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yyyw();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, yyzx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yyzx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, yyzy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yyzy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, yyzz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yyzz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, yyzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yyzw();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, yywx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yywx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, yywy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yywy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, yywz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yywz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, yyww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yyww();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, yzxx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yzxx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, yzxy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yzxy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, yzxz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yzxz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, yzxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yzxw();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, yzyx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yzyx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, yzyy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yzyy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, yzyz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yzyz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, yzyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yzyw();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, yzzx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yzzx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, yzzy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yzzy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, yzzz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yzzz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, yzzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yzzw();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, yzwx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yzwx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, yzwy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yzwy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, yzwz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yzwz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, yzww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.yzww();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, ywxx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ywxx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, ywxy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ywxy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, ywxz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ywxz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, ywxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ywxw();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, ywyx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ywyx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, ywyy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ywyy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, ywyz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ywyz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, ywyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ywyw();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, ywzx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ywzx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, ywzy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ywzy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, ywzz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ywzz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, ywzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ywzw();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, ywwx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ywwx();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, ywwy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ywwy();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, ywwz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ywwz();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, ywww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ywww();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, zxxx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zxxx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, zxxy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zxxy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, zxxz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zxxz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, zxxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zxxw();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, zxyx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zxyx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, zxyy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zxyy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, zxyz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zxyz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, zxyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zxyw();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, zxzx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zxzx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, zxzy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zxzy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, zxzz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zxzz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, zxzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zxzw();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, zxwx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zxwx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, zxwy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zxwy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, zxwz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zxwz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, zxww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zxww();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, zyxx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zyxx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, zyxy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zyxy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, zyxz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zyxz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, zyxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zyxw();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, zyyx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zyyx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, zyyy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zyyy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, zyyz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zyyz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, zyyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zyyw();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, zyzx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zyzx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, zyzy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zyzy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, zyzz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zyzz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, zyzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zyzw();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, zywx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zywx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, zywy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zywy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, zywz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zywz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, zyww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zyww();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, zzxx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zzxx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, zzxy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zzxy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, zzxz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zzxz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, zzxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zzxw();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, zzyx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zzyx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, zzyy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zzyy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, zzyz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zzyz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, zzyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zzyw();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, zzzx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zzzx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, zzzy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zzzy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, zzzz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zzzz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, zzzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zzzw();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, zzwx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zzwx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, zzwy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zzwy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, zzwz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zzwz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, zzww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zzww();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, zwxx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zwxx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, zwxy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zwxy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, zwxz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zwxz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, zwxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zwxw();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, zwyx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zwyx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, zwyy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zwyy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, zwyz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zwyz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, zwyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zwyw();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, zwzx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zwzx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, zwzy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zwzy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, zwzz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zwzz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, zwzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zwzw();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, zwwx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zwwx();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, zwwy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zwwy();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, zwwz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zwwz();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, zwww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.zwww();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, wxxx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wxxx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, wxxy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wxxy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, wxxz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wxxz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, wxxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wxxw();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, wxyx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wxyx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, wxyy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wxyy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, wxyz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wxyz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, wxyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wxyw();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, wxzx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wxzx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, wxzy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wxzy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, wxzz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wxzz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, wxzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wxzw();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, wxwx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wxwx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, wxwy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wxwy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, wxwz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wxwz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, wxww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wxww();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, wyxx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wyxx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, wyxy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wyxy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, wyxz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wyxz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, wyxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wyxw();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, wyyx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wyyx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, wyyy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wyyy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, wyyz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wyyz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, wyyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wyyw();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, wyzx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wyzx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, wyzy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wyzy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, wyzz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wyzz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, wyzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wyzw();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, wywx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wywx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, wywy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wywy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, wywz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wywz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, wyww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wyww();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, wzxx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wzxx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, wzxy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wzxy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, wzxz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wzxz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, wzxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wzxw();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, wzyx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wzyx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, wzyy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wzyy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, wzyz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wzyz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, wzyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wzyw();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, wzzx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wzzx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, wzzy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wzzy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, wzzz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wzzz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, wzzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wzzw();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, wzwx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wzwx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, wzwy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wzwy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, wzwz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wzwz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, wzww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wzww();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, wwxx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wwxx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, wwxy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wwxy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, wwxz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wwxz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, wwxw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wwxw();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, wwyx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wwyx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, wwyy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wwyy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, wwyz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wwyz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, wwyw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wwyw();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, wwzx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wwzx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, wwzy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wwzy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, wwzz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wwzz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, wwzw)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wwzw();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, wwwx)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wwwx();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, wwwy)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wwwy();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, wwwz)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wwwz();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, wwww)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.wwww();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, r)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    double r = vec.r()[0];
    cr_assert_eq(r, 1.0);
}

Test(Vector, g)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    double g = vec.g()[0];
    cr_assert_eq(g, 2.0);
}

Test(Vector, b)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    double b = vec.b()[0];
    cr_assert_eq(b, 3.0);
}

Test(Vector, a)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    double a = vec.a()[0];
    cr_assert_eq(a, 4.0);
}

Test(Vector, rr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.rr();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
}

Test(Vector, rg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.rg();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
}

Test(Vector, rb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.rb();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
}

Test(Vector, ra)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.ra();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
}

Test(Vector, gr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.gr();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
}

Test(Vector, gg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.gg();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
}

Test(Vector, gb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.gb();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
}

Test(Vector, ga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.ga();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
}

Test(Vector, br)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.br();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
}

Test(Vector, bg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.bg();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
}

Test(Vector, bb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.bb();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
}

Test(Vector, ba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.ba();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
}

Test(Vector, ar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.ar();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
}

Test(Vector, ag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.ag();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
}

Test(Vector, ab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.ab();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
}

Test(Vector, aa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<2> vec2 = vec.aa();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
}

Test(Vector, rrr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.rrr();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, rrg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.rrg();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, rrb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.rrb();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, rra)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.rra();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, rgr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.rgr();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, rgg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.rgg();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, rgb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.rgb();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, rga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.rga();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, rbr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.rbr();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, rbg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.rbg();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, rbb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.rbb();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, rba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.rba();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, rar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.rar();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, rag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.rag();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, rab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.rab();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, raa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.raa();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, grr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.grr();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, grg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.grg();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, grb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.grb();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, gra)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.gra();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, ggr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.ggr();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, ggg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.ggg();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, ggb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.ggb();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, gga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.gga();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, gbr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.gbr();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, gbg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.gbg();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, gbb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.gbb();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, gba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.gba();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, gar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.gar();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, gag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.gag();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, gab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.gab();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, gaa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.gaa();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, brr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.brr();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, brg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.brg();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, brb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.brb();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, bra)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.bra();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, bgr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.bgr();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, bgg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.bgg();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, bgb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.bgb();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, bga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.bga();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, bbr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.bbr();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, bbg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.bbg();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, bbb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.bbb();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, bba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.bba();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, bar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.bar();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, bag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.bag();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, bab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.bab();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, baa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.baa();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, arr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.arr();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, arg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.arg();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, arb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.arb();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, ara)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.ara();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, agr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.agr();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, agg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.agg();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, agb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.agb();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, aga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.aga();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, abr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.abr();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, abg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.abg();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, abb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.abb();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, aba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.aba();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, aar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.aar();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
}

Test(Vector, aag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.aag();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
}

Test(Vector, aab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.aab();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
}

Test(Vector, aaa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<3> vec2 = vec.aaa();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
}

Test(Vector, rrrr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rrrr();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, rrrg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rrrg();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, rrrb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rrrb();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, rrra)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rrra();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, rrgr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rrgr();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, rrgg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rrgg();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, rrgb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rrgb();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, rrga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rrga();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, rrbr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rrbr();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, rrbg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rrbg();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, rrbb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rrbb();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, rrba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rrba();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, rrar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rrar();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, rrag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rrag();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, rrab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rrab();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, rraa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rraa();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, rgrr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rgrr();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, rgrg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rgrg();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, rgrb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rgrb();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, rgra)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rgra();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, rggr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rggr();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, rggg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rggg();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, rggb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rggb();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, rgga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rgga();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, rgbr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rgbr();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, rgbg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rgbg();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, rgbb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rgbb();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, rgba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rgba();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, rgar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rgar();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, rgag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rgag();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, rgab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rgab();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, rgaa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rgaa();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, rbrr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rbrr();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, rbrg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rbrg();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, rbrb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rbrb();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, rbra)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rbra();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, rbgr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rbgr();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, rbgg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rbgg();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, rbgb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rbgb();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, rbga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rbga();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, rbbr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rbbr();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, rbbg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rbbg();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, rbbb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rbbb();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, rbba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rbba();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, rbar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rbar();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, rbag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rbag();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, rbab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rbab();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, rbaa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rbaa();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, rarr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rarr();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, rarg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rarg();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, rarb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rarb();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, rara)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rara();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, ragr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ragr();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, ragg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ragg();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, ragb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ragb();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, raga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.raga();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, rabr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rabr();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, rabg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rabg();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, rabb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.rabb();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, raba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.raba();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, raar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.raar();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, raag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.raag();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, raab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.raab();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, raaa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.raaa();
    cr_assert_eq(vec2[0], 1.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, grrr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.grrr();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, grrg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.grrg();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, grrb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.grrb();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, grra)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.grra();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, grgr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.grgr();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, grgg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.grgg();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, grgb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.grgb();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, grga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.grga();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, grbr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.grbr();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, grbg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.grbg();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, grbb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.grbb();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, grba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.grba();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, grar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.grar();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, grag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.grag();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, grab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.grab();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, graa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.graa();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, ggrr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ggrr();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, ggrg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ggrg();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, ggrb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ggrb();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, ggra)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ggra();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, gggr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gggr();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, gggg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gggg();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, gggb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gggb();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, ggga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ggga();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, ggbr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ggbr();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, ggbg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ggbg();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, ggbb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ggbb();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, ggba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ggba();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, ggar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ggar();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, ggag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ggag();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, ggab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ggab();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, ggaa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.ggaa();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, gbrr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gbrr();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, gbrg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gbrg();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, gbrb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gbrb();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, gbra)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gbra();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, gbgr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gbgr();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, gbgg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gbgg();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, gbgb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gbgb();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, gbga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gbga();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, gbbr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gbbr();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, gbbg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gbbg();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, gbbb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gbbb();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, gbba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gbba();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, gbar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gbar();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, gbag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gbag();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, gbab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gbab();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, gbaa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gbaa();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, garr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.garr();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, garg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.garg();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, garb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.garb();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, gara)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gara();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, gagr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gagr();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, gagg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gagg();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, gagb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gagb();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, gaga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gaga();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, gabr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gabr();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, gabg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gabg();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, gabb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gabb();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, gaba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gaba();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, gaar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gaar();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, gaag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gaag();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, gaab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gaab();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, gaaa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.gaaa();
    cr_assert_eq(vec2[0], 2.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, brrr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.brrr();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, brrg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.brrg();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, brrb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.brrb();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, brra)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.brra();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, brgr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.brgr();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, brgg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.brgg();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, brgb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.brgb();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, brga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.brga();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, brbr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.brbr();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, brbg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.brbg();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, brbb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.brbb();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, brba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.brba();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, brar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.brar();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, brag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.brag();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, brab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.brab();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, braa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.braa();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, bgrr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bgrr();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, bgrg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bgrg();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, bgrb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bgrb();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, bgra)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bgra();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, bggr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bggr();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, bggg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bggg();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, bggb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bggb();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, bgga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bgga();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, bgbr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bgbr();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, bgbg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bgbg();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, bgbb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bgbb();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, bgba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bgba();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, bgar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bgar();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, bgag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bgag();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, bgab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bgab();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, bgaa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bgaa();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, bbrr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bbrr();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, bbrg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bbrg();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, bbrb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bbrb();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, bbra)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bbra();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, bbgr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bbgr();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, bbgg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bbgg();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, bbgb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bbgb();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, bbga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bbga();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, bbbr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bbbr();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, bbbg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bbbg();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, bbbb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bbbb();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, bbba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bbba();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, bbar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bbar();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, bbag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bbag();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, bbab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bbab();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, bbaa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bbaa();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, barr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.barr();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, barg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.barg();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, barb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.barb();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, bara)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bara();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, bagr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bagr();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, bagg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bagg();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, bagb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.bagb();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, baga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.baga();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, babr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.babr();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, babg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.babg();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, babb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.babb();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, baba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.baba();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, baar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.baar();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, baag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.baag();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, baab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.baab();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, baaa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.baaa();
    cr_assert_eq(vec2[0], 3.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, arrr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.arrr();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, arrg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.arrg();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, arrb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.arrb();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, arra)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.arra();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, argr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.argr();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, argg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.argg();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, argb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.argb();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, arga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.arga();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, arbr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.arbr();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, arbg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.arbg();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, arbb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.arbb();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, arba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.arba();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, arar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.arar();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, arag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.arag();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, arab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.arab();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, araa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.araa();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 1.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, agrr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.agrr();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, agrg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.agrg();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, agrb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.agrb();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, agra)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.agra();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, aggr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aggr();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, aggg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aggg();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, aggb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aggb();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, agga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.agga();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, agbr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.agbr();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, agbg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.agbg();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, agbb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.agbb();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, agba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.agba();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, agar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.agar();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, agag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.agag();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, agab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.agab();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, agaa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.agaa();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 2.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, abrr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.abrr();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, abrg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.abrg();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, abrb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.abrb();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, abra)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.abra();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, abgr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.abgr();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, abgg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.abgg();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, abgb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.abgb();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, abga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.abga();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, abbr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.abbr();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, abbg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.abbg();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, abbb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.abbb();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, abba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.abba();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, abar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.abar();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, abag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.abag();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, abab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.abab();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, abaa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.abaa();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 3.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, aarr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aarr();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, aarg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aarg();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, aarb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aarb();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, aara)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aara();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 1.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, aagr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aagr();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, aagg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aagg();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, aagb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aagb();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, aaga)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aaga();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 2.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, aabr)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aabr();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, aabg)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aabg();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, aabb)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aabb();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, aaba)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aaba();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 3.0);
    cr_assert_eq(vec2[3], 4.0);
}

Test(Vector, aaar)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aaar();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 1.0);
}

Test(Vector, aaag)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aaag();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 2.0);
}

Test(Vector, aaab)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aaab();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 3.0);
}

Test(Vector, aaaa)
{
    GLSL::Vector<4> vec(1.0, 2.0, 3.0, 4.0);
    GLSL::Vector<4> vec2 = vec.aaaa();
    cr_assert_eq(vec2[0], 4.0);
    cr_assert_eq(vec2[1], 4.0);
    cr_assert_eq(vec2[2], 4.0);
    cr_assert_eq(vec2[3], 4.0);
}
