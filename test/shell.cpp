// Preshell - Interactive C/C++ preprocessor shell
// Copyright (C) 2013, Abel Sinkovics (abel@sinkovics.hu)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "test_shell.hpp"

#include <boost/test/unit_test.hpp>

using namespace preshell;

BOOST_AUTO_TEST_CASE(test_builtin_macro_definitions_are_available)
{
  config cfg = config::empty;
  cfg.builtin_macro_definitions = "#define FOO bar\n";
  test_shell sh(cfg);

  sh.line_available("FOO");

  BOOST_CHECK_EQUAL("bar", sh.normal());
}

BOOST_AUTO_TEST_CASE(test_line_with_builtin_macro_definitions)
{
  config cfg = config::empty;
  cfg.builtin_macro_definitions = "#define FOO bar\n";
  test_shell sh(cfg);

  sh.line_available("__LINE__");

  BOOST_CHECK_EQUAL("1", sh.normal());
}

BOOST_AUTO_TEST_CASE(test_displaying_errors_in_builtin_macro_definition)
{
  config cfg = config::empty;
  cfg.builtin_macro_definitions = "#error foo";

  test_shell sh(cfg);

  BOOST_CHECK(!sh.error().empty());
}

BOOST_AUTO_TEST_CASE(test_redefining_protected_name_in_builtin_macros)
{
  config cfg = config::empty;
  cfg.builtin_macro_definitions = "#define __STDC__ 13\n";

  test_shell sh(cfg);

  BOOST_CHECK(sh.error().empty());
}

BOOST_AUTO_TEST_CASE(
  test_redefining_protected_name_in_builtin_macros_with_spaces
)
{
  config cfg = config::empty;
  cfg.builtin_macro_definitions = "  #  define __STDC__ 13\n";

  test_shell sh(cfg);

  BOOST_CHECK(sh.error().empty());
}

BOOST_AUTO_TEST_CASE(test_including_standard_headers_with_default_config)
{
  config cfg = config::default_config;
  cfg.enable_warnings = false;

  test_shell sh(cfg);

  sh.line_available("#include <vector>");

  // Comparing to empty string produces a more informative error message when
  // the assertion fails
  BOOST_CHECK_EQUAL("", sh.error());
}

BOOST_AUTO_TEST_CASE(test_history_is_stored)
{
  std::vector<std::string> history;
  test_shell sh(history);

  sh.line_available("int");

  BOOST_REQUIRE_EQUAL(1, history.size());
  BOOST_CHECK_EQUAL("int", history.front());
}

BOOST_AUTO_TEST_CASE(test_empty_line_is_not_stored_in_history)
{
  std::vector<std::string> history;
  test_shell sh(history);

  sh.line_available("");

  BOOST_CHECK_EQUAL(0, history.size());
}

BOOST_AUTO_TEST_CASE(
  test_the_same_thing_following_each_other_is_not_added_to_history_twice
)
{
  std::vector<std::string> history;
  test_shell sh(history);

  sh.line_available("int");
  sh.line_available("int");

  BOOST_REQUIRE_EQUAL(1, history.size());
  BOOST_CHECK_EQUAL("int", history.front());
}

