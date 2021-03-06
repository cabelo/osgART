/* -*-c++-*- 
 * 
 * osgART - Augmented Reality ToolKit for OpenSceneGraph
 * 
 * Copyright (C) 2005-2009 Human Interface Technology Laboratory New Zealand
 * Copyright (C) 2010-2014 Raphael Grasset, Julian Looser, Hartmut Seichter
 *
 * This library is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the osgart.org website.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
*/

// std include

// OpenThreads include

// OSG include
#include <osg/Switch>
#include <osg/Notify>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>

// local include
#include "osgART/BaseCallback"



namespace osgART {

	void addEventCallback(osg::Node* node, osg::NodeCallback* cb)
	{
		/* paranoia check */
		if (!node) return;

		/* add initial callback */
		if (!node->getEventCallback())
		{
			node->setEventCallback(cb);

		} else if (cb)
		{
			node->getEventCallback()->addNestedCallback(cb);
		}
	}


	void removeEventCallback(osg::Node* node, osg::NodeCallback* cb) {

	   if (!node || !cb) return;    // Sanity check

	   osg::NodeCallback* n = node->getEventCallback();
	   if (!n) return;                // There is no callback list

	   // Check the first callback
	   if (n == cb) {
		   // The first callback matches, so remove it, and reattach its child (which might be NULL)
		   node->setEventCallback(n->getNestedCallback());
		   return;
	   }

	   // Check nested callbacks
	   while (n) {

		   osg::NodeCallback* nested = n->getNestedCallback();
		   if (!nested) return;        // Run out of children

		   if (nested == cb) {
			   // The callback matches, so remove it, and reattach its child (which might be NULL)
			   n->setNestedCallback(nested->getNestedCallback());
			   return;
		   }

		   n = nested; // Move to next callback

	   }

   }

};
