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

#ifndef _T3D_PHYSICS_PHYSICSCONSTRAINT_H_
#define _T3D_PHYSICS_PHYSICSCONSTRAINT_H_

#ifndef _REFBASE_H_
#include "core/util/refBase.h"
#endif

class SceneObject;

class PhysicsConstraint : public WeakRefBase
{
public:
   enum ConstraintType
   {
      /// Creates a hinge constraint
      HINGE_CONSTRAINT,

      /// No constraint
      NO_CONSTRAINT
   };

protected:
   /// The constraint type
   ConstraintType mConstraintType;

   /// The first object to be attached
   PhysicsBody *mObjA;

   /// The second object to be attached
   PhysicsBody *mObjB;

   /// A's pivot point
   /// Used for hinge
   Point3F mPivotInA;

   /// B's pivot point
   /// Used for hinge
   Point3F mPivotInB;

   /// A's axis
   /// Used for hinge
   Point3F mAxisInA;

   /// B's axis
   /// Used for hinge
   Point3F mAxisInB;

   /// Use the reference frame of A
   /// Used for hinge
   bool mUseReferenceFrameA;

public:
   virtual ~PhysicsConstraint() {}

   /// Initializes the constraint
   virtual void init(ConstraintType type) = 0;

   /// Sets the rigidbodies
   virtual void setRigidBodies(PhysicsBody *a, PhysicsBody *b) = 0;

   /// Set's the pivot points of the rigidbodies
   virtual void setPivotPoints(Point3F &axisA, Point3F &axisB) = 0;

   /// Sets the axes points of the rigidbodies
   virtual void setAxes(Point3F &axisA, Point3F &axisB) = 0;
};

#endif // _T3D_PHYSICS_PHYSICSCONSTRAINT_H_