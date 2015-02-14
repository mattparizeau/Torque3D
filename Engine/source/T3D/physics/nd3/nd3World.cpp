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
#include "T3D/physics/nd3/nd3.h"
#include "T3D/physics/nd3/nd3World.h"
#include "T3D/physics/nd3/nd3Plugin.h"

#include "T3D/physics/physicsUserData.h"
#include "core/stream/bitStream.h"
#include "platform/profiler.h"
#include "sim/netConnection.h"
#include "console/console.h"
#include "console/consoleTypes.h"
#include "scene/sceneRenderState.h"
#include "T3D/gameBase/gameProcess.h"


Nd3World::Nd3World() :
   mProcessList( NULL ),
   mIsSimulating( false ),
   mErrorReport( false ),
   mTickCount( 0 ),
   mIsEnabled( false )
{
   mWorld = NULL;
} 

Nd3World::~Nd3World()
{
   mWorld = NULL;
}

bool Nd3World::initWorld( bool isServer, ProcessList *processList )
{
   mIsServer = isServer;

   // create the world!
   mWorld = NewtonCreate();

   // my implementation don't really support threading, but this is here just in case
   // please note that every callback will not be implemented as threadsafe.
#ifndef DG_USE_THREAD_EMULATION
   NewtonSetThreadsCount(mWorld, 2);
#endif
   
   // docs says to reset the cache upon creating or resetting the world.
   NewtonInvalidateCache(mWorld);

   // set default solver
   NewtonSetSolverModel(mWorld, 1);

   AssertFatal(processList, "Nd3World::init() - We need a process list to create the world!");
   mProcessList = processList;
   mProcessList->preTickSignal().notify(this, &Nd3World::getPhysicsResults);
   mProcessList->postTickSignal().notify(this, &Nd3World::tickPhysics, 1000.0f);
   
#ifdef TORQUE_DEBUG
   Con::printf("Nd3World::init() - successfully Initialized newton wrold.");
#endif

   return true;
}

void Nd3World::_destroy()
{
   // clean up the newton api
   NewtonDestroyAllBodies(mWorld);
   NewtonDestroy(mWorld);
   mWorld = NULL;

   // Release the tick processing signals.
   if ( mProcessList )
   {
      mProcessList->preTickSignal().remove( this, &Nd3World::getPhysicsResults );
      mProcessList->postTickSignal().remove( this, &Nd3World::tickPhysics );
      mProcessList = NULL;
   }
}

void Nd3World::tickPhysics( U32 elapsedMs )
{
   if (!mIsEnabled )
      return;

   // Did we forget to call getPhysicsResults somewhere?
   AssertFatal( !mIsSimulating, "Nd3World::tickPhysics() - Already simulating!" );

   // The elapsed time should be non-zero and 
   // a multiple of TickMs!
   AssertFatal(   elapsedMs != 0 &&
                  ( elapsedMs % TickMs ) == 0 , "Nd3World::tickPhysics() - Got bad elapsed time!" );

   PROFILE_SCOPE(Nd3World_TickPhysics);

   // Convert it to seconds.
   const F32 elapsedSec = (F32)elapsedMs * 0.001f;

   // Simulate..
   NewtonUpdate(mWorld, elapsedSec);
   
   mIsSimulating = true;

   Con::printf( "%s Nd3World::tickPhysics!", !mIsServer ? "Client" : "Server" );
}

void Nd3World::getPhysicsResults()
{
   if (!mIsSimulating ) 
      return;

   PROFILE_SCOPE(Nd3World_GetPhysicsResults);

   mIsSimulating = false;
   mTickCount++;
}

void Nd3World::setEnabled( bool enabled )
{
   mIsEnabled = enabled;

   if ( !mIsEnabled )
      getPhysicsResults();
}

void Nd3World::destroyWorld()
{
   _destroy();
}

bool Nd3World::castRay( const Point3F &startPnt, const Point3F &endPnt, RayInfo *ri, const Point3F &impulse )
{
   AssertFatal(false, "N3dWorld::castRay() - please don't use this. Just use torque's container system.");
   return false;
}

PhysicsBody* Nd3World::castRay( const Point3F &start, const Point3F &end, U32 bodyTypes )
{
   AssertFatal(false, "N3dWorld::castRay() - please don't use this. Just use torque's container system.");
   return NULL;
}

void Nd3World::explosion( const Point3F &pos, F32 radius, F32 forceMagnitude )
{
   AssertFatal(false, "N3dWorld::explosion() - Explosion in a newton world is not supported.");
}

void Nd3World::onDebugDraw( const SceneRenderState *state )
{
   AssertFatal(false, "N3dWorld::onDebugDraw() - This will be a pain to set up, but newton does support debug drawing.");
}

void Nd3World::reset()
{

}