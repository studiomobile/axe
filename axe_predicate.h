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

#ifndef AXE_PREDICATE_H
#define AXE_PREDICATE_H

#include <utility>
#include "axe_trait.h"

namespace axe {

    //-------------------------------------------------------------------------
    /// is_alpha returns true for ASCII alpha characters
    //-------------------------------------------------------------------------
    struct is_alpha AXE_PREDICATE
    {
        template<class C>
        bool operator() (C c) const { return c >= C('A') && c <= C('Z') || c >= C('a') && c <= C('z') || c == C('_'); }
    };

    //-------------------------------------------------------------------------
    /// is_num returns true for single digits
    //-------------------------------------------------------------------------
    struct is_num AXE_PREDICATE
    {
        template<class C>
        bool operator() (C c) const { return c >= C('0') && c <= C('9'); }
    };

    //-------------------------------------------------------------------------
    /// is_alnum returns true for ASCII characters or numbers
    //-------------------------------------------------------------------------
    struct is_alnum AXE_PREDICATE
    {
        template<class ChartT>
        bool operator()(ChartT c) const { return is_alpha()(c) || is_num()(c); }
    };

    //-------------------------------------------------------------------------
    /// is_hex returns true for hex characters
    //-------------------------------------------------------------------------
    struct is_hex AXE_PREDICATE
    {
        template<class C>
        bool operator() (C c) const
        { 
            return is_num()(c) || c >= C('a') && c <= C('f') || c >= C('A') && c <= C('F');
        }
    };

    //-------------------------------------------------------------------------
    /// is_oct returns true for oct characters
    //-------------------------------------------------------------------------
    struct is_oct AXE_PREDICATE
    {
        template<class C>
        bool operator() (C c) const { return c >= C('0') && c <= C('7'); }
    };

    //-------------------------------------------------------------------------
    /// is_bin returns true for binary characters
    //-------------------------------------------------------------------------
    struct is_bin AXE_PREDICATE
    {
        template<class C>
        bool operator() (C c) const { return c == C('0') || c == C('1'); }
    };

    //-------------------------------------------------------------------------
    /// printable characters
    //-------------------------------------------------------------------------
    struct is_printable AXE_PREDICATE
    {
        template<class C>
        bool operator() (C c) const { return c >= C(' ') && c <= C('~'); }
    };

    //-------------------------------------------------------------------------
    /// is_space returns true for space characters
    //-------------------------------------------------------------------------
    struct is_space AXE_PREDICATE
    {
        template<class C>
        bool operator() (C c) const { return c == C(' ') || c == C('\t') || c == C('\n') || c == C('\r'); }
    };

    //-------------------------------------------------------------------------
    /// is_char returns true if value is equal to character
    //-------------------------------------------------------------------------
    template<class CharT>
    struct is_char_t AXE_PREDICATE
    {
        CharT c_;
    public:
        is_char_t(CharT c) : c_(c) {}
        bool operator ()(CharT c) const { return c_ == c; }
    };

    //-------------------------------------------------------------------------
    /// is_any returns true if value is in range specified by pair of characters
    //-------------------------------------------------------------------------
    template<class CharT = void>
    class is_any_t AXE_PREDICATE
    {
        CharT from_, to_; // specifies [from_, to_] range
    public:
        is_any_t(CharT from, CharT to) : from_(from), to_(to) {}

        template<class V>
        bool operator() (V value) const 
        { 
            static_assert(std::is_convertible<V, CharT>::value, "must be convertible to CharT");
            return value >= from_ && value <= to_;
        }
    };

    //-------------------------------------------------------------------------
    /// is_any_t<void> always returns true
    //-------------------------------------------------------------------------
    template<>
    class is_any_t<void> AXE_PREDICATE
    {
    public:

        template<class V>
        bool operator() (V) const { return true; }
    };

    //-------------------------------------------------------------------------
    /// is_any_t<const CharT*> returns true if value is present in zero terminated string
    //-------------------------------------------------------------------------
    template<class CharT>
    class is_any_t<const CharT*> AXE_PREDICATE
    {
        const CharT* str_;
    public:
        explicit is_any_t(const CharT* str) : str_(str) {}

        template<class V>
        bool operator() (V value) const 
        { 
            static_assert(std::is_convertible<V, CharT>::value, "must be convertible to CharT");
            const CharT* i = str_;
            while(i && *i && !(*i == value))
                ++i;
            
            return i && *i == value;
        }
    };

    //-------------------------------------------------------------------------
    /// p_and_t - predicate for AND operation on predicates
    //-------------------------------------------------------------------------
    template<class P1, class P2>
    class p_and_t AXE_PREDICATE
    {
        P1 p1_;
        P2 p2_;
    public:
        p_and_t(P1&& p1, P2&& p2) : p1_(std::forward<P1>(p1)), p2_(std::forward<P2>(p2)) {}

        template<class CharT>
        bool operator ()(CharT c) const { return p1_(c) && p2_(c); }
    };

    //-------------------------------------------------------------------------
    /// p_or_t - predicate for OR operation on predicates
    //-------------------------------------------------------------------------
    template<class P1, class P2>
    class p_or_t AXE_PREDICATE
    {
        P1 p1_;
        P2 p2_;
    public:
        p_or_t(P1&& p1, P2&& p2) : p1_(std::forward<P1>(p1)), p2_(std::forward<P2>(p2)) {}

        template<class CharT>
        bool operator ()(CharT c) const { return p1_(c) || p2_(c); }
    };

    //-------------------------------------------------------------------------
    /// p_xor_t - predicate for boolean XOR operation on predicates
    //-------------------------------------------------------------------------
    template<class P1, class P2>
    class p_xor_t AXE_PREDICATE
    {
        P1 p1_;
        P2 p2_;
    public:
        p_xor_t(P1&& p1, P2&& p2) : p1_(std::forward<P1>(p1)), p2_(std::forward<P2>(p2)) {}

        template<class CharT>
        bool operator ()(CharT c) const { return p1_(c) ^ p2_(c); }
    };

    //-------------------------------------------------------------------------
    /// p_xor_t - predicate for NOT operation
    //-------------------------------------------------------------------------
    template<class P1>
    class p_not_t AXE_PREDICATE
    {
        P1 p1_;
    public:
        p_not_t(P1&& p1) : p1_(std::forward<P1>(p1)) {}

        template<class CharT>
        bool operator ()(CharT c) const { return !p1_(c); }
    };
}

#endif
