//-----------------------------------------------------------------------------
// Copyright (c) 2015 GarageGames, LLC
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
#include "T3D/physics/nd3/nd3Body.h"

#include "T3D/physics/nd3/nd3.h"
#include "T3D/physics/nd3/nd3World.h"
#include "T3D/physics/nd3/nd3Collision.h"
#include "math/mBox.h"
#include "console/console.h"

Nd3Body::Nd3Body() :
   //mActor( NULL ),
   //mWorld( NULL ),
   //mMass( 0.0f ),
   //mCompound( NULL ),
   mCenterOfMass( NULL ),
   mInvCenterOfMass( NULL ),
   mIsDynamic( false ),
   mIsEnabled( false )
{
}

Nd3Body::~Nd3Body()
{
   _releaseActor();
}

void Nd3Body::_releaseActor()
{

}

bool Nd3Body::init(PhysicsCollision *shape, F32 mass, U32 bodyFlags, SceneObject *obj,  PhysicsWorld *world)
{
   return true;
}

void Nd3Body::setMaterial(F32 restitution, F32 friction,  F32 staticFriction)
{

}

void Nd3Body::setSleepThreshold(F32 linear, F32 angular)
{

}

void Nd3Body::setDamping(F32 linear, F32 angular)
{

}

void Nd3Body::getState(PhysicsState *outState)
{
   AssertFatal( isDynamic(), "Nd3Body::getState - This call is only for dynamics!" );
}

Point3F Nd3Body::getCMassPosition() const
{
   return Point3F(0.0f);
}

void Nd3Body::setLinVelocity(const Point3F &vel)
{

}

void Nd3Body::setAngVelocity(const Point3F &vel)
{

}

Point3F Nd3Body::getLinVelocity() const
{
   return Point3F(0.0f);
}

Point3F Nd3Body::getAngVelocity() const
{
   return Point3F(0.0f);
}

void Nd3Body::setSleeping(bool sleeping)
{

}

PhysicsWorld* Nd3Body::getWorld() 
{
   return NULL;
}

PhysicsCollision* Nd3Body::getColShape() 
{
   return NULL;
}

MatrixF& Nd3Body::getTransform(MatrixF *outMatrix)
{
   return MatrixF(true);
}

void Nd3Body::setTransform(const MatrixF &transform)
{

}

void Nd3Body::applyCorrection(const MatrixF &transform)
{

}

void Nd3Body::applyImpulse(const Point3F &origin, const Point3F &force)
{

}

Box3F Nd3Body::getWorldBounds()
{   
   return Box3F();
}

void Nd3Body::setSimulationEnabled(bool enabled)
{

}
