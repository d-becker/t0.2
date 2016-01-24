/*
 * Copyright (C) 2016 Daniel Becker <beckerdaniel.dani@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED

namespace tetris {

/**
 * This is an opaque struct used by \c Drawable. More information
 * can be found there.
 */
class DrawingContextInfo;

/**
 * An interface that should be implemented by all classes that are intended to
 * be drawn. The game logic is separated from the GUI to make it independent of
 * the GUI framework used. It is achieved through an opaque struct,
 * \c DrawingContextInfo, which is the parameter of the draw method. The struct
 * is not defined in this library, it must be defined by the user who knows
 * what GUI framework they want to use. It should contain all the information
 * are necessary for drawing.
 */
class Drawable {
public:

  /**
   * Draws the object using the  information and data provided by \a dci.
   *
   * Note: The default implementation does nothing, it should be overridden
   * by subclasses.
   *
   * \param dci The struct containing all necessary information about the
   *        drawing context.
   */
  virtual void draw(DrawingContextInfo& dci __attribute__((unused))) {

  }
};

} // namespace tetris.

#endif // DRAWABLE_H_INCLUDED
