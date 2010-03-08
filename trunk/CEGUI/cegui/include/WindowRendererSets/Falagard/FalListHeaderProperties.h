/***********************************************************************
    filename:   FalListHeaderProperties.h
    created:    Wed Jul 6 2005
    author:     Paul D Turner <paul@cegui.org.uk>
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2006 Paul D Turner & The CEGUI Development Team
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
#ifndef _FalListHeaderProperties_h_
#define _FalListHeaderProperties_h_

#include "../../CEGUIProperty.h"

// Start of CEGUI namespace section
namespace CEGUI
{
/*!
\brief
    Properties for the Falagard ListHeader
*/
namespace FalagardListHeaderProperties
{
/*!
\brief
   Property to access the segment widget type.

   \par Usage:
      - Name: SegmentWidgetType
      - Format: "[widgetTypeName]".

*/
class SegmentWidgetType : public Property
{
public:
   SegmentWidgetType() : Property(
	   "SegmentWidgetType",
	   "Property to get/set the widget type used when creating header segments.  Value should be \"[widgetTypeName]\".",
	   "")
   {}

   String   get(const PropertyReceiver* receiver) const;
   void   set(PropertyReceiver* receiver, const String& value);
};

}
} // End of  CEGUI namespace section


#endif  // end of guard _FalListHeaderProperties_h_
