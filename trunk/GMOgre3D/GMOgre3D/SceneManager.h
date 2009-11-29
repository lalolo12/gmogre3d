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

#ifndef GMOGRE_SCENE_MANAGER_H
#define GMOGRE_SCENE_MANAGER_H

#include "GMOgre3D.h"


GMFN double CreateSceneManager(double type)
{
   Ogre::SceneManager *scene_mgr = mRoot->createSceneManager(static_cast<Ogre::SceneType>((int)type), GenerateUniqueName());
   
   // Set our current to the only one that exists
   if (mSceneMgr == NULL)
   {
      mSceneMgr = scene_mgr;

      if (mFrameListener != NULL)
         mFrameListener->Create2DManager(mSceneMgr);

      mCollisionTools.setSceneManager(mSceneMgr);
   }

   return ConvertToGMPointer(scene_mgr);
}


GMFN double SetSceneManagerWorldGeometry(char *filename)
{
   try
   {   
      if (mSceneMgr == NULL)
         return FALSE;

      mSceneMgr->setWorldGeometry(filename);
   }
   catch(Ogre::Exception& e)
   {
      LogError(e.what());
      return FALSE;
   }

   return TRUE;
}


GMFN double EnableSkyBox(double enable, char *material_name)
{
   if (mSceneMgr == NULL)
      return FALSE;

   mSceneMgr->setSkyBox((enable != 0), material_name);

   return TRUE;
}


GMFN double EnableSkyDome(double enable, char *material_name, double curvature, double tiling)
{
   if (mSceneMgr == NULL)
      return FALSE;

   mSceneMgr->setSkyDome((enable != 0), material_name, curvature, tiling);

   return TRUE;
}


GMFN double EnableSkyPlane(double enable, char *material_name, double scale, double tiling)
{
   Ogre::Plane plane;
   plane.d = 5000;
   plane.normal = -Ogre::Vector3::UNIT_Y;
      
   if (mSceneMgr == NULL)
      return FALSE;

   mSceneMgr->setSkyPlane((enable != 0), plane, material_name, scale, tiling);

   return TRUE;
}


GMFN double SetAmbientLight(double color)
{
   if (mSceneMgr == NULL)
      return FALSE;

   mSceneMgr->setAmbientLight(Ogre::ColourValue(GetRedFromGMColor(color), GetGreenFromGMColor(color), GetBlueFromGMColor(color)));

   return TRUE;
}


GMFN double SetShadowTechnique(double type)
{
   if (mSceneMgr == NULL)
      return FALSE;
   
   mSceneMgr->setShadowTechnique(static_cast<Ogre::ShadowTechnique>((int)type));

   return TRUE;
}


GMFN double SetShadowFarDistance(double distance)
{
   if (mSceneMgr == NULL)
      return FALSE;

   mSceneMgr->setShadowFarDistance(distance);

   return TRUE;
}


GMFN double SetShadowColor(double color)
{
   if (mSceneMgr == NULL)
      return FALSE;

   mSceneMgr->setShadowColour(Ogre::ColourValue(GetRedFromGMColor(color), GetGreenFromGMColor(color), GetBlueFromGMColor(color)));

   return TRUE;
}


GMFN double SetFog(double type, double color, double density, double start, double end)
{
   if (mSceneMgr == NULL)
      return FALSE;

   mSceneMgr->setFog(static_cast<Ogre::FogMode>((int)type), Ogre::ColourValue(GetRedFromGMColor(color), GetGreenFromGMColor(color), GetBlueFromGMColor(color)), density, start, end);

   return TRUE;
}


GMFN double SaveScreenShot(char *filename)
{
   //mWindow->writeContentsToFile(filename);

   return TRUE;
}

#endif
