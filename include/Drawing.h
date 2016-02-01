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

#ifndef DRAWING_H_INCLUDED
#define DRAWING_H_INCLUDED

namespace tetris {

/**
 * This is an opaque struct used by \c Drawable. More information
 * can be found there.
 */
class DrawingContextInfo;

/**
 * An interface that provides a method, \a draw, which contains the drawing
 * logic for a tetris object. More information can be found in the description
 * of the \c Drawable class.
 */
struct DrawingTool {
  virtual ~DrawingTool() {}

  /**
   * Draws the object it is associated with using the information and data
   * provided by \a dci.
   *
   * Note: The default implementation does nothing, it should be overridden
   * by subclasses.
   *
   * \param dci The struct containing all necessary information about the
   *        drawing context.
   */
  virtual void draw(DrawingContextInfo& dci) = 0;
};

/**
 * An interface that should be implemented by all classes that are intended to
 * be drawn. The game logic is separated from the GUI to make it independent of
 * the GUI framework used.
 *
 * The drawing logic is the following: every object that inherits \c Drawable
 * has a polymorphic \c DrawingTool object associated with it. The \a draw
 * method of the \c Drawable object calls the virtual \a draw method of
 * the associated \c DrawingTool object. Using the provided getter and setter,
 * the \c DrawingTool object, and therefore the drawing logic of the
 * \c Drawable, can be changed at any time.
 *
 * The \a draw method of the \c Drawable class (and consequently the same
 * method of the \c DrawingTool class) takes a \c DrawingContextInfo object
 * reference as its argument. This is an opaque struct that is forward declared
 * here, but is not defined in this library. The purpose of this is to make
 * this library usable by different GUI frameworks. Every GUI framework does
 * drawing/painting differently, with different kinds of objects involved
 * in the process. Not defining \c DrawingContextInfo here allows the user
 * to define it in a way that suits her or his chosen GUI framework. Any object
 * that is necessary for drawing something can be made a member
 * of \c DrawingContextInfo. The user should also subclass \c DrawingTool and
 * implement its \a draw method in a way that can handle the framework-specific
 * \c DrawingContextInfo.
 */
class Drawable {
public:

  /**
   * Returns a (smart) pointer to the \c DrawingTool object of this \c Drawable.
   *
   * \return A (smart) pointer to the \c DrawingTool object of this \c Drawable.
   */
  std::shared_ptr<DrawingTool> getDrawingTool() {
    return m_dt;
  }

  /**
   * Sets the \c DrawingTool object of this \c Drawable to the one pointed to
   * by \a dt.
   *
   * \param dt A (smart) pointer to the \c DrawingTool object that will be
   *        set as the \c DrawingTool object of this \c Drawable.
   */
  void setDrawingTool(std::shared_ptr<DrawingTool> dt) {
    m_dt = dt;
  }

  /**
   * Draws the object using the  information and data provided by \a dci by
   * calling the \a draw method of the associated \c DrawingTool object if
   * that is not null; otherwise it does nothing.
   *
   * \param dci The struct containing all necessary information about the
   *        drawing context.
   */
  void draw(DrawingContextInfo& dci) {
    if (m_dt != nullptr) {
      m_dt->draw(dci);
    }
  }

private:
  std::shared_ptr<DrawingTool> m_dt = nullptr;
};

} // namespace tetris.

#endif // DRAWING_H_INCLUDED
