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
#include "T3D/physics/nd3/nd3Collision.h"

#include "math/mPoint3.h"
#include "math/mMatrix.h"
#include "T3D/physics/nd3/nd3.h"


Nd3Collision::Nd3Collision() 
   : mLocalXfm( true )
{
}

Nd3Collision::~Nd3Collision()
{

}

void Nd3Collision::addPlane(const PlaneF &plane)
{
   // NOTE: Torque uses a negative D... thats why we flip it here.
}

void Nd3Collision::addBox(const Point3F &halfWidth, const MatrixF &localXfm)
{

}

void Nd3Collision::addSphere(const F32 radius, const MatrixF &localXfm)
{

}

void Nd3Collision::addCapsule(F32 radius, F32 height, const MatrixF &localXfm)
{

}

bool Nd3Collision::addConvex(const Point3F *points, U32 count, const MatrixF &localXfm)
{
   return false; // not yet
}

bool Nd3Collision::addTriangleMesh(const Point3F *vert, U32 vertCount, const U32 *index, U32 triCount, const MatrixF &localXfm)
{
   return false; // not yet
}

bool Nd3Collision::addHeightfield(const U16 *heights, const bool *holes, U32 blockSize, F32 metersPerSample, const MatrixF &localXfm)
{
   // We pass the absolute maximum and minimum of a U16 height
   // field and not the actual min and max.  This helps with
   // placement.
   //const F32 heightScale = 0.03125f;
   //const F32 minHeight = 0;
   //const F32 maxHeight = 65535 * heightScale;

   return false; // not implemented yet
}
