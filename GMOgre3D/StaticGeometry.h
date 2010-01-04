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

#ifndef GMOGRE_STATIC_GEOMETRY_H
#define GMOGRE_STATIC_GEOMETRY_H

#include "GMOgre3D.h"


GMFN double CreateStaticGeometry()
{
   if (mSceneMgr == NULL)
      return FALSE;

   Ogre::StaticGeometry *static_geo = mSceneMgr->createStaticGeometry(GenerateUniqueName());

   return ConvertToGMPointer(static_geo);
}


GMFN double DestroyStaticGeometry(double static_geo_ptr)
{
   if (mSceneMgr == NULL)
      return FALSE;

   Ogre::StaticGeometry *static_geo = ConvertFromGMPointer<Ogre::StaticGeometry*>(static_geo_ptr);

   if (static_geo == NULL)
      return FALSE;

   mSceneMgr->destroyStaticGeometry(static_geo);

   return TRUE;
}


GMFN double SetStaticGeometryRegionRenderingDistance(double static_geo_ptr, double distance)
{
   Ogre::StaticGeometry *static_geo = ConvertFromGMPointer<Ogre::StaticGeometry*>(static_geo_ptr);

   if (static_geo == NULL)
      return FALSE;

   static_geo->setRenderingDistance(distance);

   return TRUE;
}


GMFN double SetStaticGeometryRegionDimensions(double static_geo_ptr, double sizex, double sizez, double sizey)
{
   Ogre::StaticGeometry *static_geo = ConvertFromGMPointer<Ogre::StaticGeometry*>(static_geo_ptr);

   if (static_geo == NULL)
      return FALSE;

   static_geo->setRegionDimensions(Ogre::Vector3(sizex, sizey, sizez));

   return TRUE;
}


GMFN double SetStaticGeometryOrigin(double static_geo_ptr, double sizex, double sizez, double sizey)
{
   Ogre::StaticGeometry *static_geo = ConvertFromGMPointer<Ogre::StaticGeometry*>(static_geo_ptr);

   if (static_geo == NULL)
      return FALSE;

   static_geo->setRegionDimensions(Ogre::Vector3(sizex, sizey, sizez));

   return TRUE;
}


GMFN double AddStaticGeometryEntity(double static_geo_ptr, double entity_ptr, double posx, double posz, double posy, double orientx, double orientz, double orienty, double scalex, double scalez, double scaley)
{
   Ogre::StaticGeometry *static_geo = ConvertFromGMPointer<Ogre::StaticGeometry*>(static_geo_ptr);

   if (static_geo == NULL)
      return FALSE;

   Ogre::Entity *ent = ConvertFromGMPointer<Ogre::Entity*>(entity_ptr);

   if (ent == NULL)
      return FALSE;

   static_geo->addEntity(ent, Ogre::Vector3(posx, posy, posz), Ogre::Quaternion(orientx, orienty, orientz), Ogre::Vector3(scalex, scaley, scalez));

   return TRUE;
}


GMFN double BuildStaticGeometry(double static_geo_ptr)
{
   Ogre::StaticGeometry *static_geo = ConvertFromGMPointer<Ogre::StaticGeometry*>(static_geo_ptr);

   if (static_geo == NULL)
      return FALSE;

   static_geo->build();

   return TRUE;
}


GMFN double ResetStaticGeometry(double static_geo_ptr)
{
   Ogre::StaticGeometry *static_geo = ConvertFromGMPointer<Ogre::StaticGeometry*>(static_geo_ptr);

   if (static_geo == NULL)
      return FALSE;

   static_geo->reset();

   return TRUE;
}


GMFN double EnableStaticGeometryCastShadows(double static_geo_ptr, double enable)
{
   Ogre::StaticGeometry *static_geo = ConvertFromGMPointer<Ogre::StaticGeometry*>(static_geo_ptr);

   if (static_geo == NULL)
      return FALSE;

   static_geo->setCastShadows((enable != 0));

   return TRUE;
}

#endif