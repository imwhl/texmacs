
/******************************************************************************
* MODULE     : poor_italic.cpp
* DESCRIPTION: Emulation of slanted fonts
* COPYRIGHT  : (C) 2016  Joris van der Hoeven
*******************************************************************************
* This software falls under the GNU general public license version 3 or later.
* It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
* in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
******************************************************************************/

#include "font.hpp"
#include "analyze.hpp"
#include "frame.hpp"

/******************************************************************************
* True Type fonts
******************************************************************************/

struct poor_italic_font_rep: font_rep {
  font   base;
  double xslant;

  poor_italic_font_rep (string name, font base, double xslant);

  bool   supports (string c);
  void   get_extents (string s, metric& ex);
  void   get_xpositions (string s, SI* xpos);
  void   get_xpositions (string s, SI* xpos, bool lig);
  void   get_xpositions (string s, SI* xpos, SI xk);
  void   draw_fixed (renderer ren, string s, SI x, SI y, SI* xpos);
  void   draw_fixed (renderer ren, string s, SI x, SI y);
  void   draw_fixed (renderer ren, string s, SI x, SI y, bool lig);
  void   draw_fixed (renderer ren, string s, SI x, SI y, SI xk);
  font   magnify (double zoomx, double zoomy);
  void   advance_glyph (string s, int& pos);
  glyph  get_glyph (string s);
  int    index_glyph (string s, font_metric& fnm, font_glyphs& fng);
  double get_left_slope  (string s);
  double get_right_slope (string s);
  SI     get_left_correction  (string s);
  SI     get_right_correction  (string s);
};

/******************************************************************************
* Initialization of main font parameters
******************************************************************************/

poor_italic_font_rep::poor_italic_font_rep (string name, font b, double xs):
  font_rep (name, b), base (b), xslant (xs)
{
  this->copy_math_pars (base);
  this->slope += xslant;
}

/******************************************************************************
* Getting extents and drawing strings
******************************************************************************/

bool
poor_italic_font_rep::supports (string s) {
  return base->supports (s);
}

void
poor_italic_font_rep::get_extents (string s, metric& ex) {
  base->get_extents (s, ex);
  ex->x3 += (SI) floor (xslant * ex->y3);
  ex->x4 += (SI) floor (xslant * ex->y4);
}

void
poor_italic_font_rep::get_xpositions (string s, SI* xpos) {
  base->get_xpositions (s, xpos);
}

void
poor_italic_font_rep::get_xpositions (string s, SI* xpos, bool lig) {
  base->get_xpositions (s, xpos, lig);
}

void
poor_italic_font_rep::get_xpositions (string s, SI* xpos, SI xk) {
  base->get_xpositions (s, xpos, xk);
}

void
poor_italic_font_rep::draw_fixed (renderer ren, string s,
                                  SI x, SI y, SI* xpos) {
  int i=0;
  while (i < N(s)) {
    int start= i;
    base->advance_glyph (s, i);
    string ss= s (start, i);
    font_metric fnm;
    font_glyphs fng;
    int c= index_glyph (ss, fnm, fng);
    if (c >= 0) ren->draw (c, fng, x + xpos[start], y);
  }
}

void
poor_italic_font_rep::draw_fixed (renderer ren, string s, SI x, SI y) {
  if (ren->is_screen) {
    STACK_NEW_ARRAY (xpos, SI, N(s)+1);
    get_xpositions (s, xpos);
    draw_fixed (ren, s, x, y, xpos);
    STACK_DELETE_ARRAY (xpos);
  }
  else {
    ren->set_transformation (slanting (point (0.0, 0.0), xslant));
    base->draw_fixed (ren, s, x, y);
    ren->reset_transformation ();
  }
}

void
poor_italic_font_rep::draw_fixed (renderer ren, string s, SI x, SI y, bool l) {
  if (ren->is_screen) {
    STACK_NEW_ARRAY (xpos, SI, N(s)+1);
    get_xpositions (s, xpos, l);
    draw_fixed (ren, s, x, y, xpos);
    STACK_DELETE_ARRAY (xpos);
  }
  else {
    ren->set_transformation (slanting (point (0.0, 0.0), xslant));
    base->draw_fixed (ren, s, x, y, l);
    ren->reset_transformation ();
  }
}

void
poor_italic_font_rep::draw_fixed (renderer ren, string s, SI x, SI y, SI xk) {
  if (ren->is_screen) {
    STACK_NEW_ARRAY (xpos, SI, N(s)+1);
    get_xpositions (s, xpos, xk);
    draw_fixed (ren, s, x, y, xpos);
    STACK_DELETE_ARRAY (xpos);
  }
  else {
    ren->set_transformation (slanting (point (0.0, 0.0), xslant));
    base->draw_fixed (ren, s, x, y, xk);
    ren->reset_transformation ();
  }
}

font
poor_italic_font_rep::magnify (double zoomx, double zoomy) {
  return poor_italic_font (base->magnify (zoomx, zoomy),
                           xslant * (zoomx / zoomy));
}

/******************************************************************************
* Glyph manipulations
******************************************************************************/

void
poor_italic_font_rep::advance_glyph (string s, int& pos) {
  base->advance_glyph (s, pos);
}

glyph
poor_italic_font_rep::get_glyph (string s) {
  glyph gl= base->get_glyph (s);
  return slanted (gl, xslant);
}

int
poor_italic_font_rep::index_glyph (string s, font_metric& fnm,
                                             font_glyphs& fng) {
  int c= base->index_glyph (s, fnm, fng);
  fnm= slanted (fnm, xslant);
  fng= slanted (fng, xslant);
  return c;
}

/******************************************************************************
* Italic correction
******************************************************************************/

double
poor_italic_font_rep::get_left_slope (string s) {
  return base->get_left_slope (s) + xslant;
}

double
poor_italic_font_rep::get_right_slope (string s) {
  return base->get_right_slope (s) + xslant;
}

SI
poor_italic_font_rep::get_left_correction (string s) {
  if (N(s) == 0) return 0;
  int pos= 0;
  tm_char_forwards (s, pos);
  string r= s (0, pos);
  metric ex;
  base->get_extents (s, ex);
  SI dx= 0;
  if (ex->y1 < 0) dx= (SI) (xslant * (-ex->y1));
  // FIXME: we should apply a smaller correction if there is no ink
  // in the bottom left corner (e.g. 'q' as compared to 'p')
  return base->get_left_correction (s) + dx;
}

SI
poor_italic_font_rep::get_right_correction (string s) {
  if (N(s) == 0) return 0;
  int pos= N(s);
  tm_char_backwards (s, pos);
  string r= s (pos, N(s));
  metric ex;
  base->get_extents (s, ex);
  SI dx= 0;
  if (ex->y2 > 0) dx= (SI) (xslant * ex->y2);
  // FIXME: we should apply a smaller correction if there is no ink
  // in the upper right corner (e.g. 'b' as compared to 'd')
  return base->get_right_correction (s) + dx;
}

/******************************************************************************
* Interface
******************************************************************************/

font
poor_italic_font (font base, double slant) {
  string name= "pooritalic[" * base->res_name;
  if (slant != 0.25) name << "," << as_string (slant);
  name << "]";
  return make (font, name, tm_new<poor_italic_font_rep> (name, base, slant));
}