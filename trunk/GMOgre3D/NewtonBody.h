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

#ifndef GMOGRE_NEWTON_BODY_H
#define GMOGRE_NEWTON_BODY_H

#include "GMOgre3D.h"
#include "NewtonWorld.h"
#include "OgreNewt_Body.h"
#include "OgreNewt_World.h"


GMFN double CreateNewtonBody(double newton_world_ptr, double newton_collision_ptr, double type = 0)
{
   OgreNewt::World *world = ConvertFromGMPointer<OgreNewt::World*>(newton_world_ptr);

   if (!world)
      return 0;

   OgreNewt::Collision *collision = ConvertFromGMPointer<OgreNewt::Collision*>(newton_collision_ptr);

   if (!collision)
      return 0;

   OgreNewt::Body *body = NULL;

   TRY
      OgreNewt::CollisionPtr col = mNewtonCollisionMap[collision];

      body = new OgreNewt::Body(world, col, type);
      //body->setStandardForceCallback();
      body->setCustomForceAndTorqueCallback(DefaultForceCallback);
      body->setPositionOrientation(Ogre::Vector3(0,0,0), Euler(Ogre::Degree(ConvertFromGMYaw(0)), Ogre::Degree(0), Ogre::Degree(0)));
   CATCH("CreateNewtonBody")

   return ConvertToGMPointer(body);
}


GMFN double DestroyNewtonBody(double newton_body_ptr)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   delete newton_body;

   return TRUE;
}


GMFN double SetNewtonBodyPosition(double newton_body_ptr, double x, double z, double y)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   Ogre::Vector3 pos;
   Ogre::Quaternion orient;

   newton_body->getPositionOrientation(pos, orient);
   newton_body->setPositionOrientation(Ogre::Vector3(x, y, z), orient);

   return TRUE;
}


GMFN double GetNewtonBodyPosition(double newton_body_ptr)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   Ogre::Vector3 pos;
   Ogre::Quaternion orient;

   newton_body->getPositionOrientation(pos, orient);

   AcquireGMVectorGlobals();
   if (mVectorX != NULL)
   {
      *mVectorX = pos.x;
      *mVectorY = pos.z;
      *mVectorZ = pos.y;
   }

   return TRUE;
}


GMFN double SetNewtonBodyOrientation(double newton_body_ptr, double yaw, double pitch, double roll)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   Ogre::Vector3 pos;
   Ogre::Quaternion orient;

   newton_body->getPositionOrientation(pos, orient);
   newton_body->setPositionOrientation(pos, Euler(Ogre::Degree(ConvertFromGMYaw(yaw)), Ogre::Degree(pitch), Ogre::Degree(roll)));

   return TRUE;
}


GMFN double GetNewtonBodyOrientation(double newton_body_ptr)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   Ogre::Vector3 pos;
   Ogre::Quaternion orient;

   newton_body->getPositionOrientation(pos, orient);

   AcquireGMEulerGlobals();
   if (mEulerYaw != NULL)
   {
      *mEulerYaw = ConvertToGMYaw(orient.getYaw().valueDegrees());
      *mEulerPitch = orient.getPitch().valueDegrees();
      *mEulerRoll = orient.getRoll().valueDegrees();
   }

   return TRUE;
}


GMFN double AddNewtonBodyForce(double newton_body_ptr, double x, double z, double y)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   newton_body->addForce(Ogre::Vector3(x, y, z));

   return TRUE;
}


GMFN double AddNewtonBodyImpulse(double newton_body_ptr, double deltax, double deltaz, double deltay, double posx, double posz, double posy)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   newton_body->addImpulse(Ogre::Vector3(deltax, deltay, deltaz), Ogre::Vector3(posx, posy, posz));

   return TRUE;
}


GMFN double AddNewtonBodyTorque(double newton_body_ptr, double x, double z, double y)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   newton_body->addTorque(Ogre::Vector3(x, y, z));

   return TRUE;
}


GMFN double SetNewtonBodyAngularDamping(double newton_body_ptr, double x, double z, double y)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   newton_body->setAngularDamping(Ogre::Vector3(x, y, z));

   return TRUE;
}


GMFN double SetNewtonBodyCenterOfMass(double newton_body_ptr, double x, double z, double y)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   newton_body->setCenterOfMass(Ogre::Vector3(x, y, z));

   return TRUE;
}


GMFN double EnableNewtonBodyAutoSleep(double newton_body_ptr, double enable)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   newton_body->setAutoSleep(((int)enable == 0 ? 0 : 1));

   return TRUE;
}


GMFN double EnableNewtonBodyContinuousCollisionChecks(double newton_body_ptr, double enable)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   newton_body->setContinuousCollisionMode(((int)enable == 0 ? 0 : 1));

   return TRUE;
}


