//-----------------------------------------------------------------------------
//  Copyright (C) 2011-2012, GB Research, LLC (www.gbresearch.com)
//  
//  Boost Software License - Version 1.0 - August 17th, 2003
//
//  Permission is hereby granted, free of charge, to any person or organization
//  obtaining a copy of the software and accompanying documentation covered by
//  this license (the "Software") to use, reproduce, display, distribute,
//  execute, and transmit the Software, and to prepare derivative works of the
//  Software, and to permit third-parties to whom the Software is furnished to
//  do so, all subject to the following:
//
//  The copyright notices in the Software and this entire statement, including
//  the above license grant, this restriction and the following disclaimer,
//  must be included in all copies of the Software, in whole or in part, and
//  all derivative works of the Software, unless such copies or derivative
//  works are solely in the form of machine-executable object code generated by
//  a source language processor.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
//  FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
//  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef AXE_SHORTCUT_H
#define AXE_SHORTCUT_H

#include "axe_terminal_function.h"
#include "axe_composite_function.h"
#include "axe_predicate_function.h"
#include "axe_numeric_function.h"

namespace axe {
namespace shortcuts {

    const auto _ = axe::r_any(); // any char
    const auto _d = axe::r_num(); // digit
    const auto _double = axe::r_double();
    const auto _int = axe::r_decimal();
    const auto _n = axe::r_char('\n'); // eol
    const auto _o = axe::r_oct(); // octal char
    const auto _r = axe::r_char('\r'); // CR
    const auto _s = axe::r_pred(axe::is_space()); // space separators
    const auto _t = axe::r_char('\t'); // tab char
    const auto _uint = axe::r_udecimal();
    const auto _w = axe::r_alnum(); // alnum word
    const auto _ws = axe::r_char(' '); // white space
    const auto _x = axe::r_hex(); // hex char
    const auto _z = axe::r_end(); // end of range
}}

#endif
