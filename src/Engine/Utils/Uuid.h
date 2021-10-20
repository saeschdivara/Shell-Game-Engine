#pragma once

#include "Engine/Core/shellpch.h"

#include <array>

namespace Shell {

    class Uuid {
    public:
        using value_type = uint8_t;

        static Uuid Create();
        static Uuid Create(const std::string & id);

        Uuid(value_type(&arr)[16]) noexcept
        {
            std::copy(std::cbegin(arr), std::cend(arr), std::begin(m_Data));
        }

        constexpr Uuid(std::array<value_type, 16> const & arr) noexcept : m_Data{arr} {}

        template<typename ForwardIterator>
        explicit Uuid(ForwardIterator first, ForwardIterator last)
        {
            if (std::distance(first, last) == 16)
                std::copy(first, last, std::begin(m_Data));
        }

        template<class CharT = char,
                class Traits = std::char_traits<CharT>,
                class Allocator = std::allocator<CharT>>
        inline std::basic_string<CharT, Traits, Allocator> toString(Uuid const & id)
        {
            std::basic_stringstream<CharT, Traits, Allocator> sstr;
            sstr << id;
            return sstr.str();
        }

    private:
        std::array<value_type, 16> m_Data;

        template <class Elem, class Traits>
        friend std::basic_ostream<Elem, Traits> & operator<<(std::basic_ostream<Elem, Traits> &s, Uuid const & id);
    };
    template <class Elem, class Traits>
    std::basic_ostream<Elem, Traits> & operator<<(std::basic_ostream<Elem, Traits> &s, Uuid const & id)
    {
        // save current flags
        std::ios_base::fmtflags f(s.flags());

        // manipulate stream as needed
        s << std::hex << std::setfill(static_cast<Elem>('0'))
          << std::setw(2) << (int)id.m_Data[0]
          << std::setw(2) << (int)id.m_Data[1]
          << std::setw(2) << (int)id.m_Data[2]
          << std::setw(2) << (int)id.m_Data[3]
          << '-'
          << std::setw(2) << (int)id.m_Data[4]
          << std::setw(2) << (int)id.m_Data[5]
          << '-'
          << std::setw(2) << (int)id.m_Data[6]
          << std::setw(2) << (int)id.m_Data[7]
          << '-'
          << std::setw(2) << (int)id.m_Data[8]
          << std::setw(2) << (int)id.m_Data[9]
          << '-'
          << std::setw(2) << (int)id.m_Data[10]
          << std::setw(2) << (int)id.m_Data[11]
          << std::setw(2) << (int)id.m_Data[12]
          << std::setw(2) << (int)id.m_Data[13]
          << std::setw(2) << (int)id.m_Data[14]
          << std::setw(2) << (int)id.m_Data[15];

        // restore original flags
        s.flags(f);

        return s;
    }

    template<class CharT = char,
            class Traits = std::char_traits<CharT>,
            class Allocator = std::allocator<CharT>>
    inline std::basic_string<CharT, Traits, Allocator> UuidToString(Uuid const & id)
    {
        std::basic_stringstream<CharT, Traits, Allocator> sstr;
        sstr << id;
        return sstr.str();
    }
}
