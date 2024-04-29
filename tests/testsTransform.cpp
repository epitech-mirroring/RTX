/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <criterion/criterion.h>
#include "Transform.hpp"

Test(Transform, Constructor)
{
    Transform transform;
    cr_assert_eq(transform.getPosition().x(), 0.0);
    cr_assert_eq(transform.getPosition().y(), 0.0);
    cr_assert_eq(transform.getPosition().z(), 0.0);
    cr_assert_eq(transform.getRotation().x, 0.0);
    cr_assert_eq(transform.getRotation().y, 0.0);
    cr_assert_eq(transform.getRotation().z, 0.0);
    cr_assert_eq(transform.getRotation().w, 1.0);
    cr_assert_eq(transform.getScale().x(), 1.0);
    cr_assert_eq(transform.getScale().y(), 1.0);
    cr_assert_eq(transform.getScale().z(), 1.0);
}

Test(Transform, Constructor_With_Args)
{
    Transform transform(GLSL::Vector<3>(1.0, 2.0, 3.0), GLSL::Quaternion(4.0, 5.0, 6.0, 7.0), GLSL::Vector<3>(8.0, 9.0, 10.0));
    cr_assert_eq(transform.getPosition().x(), 1.0);
    cr_assert_eq(transform.getPosition().y(), 2.0);
    cr_assert_eq(transform.getPosition().z(), 3.0);
    cr_assert_eq(transform.getRotation().x, 4.0);
    cr_assert_eq(transform.getRotation().y, 5.0);
    cr_assert_eq(transform.getRotation().z, 6.0);
    cr_assert_eq(transform.getRotation().w, 7.0);
    cr_assert_eq(transform.getScale().x(), 8.0);
    cr_assert_eq(transform.getScale().y(), 9.0);
    cr_assert_eq(transform.getScale().z(), 10.0);
}

Test(Transform, Copy_Constructor)
{
    Transform transform(GLSL::Vector<3>(1.0, 2.0, 3.0), GLSL::Quaternion(4.0, 5.0, 6.0, 7.0), GLSL::Vector<3>(8.0, 9.0, 10.0));
    Transform transform2(transform);
    cr_assert_eq(transform2.getPosition().x(), 1.0);
    cr_assert_eq(transform2.getPosition().y(), 2.0);
    cr_assert_eq(transform2.getPosition().z(), 3.0);
    cr_assert_eq(transform2.getRotation().x, 4.0);
    cr_assert_eq(transform2.getRotation().y, 5.0);
    cr_assert_eq(transform2.getRotation().z, 6.0);
    cr_assert_eq(transform2.getRotation().w, 7.0);
    cr_assert_eq(transform2.getScale().x(), 8.0);
    cr_assert_eq(transform2.getScale().y(), 9.0);
    cr_assert_eq(transform2.getScale().z(), 10.0);
    transform2.setPosition(GLSL::Vector<3>(11.0, 12.0, 13.0));
    cr_assert_eq(transform.getPosition().x(), 1.0);
    cr_assert_eq(transform.getPosition().y(), 2.0);
    cr_assert_eq(transform.getPosition().z(), 3.0);
    cr_assert_eq(transform.getRotation().x, 4.0);
    cr_assert_eq(transform.getRotation().y, 5.0);
    cr_assert_eq(transform.getRotation().z, 6.0);
    cr_assert_eq(transform.getRotation().w, 7.0);
    cr_assert_eq(transform.getScale().x(), 8.0);
    cr_assert_eq(transform.getScale().y(), 9.0);
    cr_assert_eq(transform.getScale().z(), 10.0);
}

Test(Transform, Setters)
{
    Transform transform;
    transform.setPosition(GLSL::Vector<3>(1.0, 2.0, 3.0));
    transform.setRotation(GLSL::Quaternion(4.0, 5.0, 6.0, 7.0));
    transform.setScale(GLSL::Vector<3>(8.0, 9.0, 10.0));
    cr_assert_eq(transform.getPosition().x(), 1.0);
    cr_assert_eq(transform.getPosition().y(), 2.0);
    cr_assert_eq(transform.getPosition().z(), 3.0);
    cr_assert_eq(transform.getRotation().x, 4.0);
    cr_assert_eq(transform.getRotation().y, 5.0);
    cr_assert_eq(transform.getRotation().z, 6.0);
    cr_assert_eq(transform.getRotation().w, 7.0);
    cr_assert_eq(transform.getScale().x(), 8.0);
    cr_assert_eq(transform.getScale().y(), 9.0);
    cr_assert_eq(transform.getScale().z(), 10.0);
}

