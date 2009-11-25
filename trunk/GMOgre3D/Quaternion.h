/*
--------------------------------------------------------------------------------
GMOgre3D - Wrapper of the OGRE 3D library for Game Maker

Copyright (C) 2009 Robert Geiman
                   <robgeiman@gmail.com>

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
--------------------------------------------------------------------------------
*/

#ifndef GMOGRE_QUATERNION_H
#define GMOGRE_QUATERNION_H

#include "GMOgre3D.h"


GMFN double SetQuaternionFromAngleAxis(double degrees, double x, double z, double y)
{
   Ogre::Quaternion quat(Ogre::Radian(Ogre::Degree(degrees)), Ogre::Vector3(x, y, z));

   *mQuaternionResultW = quat.w;
   *mQuaternionResultX = quat.x;
   *mQuaternionResultY = quat.z;
   *mQuaternionResultZ = quat.y;

   return TRUE;
}


GMFN double SetQuaternionFromVectors(double x1, double z1, double y1, double x2, double z2, double y2, double x3, double z3, double y3)
{
   Ogre::Quaternion quat(Ogre::Vector3(x1, y1, z1), Ogre::Vector3(x2, y2, z2), Ogre::Vector3(x3, y3, z3));

   *mQuaternionResultW = quat.w;
   *mQuaternionResultX = quat.x;
   *mQuaternionResultY = quat.z;
   *mQuaternionResultZ = quat.y;

   return TRUE;
}


GMFN double SetQuaternionFromVectorRotationTo(double x1, double z1, double y1, double x2, double z2, double y2)
{
   Ogre::Quaternion quat(Ogre::Vector3(x1, y1, z1).getRotationTo(Ogre::Vector3(x2, y2, z2)));

   *mQuaternionResultW = quat.w;
   *mQuaternionResultX = quat.x;
   *mQuaternionResultY = quat.z;
   *mQuaternionResultZ = quat.y;

   return TRUE;
}


GMFN double AddQuaternion(double w1, double x1, double y1, double z1, double w2, double x2, double y2, double z2)
{
   Ogre::Quaternion quat = Ogre::Quaternion(w1, x1, y1, z1) + Ogre::Quaternion(w2, x2, y2, z2);

   *mQuaternionResultW = quat.w;
   *mQuaternionResultX = quat.x;
   *mQuaternionResultY = quat.z;
   *mQuaternionResultZ = quat.y;

   return TRUE;
}


GMFN double SubtractQuaternion(double w1, double x1, double z1, double y1, double w2, double x2, double z2, double y2)
{
   Ogre::Quaternion quat = Ogre::Quaternion(w1, x1, y1, z1) - Ogre::Quaternion(w2, x2, y2, z2);

   *mQuaternionResultW = quat.w;
   *mQuaternionResultX = quat.x;
   *mQuaternionResultY = quat.z;
   *mQuaternionResultZ = quat.y;

   return TRUE;
}


GMFN double NormalizeQuaternion(double w, double x, double z, double y)
{
   Ogre::Quaternion quat(w, x, y, z);
   Ogre::Real len = quat.normalise();

   *mQuaternionResultW = quat.w;
   *mQuaternionResultX = quat.x;
   *mQuaternionResultY = quat.z;
   *mQuaternionResultZ = quat.y;

   return len;
}


GMFN double NormalizeResultQuaternion()
{
   double w = *mQuaternionResultW;
   double x = *mQuaternionResultX;
   double z = *mQuaternionResultY;
   double y = *mQuaternionResultZ;

   Ogre::Quaternion quat(w, x, y, z);
   Ogre::Real len = quat.normalise();

   *mQuaternionResultW = quat.w;
   *mQuaternionResultX = quat.x;
   *mQuaternionResultY = quat.z;
   *mQuaternionResultZ = quat.y;

   return len;
}


GMFN double GetQuaternionRoll(double w, double x, double z, double y)
{
   return Ogre::Quaternion(w, x, y, z).getRoll().valueDegrees();
}


GMFN double GetQuaternionPitch(double w, double x, double z, double y)
{
   return Ogre::Quaternion(w, x, y, z).getPitch().valueDegrees();
}


GMFN double GetQuaternionYaw(double w, double x, double z, double y)
{
   return Ogre::Quaternion(w, x, y, z).getYaw().valueDegrees();
}

#endif