GMFN double SetNewtonBodyForce(double newton_body_ptr, double x, double z, double y)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   newton_body->setForce(Ogre::Vector3(x, y, z));

   return TRUE;
}


GMFN double SetNewtonBodyMassMatrix(double newton_body_ptr, double mass, double x, double z, double y)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   newton_body->setMassMatrix(mass, Ogre::Vector3(x, y, z));

   return TRUE;
}


GMFN double SetNewtonBodyLinearDamping(double newton_body_ptr, double damp)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   newton_body->setLinearDamping(damp);

   return TRUE;
}


GMFN double SetNewtonBodyMaterial(double newton_body_ptr, double material_id_ptr)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   OgreNewt::MaterialID *mat_id = ConvertFromGMPointer<OgreNewt::MaterialID*>(material_id_ptr);

   if (!mat_id)
      return FALSE;

   newton_body->setMaterialGroupID(mat_id);

   return TRUE;
}


GMFN double GetNewtonBodyMaterial(double newton_body_ptr)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return 0;

   return ConvertToGMPointer(newton_body->getMaterialGroupID());
}


GMFN double SetNewtonBodyOmega(double newton_body_ptr, double x, double z, double y)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   newton_body->setOmega(Ogre::Vector3(x, y, z));

   return TRUE;
}


GMFN double SetNewtonBodyTorque(double newton_body_ptr, double x, double z, double y)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   newton_body->setTorque(Ogre::Vector3(x, y, z));

   return TRUE;
}


GMFN double SetNewtonBodyVelocity(double newton_body_ptr, double x, double z, double y)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   newton_body->setVelocity(Ogre::Vector3(x, y, z));

   return TRUE;
}


GMFN double GetNewtonBodyType(double newton_body_ptr)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   newton_body->getType();

   return TRUE;
}


GMFN double FreezeNewtonBody(double newton_body_ptr)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   newton_body->freeze();

   return TRUE;
}


GMFN double UnfreezeNewtonBody(double newton_body_ptr)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   newton_body->unFreeze();

   return TRUE;
}


GMFN double SetNewtonBodyUserData(double newton_body_ptr, double data)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   newton_body->setUserData(ConvertFromGMPointer<void*>(data));

   return TRUE;
}


GMFN double GetNewtonBodyUserData(double newton_body_ptr)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return 0;

   return ConvertToGMPointer(newton_body->getUserData());
}


GMFN double AttachNewtonBodyToSceneNode(double newton_body_ptr, double scene_node_ptr)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   Ogre::SceneNode *node = ConvertFromGMPointer<Ogre::SceneNode*>(scene_node_ptr);

   if (!node)
      return FALSE;

   newton_body->attachNode(node);

   LockMutex lm(gMutex);

   GMInstance gminst;

   SceneNodeMap::iterator iter = mSceneNodeAttachments.find(node);
   if (iter != mSceneNodeAttachments.end())
      gminst = iter->second;

   gminst.BodyAttached = true;
   gminst.mBody = newton_body;

   mSceneNodeAttachments[node] = gminst;
   mNewtonBodyAttachments[newton_body] = node;

   // We are already attached to our GM object, so update body position/orientation
   if (mGMAPI && gminst.GMInstanceAttached)
   {
      gminst.mGMInstancePtr = mGMAPI->GetInstancePtr(gminst.mGMInstanceID);
      AcquireGMLocalVariablePointers(&gminst);

      // Snap to current position/orientation
      newton_body->setPositionOrientation(Ogre::Vector3(gminst.mGMInstancePtr->x, gminst.mGMInstancePtr->y, *gminst.pZ), Euler(Ogre::Degree(ConvertFromGMYaw(gminst.mGMInstancePtr->direction)), Ogre::Degree(*gminst.pPitch), Ogre::Degree(*gminst.pRoll)));
   }

   return TRUE;
}


GMFN double DetachNewtonBodyFromSceneNode(double newton_body_ptr, double scene_node_ptr)
{
   OgreNewt::Body *newton_body = ConvertFromGMPointer<OgreNewt::Body*>(newton_body_ptr);

   if (!newton_body)
      return FALSE;

   Ogre::SceneNode *node = ConvertFromGMPointer<Ogre::SceneNode*>(scene_node_ptr);

   if (!node)
      return FALSE;

   if (newton_body->getOgreNode() == node)
   {
      newton_body->attachNode(NULL);

      LockMutex lm(gMutex);

      SceneNodeMap::iterator iter = mSceneNodeAttachments.find(node);

      if (iter == mSceneNodeAttachments.end())
         return FALSE;

      // Remove from map if needed.
      (&iter->second)->BodyAttached = false;
      (&iter->second)->mBody = NULL;
      if (iter->second.GMInstanceAttached == false)
         mSceneNodeAttachments.erase(iter);

      mNewtonBodyAttachments.erase(mNewtonBodyAttachments.find(newton_body));
   }

   return TRUE;
}

#endif
