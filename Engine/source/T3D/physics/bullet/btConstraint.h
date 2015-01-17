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

#ifndef _T3D_PHYSICS_BTCONSTRAINT_H_
#define _T3D_PHYSICS_BTCONSTRAINT_H_

#include "T3D/physics/physicsConstraint.h"

class BtConstraint : public PhysicsConstraint
{
protected:

   /// The constraint
   btTypedConstraint *mConstraint;
   
   /// Gets the rigidbody of a shape
   inline btRigidBody *getRigidBody(PhysicsBody *body)
   {
      return static_cast<BtBody*>(body)->getRigidBody();
   }

public:
   BtConstraint();
   virtual ~BtConstraint();

   /// Initializes the constraint and creates it.
   virtual void init(ConstraintType type);

   /// Sets the rigidbodies
   virtual void setRigidBodies(PhysicsBody *a, PhysicsBody *b);

   /// Sets the pivot points of the rigidbodies
   virtual void setPivotPoints(Point3F &pivotA, Point3F &pivotB);

   /// Sets the axes points of the rigidbodies
   virtual void setAxes(Point3F &axisA, Point3F &axisB);
};

#endif // _T3D_PHYSICS_BTCONSTRAINT_H_