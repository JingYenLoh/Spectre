/*
    This file is part of Spectre, an open-source physically based
    spectral raytracing library.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "gtest.h"
#include "math/transform.h"

TEST(TransformTest, CanBeCreated)
{
    ASSERT_NO_THROW(Transform());
}

TEST(TransformTest, DefaultsToIdentity)
{
    EXPECT_TRUE(Transform().GetMatrix().IsIdentity());
    EXPECT_TRUE(Transform().GetMatrixInverse().IsIdentity());
}

TEST(TransformTest, CanSetTranlation)
{
    Transform t;
    ASSERT_NO_THROW(t.SetTranslation({ 1, 2, 3 }));
    EXPECT_EQ(t.GetMatrix(), Matrix4x4(1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 3, 0, 0, 0, 1));
    ASSERT_NO_THROW(t.SetTranslation({ 1, 2, 4 }));
    EXPECT_EQ(t.GetMatrix(), Matrix4x4(1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 4, 0, 0, 0, 1));
}

TEST(TransformTest, CanSetRotation)
{
    Transform t;
    ASSERT_NO_THROW(t.SetRotation({ Math::Pi / 2, 0, 0 }));
    EXPECT_EQ(t.GetMatrix(), Matrix4x4(1, 0, 0, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 1));
}

TEST(TransformTest, CanSetScale)
{
    Transform t;
    ASSERT_NO_THROW(t.SetScale({ 1, 2, 4}));
    EXPECT_EQ(t.GetMatrix(), Matrix4x4(1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1));
}

TEST(TransformTest, MatrixHasCorrectValues)
{
    Transform t, t2;

    ASSERT_NO_THROW(t.SetTranslation({ 1, 2, 3 }));
    EXPECT_EQ(t.GetMatrix(), Matrix4x4(1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 3, 0, 0, 0, 1));
    EXPECT_EQ(t.GetMatrixInverse(), Matrix4x4(1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 3, 0, 0, 0, 1).Inversed());

    ASSERT_NO_THROW(t.SetScale({ 1, 1, 4 }));
    EXPECT_EQ(t.GetMatrix(), Matrix4x4(1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 4, 3, 0, 0, 0, 1));
    EXPECT_EQ(t.GetMatrixInverse(), Matrix4x4(1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 4, 3, 0, 0, 0, 1).Inversed());

    ASSERT_NO_THROW(t2.SetRotation({ Math::Pi / 2, 0, 0 }));
    EXPECT_EQ(t2.GetMatrix(), Matrix4x4(1, 0, 0, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 1));
    EXPECT_EQ(t2.GetMatrixInverse(), Matrix4x4(1, 0, 0, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 1).Inversed());

    ASSERT_NO_THROW(t2.SetRotation({ Math::Pi / 2, Math::Pi / 2, Math::Pi / 2 }));
    EXPECT_EQ(t2.GetMatrix(), Matrix4x4(0, 0, 1, 0, 0, 1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 1));
    EXPECT_EQ(t2.GetMatrixInverse(), Matrix4x4(0, 0, 1, 0, 0, 1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 1).Inversed());

    ASSERT_NO_THROW(t.SetRotation({ Math::Pi / 2, Math::Pi / 2, Math::Pi / 2 }));
    EXPECT_EQ(t.GetMatrix(), Matrix4x4(0, 0, 4, 1, 0, 1, 0, 2, -1, 0, 0, 3, 0, 0, 0, 1));
    EXPECT_EQ(t.GetMatrixInverse(), Matrix4x4(0, 0, 4, 1, 0, 1, 0, 2, -1, 0, 0, 3, 0, 0, 0, 1).Inversed());
}

TEST(TransformTest, CanTransformVectorsIdentity)
{
    Transform t;
    Vector3 forward = { 0, 0, 1 };
    Vector3 up = { 0, 1, 0 };
    Vector3 right = { 1, 0, 0 };

    // Indentity transform should not change vector
    EXPECT_EQ(t(forward), forward);
    EXPECT_EQ(t(up), up);
    EXPECT_EQ(t(right), right);
}

TEST(TransformTest, CanTransformVectorsTranslated)
{
    Transform t;
    t.SetTranslation({ 1.0, -1.0, 2.5 });

    Vector3 forward = { 0, 0, 1 };
    Vector3 up = { 0, 1, 0 };
    Vector3 right = { 1, 0, 0 };

    // Translation should not change vector
    EXPECT_EQ(t(forward), forward);
    EXPECT_EQ(t(up), up);
    EXPECT_EQ(t(right), right);
}

TEST(TransformTest, CanTransformVectorsScaled)
{
    Transform t;
    t.SetScale({ 2.0, 2.0, -2.0 });

    Vector3 forward = { 0, 0, 1 };
    Vector3 up = { 0, 1, 0 };
    Vector3 right = { 1, 0, 0 };

    // Scale should change vector
    EXPECT_EQ(t(forward), Vector3(0, 0, -2));
    EXPECT_EQ(t(up), Vector3(0, 2, 0));
    EXPECT_EQ(t(right), Vector3(2, 0, 0));
}

TEST(TransformTest, CanTransformVectorsRotated)
{
    Transform t;
    t.SetRotation({ 0, Math::DegToRad(90), 0 });

    Vector3 forward = { 0, 0, 1 };
    Vector3 up = { 0, 1, 0 };
    Vector3 right = { 1, 0, 0 };

    // Rotation should change vector
    EXPECT_EQ(t(forward), right);
    EXPECT_EQ(t(up), up);
    EXPECT_EQ(t(right), -forward);

    t.SetRotation({ Math::DegToRad(90), 0, 0});
    EXPECT_EQ(t(forward), -up);
    EXPECT_EQ(t(up), forward);
    EXPECT_EQ(t(right), right);
}

TEST(TransformTest, CanTransformPointsIdentity)
{
    Transform t;
    Point3 forward = { 0, 0, 1 };
    Point3 up = { 0, 1, 0 };
    Point3 right = { 1, 0, 0 };

    // Indentity transform should not change point
    EXPECT_EQ(t(forward), forward);
    EXPECT_EQ(t(up), up);
    EXPECT_EQ(t(right), right);
}

TEST(TransformTest, CanTransformPointsTranslated)
{
    Transform t;
    Vector3 translation(1.0, 2.5, -1.0);
    t.SetTranslation(translation);

    Point3 forward = { 0, 0, 1 };
    Point3 up = { 0, 1, 0 };
    Point3 right = { 1, 0, 0 };

    // Translation should change point
    EXPECT_EQ(t(forward), forward + translation);
    EXPECT_EQ(t(up), up + translation);
    EXPECT_EQ(t(right), right + translation);
}

TEST(TransformTest, CanTransformPointsScaled)
{
    Transform t;
    t.SetScale({ 2.0, 2.0, -2.0 });

    Point3 forward = { 0, 0, 1 };
    Point3 up = { 0, 1, 0 };
    Point3 right = { 1, 0, 0 };

    // Scale should change point
    EXPECT_EQ(t(forward), Point3(0, 0, -2));
    EXPECT_EQ(t(up), Point3(0, 2, 0));
    EXPECT_EQ(t(right), Point3(2, 0, 0));
}

TEST(TransformTest, CanTransformPointsRotated)
{
    Transform t;
    t.SetRotation({ 0, Math::DegToRad(90), 0 });

    Point3 forward = { 0, 0, 1 };
    Point3 up = { 0, 1, 0 };
    Point3 right = { 1, 0, 0 };

    // Rotation should change point
    EXPECT_EQ(t(forward), right);
    EXPECT_EQ(t(up), up);
    EXPECT_EQ(t(right), -forward);

    t.SetRotation({ Math::DegToRad(90), 0, 0 });
    EXPECT_EQ(t(forward), -up);
    EXPECT_EQ(t(up), forward);
    EXPECT_EQ(t(right), right);
}

TEST(TransformTest, CanTransformNormalsIdentity)
{
    Transform t;
    Normal3 forward = { 0, 0, 1 };
    Normal3 up = { 0, 1, 0 };
    Normal3 right = { 1, 0, 0 };

    // Indentity transform should not change normal
    EXPECT_EQ(t(forward), forward);
    EXPECT_EQ(t(up), up);
    EXPECT_EQ(t(right), right);
}

TEST(TransformTest, CanTransformNormalsTranslated)
{
    Transform t;
    Vector3 translation(1.0, 2.5, -1.0);
    t.SetTranslation(translation);

    Normal3 forward = { 0, 0, 1 };
    Normal3 up = { 0, 1, 0 };
    Normal3 right = { 1, 0, 0 };

    // Translation should not change normal
    EXPECT_EQ(t(forward), forward);
    EXPECT_EQ(t(up), up);
    EXPECT_EQ(t(right), right);
}

TEST(TransformTest, CanTransformNormalsScaled)
{
    Transform t;
    t.SetScale({ 0.5, 0.5, 0.5 });

    Normal3 forward = { 0, 0, 1 };
    Normal3 up = { 0, 1, 0 };
    Normal3 right = { 1, 0, 0 };

    // Scale should change normal
    EXPECT_EQ(t(forward).Normalized(), Normal3(0, 0, 1.0));
    EXPECT_EQ(t(up).Normalized(), Normal3(0, 1.0, 0));
    EXPECT_EQ(t(right).Normalized(), Normal3(1.0, 0, 0));

    // Scaling non-axis aligned normal must be done with inv transposed mat
    t.SetScale({ 1.0, 0.5, 1.0 });
    Normal3 rightDiag = Normal3(1.0, 1.0, 0.0).Normalized();
    Vector3 rightDiagVec = Vector3(1.0, 1.0, 0.0).Normalized();

    EXPECT_FALSE(t(rightDiag) == t(rightDiagVec));
    EXPECT_EQ(t(rightDiag).Normalized(), Normal3(2, 4, 0).Normalized());
}

TEST(TransformTest, CanTransformNormalsRotated)
{
    Transform t;
    t.SetRotation({ 0, Math::DegToRad(90), 0 });

    Normal3 forward = { 0, 0, 1 };
    Normal3 up = { 0, 1, 0 };
    Normal3 right = { 1, 0, 0 };

    // Rotation should change normal
    EXPECT_EQ(t(forward), right);
    EXPECT_EQ(t(up), up);
    EXPECT_EQ(t(right), -forward);

    t.SetRotation({ Math::DegToRad(90), 0, 0 });
    EXPECT_EQ(t(forward), -up);
    EXPECT_EQ(t(up), forward);
    EXPECT_EQ(t(right), right);
}

TEST(TransformTest, CanTransformRaysIdentity)
{
    Transform t;
    Ray r1({ 0,0,1 }, { 0,0,1 });
    Ray r2({ 0,1,0 }, { 0,1,0 });
    Ray r3({ 1,0,0 }, { 1,0,0 });

    EXPECT_EQ(t(r1), r1);
    EXPECT_EQ(t(r2), r2);
    EXPECT_EQ(t(r3), r3);
}

TEST(TransformTest, CanTransformRaysTranslated)
{
    Transform t;
    t.SetTranslation({ 1.0, -1.0, 2.5 });

    Ray r1({ 0,0,1 }, { 0,0,1 });
    Ray r2({ 0,1,0 }, { 0,1,0 });
    Ray r3({ 1,0,0 }, { 1,0,0 });

    EXPECT_EQ(t(r1).GetDirection(), r1.GetDirection());
    EXPECT_EQ(t(r2).GetDirection(), r2.GetDirection());
    EXPECT_EQ(t(r3).GetDirection(), r3.GetDirection());
    EXPECT_EQ(t(r1).GetOrigin(), r1.GetOrigin() + Vector3(1.0, -1.0, 2.5));
    EXPECT_EQ(t(r2).GetOrigin(), r2.GetOrigin() + Vector3(1.0, -1.0, 2.5));
    EXPECT_EQ(t(r3).GetOrigin(), r3.GetOrigin() + Vector3(1.0, -1.0, 2.5));
}

TEST(TransformTest, CanTransformRaysScaled)
{
    Transform t;
    t.SetScale({ 2.0, 2.0, -2.0 });

    Ray r1({ 0,0,1 }, { 0,0,1 });
    Ray r2({ 0,1,0 }, { 0,1,0 });
    Ray r3({ 1,0,0 }, { 1,0,0 });

    EXPECT_EQ(t(r1).GetDirection(), Vector3(0, 0, -2).Normalized());
    EXPECT_EQ(t(r2).GetDirection(), Vector3(0, 2, 0).Normalized());
    EXPECT_EQ(t(r3).GetDirection(), Vector3(2, 0, 0).Normalized());

    EXPECT_EQ(t(r1).GetOrigin(), Point3(0, 0, -2));
    EXPECT_EQ(t(r2).GetOrigin(), Point3(0, 2, 0));
    EXPECT_EQ(t(r3).GetOrigin(), Point3(2, 0, 0));
}

TEST(TransformTest, CanTransformRaysRotated)
{
    Transform t;
    t.SetRotation({ 0, Math::DegToRad(90), 0 });

    Ray forward({ 0,0,1 }, { 0,0,1 });
    Ray up({ 0,1,0 }, { 0,1,0 });
    Ray right({ 1,0,0 }, { 1,0,0 });

    EXPECT_EQ(t(forward).GetDirection(), right.GetDirection());
    EXPECT_EQ(t(up).GetDirection(), up.GetDirection());
    EXPECT_EQ(t(right).GetDirection(), -forward.GetDirection());

    EXPECT_EQ(t(forward).GetOrigin(), right.GetOrigin());
    EXPECT_EQ(t(up).GetOrigin(), up.GetOrigin());
    EXPECT_EQ(t(right).GetOrigin(), -forward.GetOrigin());
}

TEST(TransformTest, CanGetInverse)
{
    Transform t, t2;

    t.SetTranslation({ 1, 2, 3 });
    t.SetScale({ 1, 1, 4 });
    t.SetRotation({ Math::Pi / 2, Math::Pi / 2, Math::Pi / 2 });
    t2.SetRotation({ Math::Pi / 2, 0, 0 });
    t2.SetRotation({ Math::Pi / 2, Math::Pi / 2, Math::Pi / 2 });

    Transform tInv = t.Inversed();
    Transform tInv2 = t2.Inversed();

    EXPECT_EQ(tInv.GetMatrix(), t.GetMatrixInverse());
    EXPECT_EQ(tInv.GetMatrixInverse(), t.GetMatrix());

    EXPECT_EQ(tInv2.GetMatrix(), t2.GetMatrixInverse());
    EXPECT_EQ(tInv2.GetMatrixInverse(), t2.GetMatrix());
}

TEST(TransformTest, CorrectOrderOfTransformations)
{
    // Should scale at origin, rotate at origin, then translate to position
    Transform t;

    Point3 front = { 0, 0, 1 };
    Point3 up = { 0, 1, 0 };
    Point3 right = { 1, 0, 0 };

    t.SetScale(2.0);
    EXPECT_EQ(t(front), Point3(0, 0, 2));
    EXPECT_EQ(t(up), Point3(0, 2, 0));
    EXPECT_EQ(t(right), Point3(2, 0, 0));

    t.SetRotation(Vector3(Math::DegToRad(90), 0, 0));
    EXPECT_EQ(t(front), Point3(0, -2, 0));
    EXPECT_EQ(t(up), Point3(0, 0, 2));
    EXPECT_EQ(t(right), Point3(2, 0, 0));

    t.SetTranslation(Vector3(20, 30, 40));
    EXPECT_EQ(t(front), Point3(20, 28, 40));
    EXPECT_EQ(t(up), Point3(20, 30, 42));
    EXPECT_EQ(t(right), Point3(22, 30, 40));

    Transform t2;
    Point3 origin = { 0, 0, 0 };
    t2.SetTranslation({ 10, 100, 20 });
    t2.SetRotation({ Math::DegToRad(90), 0, 0 });
    EXPECT_EQ(t2(origin), Point3(10, 100, 20));
    Vector3 forward = { 0, 0, 1 };
    EXPECT_EQ(t2(forward), Vector3(0, -1, 0));
    Ray forwardRay({ 0, 0, 0 }, { 0,0,1 });
    EXPECT_EQ(t2(forwardRay), Ray({10, 100, 20}, {0, -1, 0}));

    Transform t3;
    t3.SetTranslation({ 0, 0.5, -10 });
    t3.SetScale({ 0.005 });
    t3.SetRotation({ Math::DegToRad(2), 0, 0 });
    EXPECT_EQ(t3(forwardRay).GetOrigin(), Point3(0, 0.5, -10));
}

