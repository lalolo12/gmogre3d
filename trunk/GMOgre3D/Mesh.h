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

#ifndef GMOGRE_MESH_H
#define GMOGRE_MESH_H

#include "GMOgre3D.h"


static Ogre::String mesh_name;
static Ogre::String mesh_group_name;


GMFN double CreateMesh(char *mesh_name, char *group = const_cast<char*>(Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME.c_str()))
{
   Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual(mesh_name, group);

   if (mesh.isNull())
      return FALSE;

   return TRUE;
}


GMFN double LoadMesh1(char *mesh, char *group = const_cast<char*>(Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME.c_str()))
{
   mesh_name = mesh;
   mesh_group_name = group;

   return TRUE;
}


GMFN double LoadMesh2(double vertex_buffer_usage = Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, double index_buffer_usage = Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, double disable_vertex_buffer_shadow = false, double disable_index_buffer_shadow = false)
{
   Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().load(mesh_name, mesh_group_name, static_cast<Ogre::HardwareBuffer::Usage>((int)vertex_buffer_usage), static_cast<Ogre::HardwareBuffer::Usage>((int)index_buffer_usage), (disable_vertex_buffer_shadow == 0), (disable_index_buffer_shadow == 0));

   if (mesh.isNull())
      return FALSE;

   return TRUE;
}


GMFN double SetMeshSkeletonName(char *mesh_name, char *skeleton)
{
   Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().getByName(mesh_name);

   if (mesh.isNull())
      return FALSE;
  
   mesh->setSkeletonName(skeleton);

   return TRUE;
}


GMFN double SuggestMeshTangentVectorSourceCoordSet(char *mesh_name, double target_semantic)
{
   Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().getByName(mesh_name);

   if (mesh.isNull())
      return FALSE;

   unsigned short source_coord_set;
   unsigned short index;

   mesh->suggestTangentVectorBuildParams(static_cast<Ogre::VertexElementSemantic>((int)target_semantic), source_coord_set, index);

   return (double)source_coord_set;
}


GMFN double SuggestMeshTangentVectorIndex(char *mesh_name, double target_semantic)
{
   Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().getByName(mesh_name);

   if (mesh.isNull())
      return FALSE;

   unsigned short source_coord_set;
   unsigned short index;

   mesh->suggestTangentVectorBuildParams(static_cast<Ogre::VertexElementSemantic>((int)target_semantic), source_coord_set, index);

   return (double)index;
}


GMFN double BuildMeshTangentVectors1(char *mesh)
{
   mesh_name = mesh;

   return TRUE;
}


GMFN double BuildMeshTangentVectors2(double target_semantic, double source_coord_set, double index, double split_mirrored, double split_rotated)
{
   Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().getByName(mesh_name);

   if (mesh.isNull())
      return FALSE;
  
   mesh->buildTangentVectors(static_cast<Ogre::VertexElementSemantic>((int)target_semantic), source_coord_set, index, (split_mirrored != 0), (split_rotated != 0));

   return TRUE;
}


GMFN double ExportMeshToFile(char *mesh_name, char *mesh_filename)
{
   Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().getByName(mesh_name);

   if (mesh.isNull())
      return FALSE;

   Ogre::MeshSerializer ser;
   ser.exportMesh(mesh.getPointer(), mesh_filename);

   return TRUE;
}

#endif
