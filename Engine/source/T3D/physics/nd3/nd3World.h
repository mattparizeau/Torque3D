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

#ifndef _T3D_PHYSICS_ND3_ND3WORLD_H_
#define _T3D_PHYSICS_ND3_ND3WORLD_H_

#ifndef _T3D_PHYSICS_PHYSICSWORLD_H_
#include "T3D/physics/physicsWorld.h"
#endif
#ifndef _T3D_PHYSICS_ND3_ND3_H_
#include "T3D/physics/nd3/nd3.h"
#endif
#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

class ProcessList;
class PhysicsBody;

class Nd3World : public PhysicsWorld
{
protected:

   NewtonWorld *mWorld;

   bool mErrorReport;

   bool	mIsEnabled;

   bool mIsSimulating;

   bool mIsServer;

   U32 mTickCount;

   ProcessList *mProcessList;

   void _destroy();

   /// { @group Callbacks
   /// These functions are called from the newton SDK.

   /// }

public:

   Nd3World();
   virtual ~Nd3World();

   // PhysicWorld
   virtual bool initWorld( bool isServer, ProcessList *processList );
   virtual void destroyWorld();
   virtual void reset();
   virtual bool isEnabled() const { return mIsEnabled; }

   void tickPhysics( U32 elapsedMs );
   void getPhysicsResults();
   bool isWritable() const { return !mIsSimulating; }

   void setEnabled( bool enabled );
   bool getEnabled() const { return mIsEnabled; }

   /// { @group Unsupported
   /// I choose to not support these functions.
   /// Newton probably supports it, but I do not have a use for them.
   virtual bool castRay(const Point3F &startPnt, const Point3F &endPnt, RayInfo *ri, const Point3F &impulse);
   virtual PhysicsBody* castRay(const Point3F &start, const Point3F &end, U32 bodyTypes);
   virtual void explosion(const Point3F &pos, F32 radius, F32 forceMagnitude);
   virtual void onDebugDraw(const SceneRenderState *state);
   /// }
};

#endif // _T3D_PHYSICS_ND3_ND3WORLD_H_