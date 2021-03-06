
/******************************************************************************
* MODULE     : impl_language.hpp
* COPYRIGHT  : (C) 1999  Joris van der Hoeven
*******************************************************************************
* This software falls under the GNU general public license version 3 or later.
* It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
* in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
******************************************************************************/

#ifndef IMPL_LANGUAGE_H
#define IMPL_LANGUAGE_H
#include "language.hpp"
#include "number_parser.hpp"

extern text_property_rep tp_normal_rep;
extern text_property_rep tp_hyph_rep;
extern text_property_rep tp_thin_space_rep;
extern text_property_rep tp_space_rep;
extern text_property_rep tp_dspace_rep;
extern text_property_rep tp_nb_thin_space_rep;
extern text_property_rep tp_nb_space_rep;
extern text_property_rep tp_nb_dspace_rep;
extern text_property_rep tp_period_rep;
extern text_property_rep tp_cjk_normal_rep;
extern text_property_rep tp_cjk_no_break_rep;
extern text_property_rep tp_cjk_period_rep;
extern text_property_rep tp_cjk_wide_period_rep;
extern text_property_rep tp_cjk_no_break_period_rep;
extern text_property_rep tp_half_rep;
extern text_property_rep tp_operator_rep;
extern text_property_rep tp_short_apply_rep;
extern text_property_rep tp_apply_rep;

struct abstract_language_rep: language_rep {
  abstract_language_rep (string s): language_rep(s) {};
  virtual bool belongs_to_identifier (char c);
  void parse_identifier (hashmap<string, string>& t, string s, int& pos);
  void parse_alpha (string s, int& pos);
  void parse_type (hashmap<string,string>& t, string s, int& pos);
  void parse_keyword (hashmap<string,string>& t, string s, int& pos);
  void parse_constant (hashmap<string,string>& t, string s, int& pos);
  void parse_blanks (string s, int& pos);
};

struct verb_language_rep: language_rep {
  verb_language_rep (string name);
  text_property advance (tree t, int& pos);
  array<int> get_hyphens (string s);
  void hyphenate (string s, int after, string& left, string& right);
  string get_color (tree t, int start, int end);
};

struct scheme_language_rep: language_rep {
  hashmap<string,string> colored;
  scheme_language_rep (string name);
  text_property advance (tree t, int& pos);
  array<int> get_hyphens (string s);
  void hyphenate (string s, int after, string& left, string& right);
  string get_color (tree t, int start, int end);
};

struct mathemagix_language_rep: abstract_language_rep {
  hashmap<string,string> colored;
  number_parser_rep number_parser;
  mathemagix_language_rep (string name);
  text_property advance (tree t, int& pos);
  array<int> get_hyphens (string s);
  void hyphenate (string s, int after, string& left, string& right);
  string get_color (tree t, int start, int end);

  bool belongs_to_identifier (char c);
  void parse_identifier_or_markup (hashmap<string, string>& t,
    string s, int& pos, bool postfix, bool& is_markup);
  void parse_keyword (hashmap<string,string>& t, string s, int& pos);
  void parse_modifier (hashmap<string,string>& t, string s, int& pos);
  void parse_class (hashmap<string,string>& t, string s, int& pos);
  void parse_postfix (hashmap<string,string>& t, string s, int& pos);
  void parse_constant (hashmap<string,string>& t, string s, int& pos);
};

struct r_language_rep: abstract_language_rep {
  hashmap<string,string> colored;
  number_parser_rep number_parser;
  r_language_rep (string name);
  text_property advance (tree t, int& pos);
  array<int> get_hyphens (string s);
  void hyphenate (string s, int after, string& left, string& right);
  string get_color (tree t, int start, int end);

  bool belongs_to_identifier (char c);
  void parse_identifier (hashmap<string, string>& t, string s, int& pos);
  void parse_identifier_or_markup (hashmap<string, string>& t,
    string s, int& pos, bool postfix, bool& is_markup);
  void parse_keyword (hashmap<string,string>& t, string s, int& pos);
  void parse_modifier (hashmap<string,string>& t, string s, int& pos);
  void parse_class (hashmap<string,string>& t, string s, int& pos);
  void parse_postfix (hashmap<string,string>& t, string s, int& pos);
  void parse_constant (hashmap<string,string>& t, string s, int& pos);
};


struct cpp_language_rep: abstract_language_rep {
  hashmap<string,string> colored;
  number_parser_rep number_parser;
  cpp_language_rep (string name);
  text_property advance (tree t, int& pos);
  array<int> get_hyphens (string s);
  void hyphenate (string s, int after, string& left, string& right);
  string get_color (tree t, int start, int end);

  void parse_preprocessing (string s, int & pos);
};

struct scilab_language_rep: abstract_language_rep {
  hashmap<string,string> colored;
  number_parser_rep number_parser;
  scilab_language_rep (string name);
  text_property advance (tree t, int& pos);
  array<int> get_hyphens (string s);
  void hyphenate (string s, int after, string& left, string& right);
  string get_color (tree t, int start, int end);

  bool belongs_to_identifier (char c);
  string parse_keywords (hashmap<string,string>& t, string s, int& pos);
  string parse_operators (hashmap<string,string>& t, string s, int& pos);
};

struct python_language_rep: abstract_language_rep {
  hashmap<string,string> colored;
  number_parser_rep number_parser;
  python_language_rep (string name);
  text_property advance (tree t, int& pos);
  array<int> get_hyphens (string s);
  void hyphenate (string s, int after, string& left, string& right);
  string get_color (tree t, int start, int end);

  string parse_keywords (hashmap<string,string>& t, string s, int& pos);
  string parse_operators (hashmap<string,string>& t, string s, int& pos);
};

struct java_language_rep: abstract_language_rep {
  hashmap<string,string> colored;
  number_parser_rep number_parser;
  java_language_rep (string name);
  text_property advance (tree t, int& pos);
  array<int> get_hyphens (string s);
  void hyphenate (string s, int after, string& left, string& right);
  string get_color (tree t, int start, int end);

  string parse_keywords (hashmap<string,string>& t, string s, int& pos);
  string parse_operators (hashmap<string,string>& t, string s, int& pos);
};

struct scala_language_rep: abstract_language_rep {
  hashmap<string,string> colored;
  number_parser_rep number_parser;
  scala_language_rep (string name);
  text_property advance (tree t, int& pos);
  array<int> get_hyphens (string s);
  void hyphenate (string s, int after, string& left, string& right);
  string get_color (tree t, int start, int end);

  string parse_keywords (hashmap<string,string>& t, string s, int& pos);
  string parse_operators (hashmap<string,string>& t, string s, int& pos);
};

struct fortran_language_rep: abstract_language_rep {
  hashmap<string,string> colored;
  number_parser_rep number_parser;
  fortran_language_rep (string name);
  text_property advance (tree t, int& pos);
  array<int> get_hyphens (string s);
  void hyphenate (string s, int after, string& left, string& right);
  string get_color (tree t, int start, int end);

  string parse_keywords (hashmap<string,string>& t, string s, int& pos);
  string parse_operators (hashmap<string,string>& t, string s, int& pos);
};

#endif // defined IMPL_LANGUAGE_H
