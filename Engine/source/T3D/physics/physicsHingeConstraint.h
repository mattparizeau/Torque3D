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

#ifndef _PHYSICS_HINGE_CONSTRAINT_H_
#define _PHYSICS_HINGE_CONSTRAINT_H_

#include "scene/sceneObject.h"

class PhysicsConstraint;
class PhysicsShape;

class PhysicsHingeConstraint : public SceneObject
{
   typedef SceneObject Parent;
protected:
   /// The physics constraint
   PhysicsConstraint *mConstraint;

   /// ObjectA to attach
   PhysicsShape *mObjA;

   /// ObjectB to attach
   PhysicsShape *mObjB;

   /// A's pivot point
   Point3F mPivotInA;

   /// B's pivot point
   Point3F mPivotInB;

   /// A's axis
   Point3F mAxisInA;

   /// B's axis
   Point3F mAxisInB;

   /// Use the reference frame of A
   bool mUseReferenceFrameA;

   /// Mask bits
   enum MaskBits
   {
      StateMask = Parent::NextFreeMask << 0,
      CreateMask = Parent::NextFreeMask << 1,
      NextFreeMask = Parent::NextFreeMask << 1
   };

public:
   PhysicsHingeConstraint();
   ~PhysicsHingeConstraint();
   DECLARE_CONOBJECT(PhysicsHingeConstraint);

   // SimObject methods
   static void initPersistFields();
   void inspectPostApply();
   bool onAdd();
   void onRemove();   

   // NetObject methods
   U32 packUpdate( NetConnection *conn, U32 mask, BitStream *stream );
   void unpackUpdate( NetConnection *conn, BitStream *stream );

   /// Initializes the constraint, called from script
   /// %hinge.init();
   void init();

   /// Sets the objects that the constraint will attach to, called from script
   /// %hinge.setObjects(%objA, %objB);
   void setObjects(PhysicsShape *objA, PhysicsShape *objB);

   /// Sets the axes points of the rigidbodies
   void setAxes(Point3F &axisA, Point3F &axisB);
};

#endif // _PHYSICS_HINGE_CONSTRAINT_H_