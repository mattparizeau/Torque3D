//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "platform/platform.h"
#include "console/console.h"
#include "T3D/physics/bullet/bt.h"
#include "T3D/physics/bullet/btBody.h"
#include "T3D/physics/bullet/btConstraint.h"
#include "T3D/physics/bullet/btCasts.h"

BtConstraint::BtConstraint()
{
   mConstraint = NULL;

   mConstraintType = NO_CONSTRAINT;
   mObjA = NULL;
   mObjB = NULL;

   mPivotInA = Point3F(0.0f);
   mPivotInB = Point3F(0.0f);
   mAxisInA = Point3F(0.0f);
   mAxisInB = Point3F(0.0f);
   mUseReferenceFrameA = false;
}

BtConstraint::~BtConstraint()
{
   // clear references
   mObjA = NULL;
   mObjB = NULL;

   SAFE_DELETE(mConstraint);
}

void BtConstraint::init(ConstraintType type)
{
   mConstraintType = type;

   if (mConstraintType == HINGE_CONSTRAINT)
   {
      // This creates a hinge constraint
      btRigidBody bodyA = *(getRigidBody(mObjA));
      btRigidBody bodyB = *(getRigidBody(mObjB));
      mConstraint = new btHingeConstraint(bodyA, 
                                          bodyB, 
                                          (const btVector3&)btCast<btVector3&>(mPivotInA), 
                                          (const btVector3&)btCast<btVector3&>(mPivotInB), 
                                          btCast<btVector3&>(mAxisInA), 
                                          btCast<btVector3&>(mAxisInB), 
                                          mUseReferenceFrameA);
   }
   else
   {
      Con::errorf("BtConstraint :: no constraint specified");
      mConstraintType = NO_CONSTRAINT;
   }
}

void BtConstraint::setRigidBodies(PhysicsBody *a, PhysicsBody *b)
{
   mObjA = a;
   mObjB = b;
}

void BtConstraint::setPivotPoints(Point3F &pivotA, Point3F &pivotB)
{
   mPivotInA = pivotA;
   mPivotInB = pivotB;
}

void BtConstraint::setAxes(Point3F &axisA, Point3F &axisB)
{
   mAxisInA = axisA;
   mAxisInB = axisB;
}