Test(Transform, Translate)
{
    Transform transform;
    transform.translate(GLSL::Vector<3>(1.0, 2.0, 3.0));
    cr_assert_eq(transform.getPosition().x(), 1.0);
    cr_assert_eq(transform.getPosition().y(), 2.0);
    cr_assert_eq(transform.getPosition().z(), 3.0);
    transform.translate(4.0, 5.0, 6.0);
    cr_assert_eq(transform.getPosition().x(), 5.0);
    cr_assert_eq(transform.getPosition().y(), 7.0);
    cr_assert_eq(transform.getPosition().z(), 9.0);
}

Test(Transform, Rotate)
{
    Transform transform;
    transform.rotate(GLSL::Quaternion(1.0, 2.0, 3.0, 1.0));
    cr_assert_eq(transform.getRotation().x, 1.0);
    cr_assert_eq(transform.getRotation().y, 2.0);
    cr_assert_eq(transform.getRotation().z, 3.0);
    transform.rotate(4.0, 5.0, 6.0);
    cr_assert_eq(transform.getRotation().x, 2.0);
    cr_assert_eq(transform.getRotation().y, 13.0);
    cr_assert_eq(transform.getRotation().z, 6.0);
    cr_assert_eq(transform.getRotation().w, -31.0);
}

Test(Transform, Scale)
{
    Transform transform;
    transform.scale(GLSL::Vector<3>(1.0, 2.0, 3.0));
    cr_assert_eq(transform.getScale().x(), 1.0);
    cr_assert_eq(transform.getScale().y(), 2.0);
    cr_assert_eq(transform.getScale().z(), 3.0);
    transform.scale(4.0, 5.0, 6.0);
    cr_assert_eq(transform.getScale().x(), 4.0);
    cr_assert_eq(transform.getScale().y(), 10.0);
    cr_assert_eq(transform.getScale().z(), 18.0);
}

Test(Transform, Get_Transformation_Matrix)
{
    Transform transform;
    transform.setPosition(GLSL::Vector<3>(1.0, 2.0, 3.0));
    transform.setRotation(GLSL::Quaternion(0, 0, 0, 1));
    transform.setScale(GLSL::Vector<3>(8.0, 9.0, 10.0));
    GLSL::Matrix<4, 4> matrix = transform.getTransformationMatrix();

    GLSL::Matrix<4, 4> expectedMatrix = GLSL::Matrix<4, 4>(8.0, 0.0, 0.0, 1.0,
                                                            0.0, 9.0, 0.0, 2.0,
                                                            0.0, 0.0, 10.0, 3.0,
                                                            0.0, 0.0, 0.0, 1.0);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cr_assert_eq(matrix[i][j], expectedMatrix[i][j], "Expected: %f, Got: %f in m%d%d", expectedMatrix[i][j], matrix[i][j], i+1, j+1);
        }
    }

    GLSL::Vector<4> point(1.0, 2.0, 3.0, 1.0);
    GLSL::Vector<4> transformedPoint = matrix * point;
    GLSL::Vector<4> expectedPoint(9.0, 20.0, 33.0, 1.0);
    cr_assert_eq(transformedPoint.x(), expectedPoint.x(), "X Expected: %f, Got: %f", expectedPoint.x(), transformedPoint.x());
    cr_assert_eq(transformedPoint.y(), expectedPoint.y(), "Y Expected: %f, Got: %f", expectedPoint.y(), transformedPoint.y());
    cr_assert_eq(transformedPoint.z(), expectedPoint.z(), "Z Expected: %f, Got: %f", expectedPoint.z(), transformedPoint.z());
    cr_assert_eq(transformedPoint.w(), expectedPoint.w(), "W Expected: %f, Got: %f", expectedPoint.w(), transformedPoint.w());
}