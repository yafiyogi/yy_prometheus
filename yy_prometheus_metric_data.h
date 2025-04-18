/*

  MIT License

  Copyright (c) 2024-2025 Yafiyogi

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

*/

#pragma once

#include <string>

#include "yy_cpp/yy_types.hpp"
#include "yy_cpp/yy_vector.h"
#include "yy_cpp/yy_observer_ptr.hpp"
#include "yy_values/yy_values_metric_data.hpp"

#include "yy_prometheus_metric_format.h"
#include "yy_prometheus_metric_types.h"
#include "yy_values/yy_values_metric_data.hpp"

namespace yafiyogi::yy_prometheus {

struct MetricData:
      public yy_values::MetricData
{
    MetricData(const yy_values::MetricId & p_id) noexcept;
    MetricData(yy_values::MetricId && p_id,
               yy_values::Labels && p_labels) noexcept;

    MetricData(yy_values::MetricId && p_id,
               yy_values::Labels && p_labels,
               std::string_view p_help,
               yy_prometheus::MetricType p_type,
               yy_prometheus::MetricUnit p_unit) noexcept;

    constexpr MetricData() noexcept = default;
    constexpr MetricData(const MetricData &) noexcept = default;
    constexpr MetricData(MetricData && p_other) noexcept:
      yy_values::MetricData(std::move(p_other)),
      m_help(std::move(p_other.m_help)),
      m_type(p_other.m_type),
      m_unit(p_other.m_unit),
      m_format(p_other.m_format)
    {
      p_other.m_type = MetricType::None;
      p_other.m_unit = MetricUnit::None;
      p_other.m_format = &NoFormat;
    }

    constexpr MetricData & operator=(const MetricData &) noexcept = default;
    constexpr MetricData & operator=(MetricData && p_other) noexcept
    {
      if(this != &p_other)
      {
        yy_values::MetricData::operator=(std::move(p_other));

        m_help = std::move(p_other.m_help);
        m_type = p_other.m_type;
        p_other.m_type = MetricType::None;
        m_unit = p_other.m_unit;
        p_other.m_unit = MetricUnit::None;
        m_format = p_other.m_format;
        p_other.m_format = &NoFormat;
      }

      return *this;
    }

    constexpr bool operator<(const MetricData & p_other) const noexcept
    {
      return compare(p_other) < 0;
    }

    constexpr bool operator==(const MetricData & p_other) const noexcept
    {
      return compare(p_other) == 0;
    }

    constexpr int compare(const MetricData & p_other) const noexcept
    {
      if(int comp = Id().compare(p_other.Id());
         0 != comp)
      {
        return comp;
      }

      if(int comp = static_cast<int>(m_type) - static_cast<int>(p_other.m_type);
         0 != comp)
      {
        return comp;
      }

      if(int comp = static_cast<int>(m_unit) - static_cast<int>(p_other.m_unit);
         0 != comp)
      {
        return comp;
      }

      return Labels().compare(p_other.Labels());
    }

    void Format(MetricBuffer & p_buffer) const
    {
      m_format(p_buffer, *this);
    }

    constexpr const std::string & Help() const noexcept
    {
      return m_help;
    }

    constexpr yy_prometheus::MetricType MetricType() const noexcept
    {
      return m_type;
    }

    constexpr void MetricType(yy_prometheus::MetricType p_type) noexcept
    {
      m_type = p_type;
    }

    constexpr yy_prometheus::MetricUnit MetricUnit() const noexcept
    {
      return m_unit;
    }

    constexpr void MetricUnit(yy_prometheus::MetricUnit p_unit) noexcept
    {
      m_unit = p_unit;
    }

    void MetricFormat(MetricFormatFn p_format) noexcept
    {
      m_format = p_format;
    }

    void swap(MetricData & p_other) noexcept;

    friend void swap(MetricData & p_lhs, MetricData & p_rhs) noexcept
    {
      p_lhs.swap(p_rhs);
    }

  private:
    std::string m_help{};
    yy_prometheus::MetricType m_type = yy_prometheus::MetricType::None;
    yy_prometheus::MetricUnit m_unit = MetricUnit::None;
    MetricFormatFn m_format = &NoFormat;
};

using MetricDataObsPtr = yy_data::observer_ptr<MetricData>;
using MetricDataVector = yy_quad::simple_vector<MetricData>;
using MetricDataVectorPtr = yy_data::observer_ptr<MetricDataVector>;

} // namespace yafiyogi::yy_prometheus
