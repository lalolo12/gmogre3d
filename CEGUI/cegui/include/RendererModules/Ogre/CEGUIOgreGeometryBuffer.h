/***********************************************************************
    filename:   CEGUIOgreGeometryBuffer.h
    created:    Tue Feb 17 2009
    author:     Paul D Turner
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2009 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#ifndef _CEGUIOgreGeometryBuffer_h_
#define _CEGUIOgreGeometryBuffer_h_

#include "../../CEGUIGeometryBuffer.h"
#include "CEGUIOgreRenderer.h"
#include "../../CEGUIRect.h"

#include <OgreMatrix4.h>
#include <OgreColourValue.h>
#include <OgreRenderOperation.h>

#include <utility>
#include <vector>

// Ogre forward refs
namespace Ogre
{
class RenderSystem;
}

// Start of CEGUI namespace section
namespace CEGUI
{
//! Implementation of CEGUI::GeometryBuffer for the Ogre engine
class OGRE_GUIRENDERER_API OgreGeometryBuffer : public GeometryBuffer
{
public:
    //! Constructor
    OgreGeometryBuffer(Ogre::RenderSystem& rs);
    //! Destructor
    virtual ~OgreGeometryBuffer();

    //! return the transformation matrix used for this buffer.
    const Ogre::Matrix4& getMatrix() const;

    // implement CEGUI::GeometryBuffer interface.
    void draw() const;
    void setTranslation(const Vector3& v);
    void setRotation(const Vector3& r);
    void setPivot(const Vector3& p);
    void setClippingRegion(const Rect& region);
    void appendVertex(const Vertex& vertex);
    void appendGeometry(const Vertex* const vbuff, uint vertex_count);
    void setActiveTexture(Texture* texture);
    void reset();
    Texture* getActiveTexture() const;
    uint getVertexCount() const;
    uint getBatchCount() const;
    void setRenderEffect(RenderEffect* effect);
    RenderEffect* getRenderEffect();

protected:
    //! convert CEGUI::colour into something Ogre can use
    Ogre::RGBA colourToOgre(const colour& col) const;
    //! update cached matrix
    void updateMatrix() const;
    //! Synchronise data in the hardware buffer with what's been added
    void syncHardwareBuffer() const;
    //! set up texture related states
    void initialiseTextureStates() const;

    //! vertex structure used internally and also by Ogre.
    struct OgreVertex
    {
        float x, y, z;
        Ogre::RGBA diffuse;
        float u, v;
    };

    //! Ogre render system we're to use.
    Ogre::RenderSystem& d_renderSystem;
    //! Texture that is set as active
    OgreTexture* d_activeTexture;
    //! rectangular clip region
    Rect d_clipRect;
    //! translation vector
    Vector3 d_translation;
    //! rotation vector
    Vector3 d_rotation;
    //! pivot point for rotation
    Vector3 d_pivot;
    //! RenderEffect that will be used by the GeometryBuffer
    RenderEffect* d_effect;
    //! offset to be applied to all geometry
    Vector2 d_texelOffset;
    //! model matrix cache
    mutable Ogre::Matrix4 d_matrix;
    //! true when d_matrix is valid and up to date
    mutable bool d_matrixValid;
    //! Render operation for this buffer.
    mutable Ogre::RenderOperation d_renderOp;
    //! H/W buffer where the vertices are rendered from.
    mutable Ogre::HardwareVertexBufferSharedPtr d_hwBuffer;
    //! whether the h/w buffer is in sync with the added geometry
    mutable bool d_sync;
    //! type to track info for per-texture sub batches of geometry
    typedef std::pair<Ogre::TexturePtr, uint> BatchInfo;
    //! type of container that tracks BatchInfos.
    typedef std::vector<BatchInfo> BatchList;
    //! list of texture batches added to the geometry buffer
    BatchList d_batches;
    //! type of container used to queue the geometry
    typedef std::vector<OgreVertex> VertexList;
    //! container where added geometry is stored.
    VertexList d_vertices;
};


} // End of  CEGUI namespace section

#endif  // end of guard _CEGUIOgreGeometryBuffer_h_
