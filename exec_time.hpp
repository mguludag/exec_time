/*****************************************************************************
 * exec_time.hpp
 *
 * Created: 9/24/2021 2021 by mguludag
 *
 * Copyright 2021 mguludag. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/
#ifndef EXEC_TIME_HPP
#define EXEC_TIME_HPP

#include <iostream>
#include <chrono>
#include <ratio>

#define exec_time_ns \
    stdx::chrono::_details::exec_time_impl<int, std::nano>(__FUNCTION__, __LINE__, " ns")
#define exec_time_us \
    stdx::chrono::_details::exec_time_impl<double, std::micro>(__FUNCTION__, __LINE__, " us")
#define exec_time_ms \
    stdx::chrono::_details::exec_time_impl<double, std::milli>(__FUNCTION__, __LINE__, " ms")
#define exec_time_s \
    stdx::chrono::_details::exec_time_impl<double, std::ratio<1>>(__FUNCTION__, __LINE__, " s")
#define exec_time_m \
    stdx::chrono::_details::exec_time_impl<double, std::ratio<60>>(__FUNCTION__, __LINE__, " m")
#define exec_time_h \
    stdx::chrono::_details::exec_time_impl<double, std::ratio<3600>>(__FUNCTION__, __LINE__, " h")

#define exec_time_elapsed(exec_time_obj) exec_time_obj.elapsed_(__LINE__)

namespace stdx {
    namespace chrono {
        namespace _details {
            template<typename T = int, typename R = std::nano>
            class exec_time_impl
            {
            public:
                exec_time_impl() = delete;
                exec_time_impl(const exec_time_impl&) = delete;
                exec_time_impl& operator=(const exec_time_impl&) = delete;
                
                explicit exec_time_impl(const char *funcname = "", int line = 0, const char *unit = "")
                {
                    std::ios_base::sync_with_stdio(false);
                    m_funcname_ = std::string(funcname);
                    m_unit_ = std::string(unit);
                    m_begin_ = line;
                    m_start_ = std::chrono::high_resolution_clock::now();
                }
                
                exec_time_impl(exec_time_impl&& move)
                {
                    m_funcname_ = move.m_funcname_;
                    m_unit_ = move.m_unit_;
                    m_begin_ = move.m_begin_;
                    m_start_ = move.m_start;                 
                }
                
                exec_time_impl& operator=(exec_time_impl&& move)
                {
                    m_funcname_ = move.m_funcname_;
                    m_unit_ = move.m_unit_;
                    m_begin_ = move.m_begin_;
                    m_start_ = move.m_start;
                    return *this;                   
                }

                ~exec_time_impl()
                {
                    auto result = std::chrono::high_resolution_clock::now() - m_start_;
                    std::clog << m_funcname_ << " from line "
                              << m_begin_ << " to end executed in "
                              << std::chrono::duration<T, R>(result).count()
                              << m_unit_ << std::endl;
                }

                inline void elapsed_(const int line = 0)
                {
                    auto result = std::chrono::high_resolution_clock::now() - m_start_;
                    std::clog << m_funcname_ << " from line "
                              << m_begin_ << " to "
                              << line << " executed in "
                              << std::chrono::duration<T, R>(result).count()
                              << m_unit_ << std::endl;
                }

            private:
                std::chrono::time_point<std::chrono::high_resolution_clock> m_start_;
                std::string m_funcname_, m_unit_;
                int m_begin_;
            };
        } // namespace _details
    } // namespace chrono
} // namespace stdx


#endif // EXEC_TIME_HPP
