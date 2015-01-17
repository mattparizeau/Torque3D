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
#include "core/stream/bitStream.h"
#include "console/engineAPI.h"
#include "scene/sceneObject.h"
#include "T3D/physics/physicsPlugin.h"
#include "T3D/physics/physicsShape.h"
#include "T3D/physics/physicsConstraint.h"
#include "T3D/physics/physicsHingeConstraint.h"

PhysicsHingeConstraint::PhysicsHingeConstraint()
{
   mObjA = NULL;
   mObjB = NULL;
   mConstraint = NULL;

   mPivotInA = Point3F(0.0f);
   mPivotInB = Point3F(0.0f);
   mAxisInA = Point3F(0.0f);
   mAxisInB = Point3F(0.0f);
   mUseReferenceFrameA = false;
}

PhysicsHingeConstraint::~PhysicsHingeConstraint()
{
   // delete the constraint if it is not null
   if (mConstraint != NULL)
   {
      delete mConstraint;
      mConstraint = NULL;
   }

   // clear references
   mObjA = NULL;
   mObjB = NULL;
}

void PhysicsHingeConstraint::initPersistFields()
{
   Parent::initPersistFields();
}

void PhysicsHingeConstraint::inspectPostApply()
{
   Parent::inspectPostApply();
}

bool PhysicsHingeConstraint::onAdd()
{
   if (!Parent::onAdd())
      return false;

   return true;
}

void PhysicsHingeConstraint::onRemove()
{
   Parent::onRemove();
}

U32 PhysicsHingeConstraint::packUpdate(NetConnection *conn, U32 mask, BitStream *stream)
{
   U32 ret = Parent::packUpdate(conn, mask, stream);

   if (stream->writeFlag(mask & StateMask))
   {
      // send down the information across the network.
      stream->writeFlag(mUseReferenceFrameA);
      stream->writeCompressedPoint(mPivotInA);
      stream->writeCompressedPoint(mPivotInB);
      stream->writeCompressedPoint(mAxisInA);
      stream->writeCompressedPoint(mAxisInB);

      // TODO: send ghost
   }

   // Create mask, calls init on the client
   stream->writeFlag(mask & CreateMask);

   return ret;
}

void PhysicsHingeConstraint::unpackUpdate(NetConnection *conn, BitStream *stream)
{
   Parent::unpackUpdate(conn, stream);

   // StateMask
   if (stream->readFlag())
   {
      mUseReferenceFrameA = stream->readFlag();
      stream->readCompressedPoint(&mPivotInA);
      stream->readCompressedPoint(&mPivotInB);
      stream->readCompressedPoint(&mAxisInA);
      stream->readCompressedPoint(&mAxisInB);

      // TODO: receive ghost id
   }

   // CreateMask
   if (stream->readFlag())
   {
      init();
   }
}

void PhysicsHingeConstraint::init()
{
   // create physics constraint
   if (PHYSICSMGR)
   {
      if (isServerObject())
         setMaskBits(CreateMask);

      SAFE_DELETE(mConstraint);

      mConstraint = PHYSICSMGR->createConstraint();
      mConstraint->setRigidBodies(mObjA->getPhysicsRep(), mObjB->getPhysicsRep());
      mConstraint->setPivotPoints(mPivotInA, mPivotInB);
      mConstraint->setAxes(mAxisInA, mAxisInB);
      mConstraint->init(PhysicsConstraint::HINGE_CONSTRAINT);
   }
}

void PhysicsHingeConstraint::setObjects(PhysicsShape *a, PhysicsShape *b)
{
   mObjA = a;
   mObjB = b;
   setMaskBits(StateMask);
}

//-----------------------------------------------------------------------------

DefineEngineMethod(PhysicsHingeConstraint, init, void, (), , "()")
{
   if (!object->isServerObject())
   {
      Con::errorf("PhysicsHingeConstraint::init() - can only be called on a server object!");
      return;
   }
   object->init();
}

DefineEngineMethod(PhysicsHingeConstraint, setObjects, void, (PhysicsShape *a, PhysicsShape *b), , "(PhysicsShape a, PhysicsShape b)")
{
   if (!object->isServerObject())
   {
      Con::errorf("PhysicsHingeConstraint::setObjects() - can only be called on a server object!");
      return;
   }

   if (a == NULL)
      Con::errorf("PhysicsHingeConstraint::setObjects() - first object is null!");
   else if (b == NULL)
      Con::errorf("PhysicsHingeConstraint::setObjects() - second object is null!");
   else
      object->setObjects(a, b);
}

// todo: expand upon other methods