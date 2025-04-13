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

#include "fmt/format.h"

#include "yy_values/yy_values_metric_id_fmt.hpp"

#include "yy_prometheus_metric_data.h"

namespace yafiyogi::yy_prometheus {

MetricData::MetricData(const yy_values::MetricId & p_id) noexcept:
  yy_values::MetricData(p_id)
{
}

MetricData::MetricData(yy_values::MetricId && p_id,
                       yy_values::Labels && p_labels) noexcept:
  yy_values::MetricData(std::move(p_id),
                        std::move(p_labels))
{
}

MetricData::MetricData(yy_values::MetricId && p_id,
                       yy_values::Labels && p_labels,
                       std::string_view p_help,
                       yy_prometheus::MetricType p_type,
                       yy_prometheus::MetricUnit p_unit) noexcept:
  yy_values::MetricData(std::move(p_id),
                        std::move(p_labels)),
  m_help(p_help),
  m_type(p_type),
  m_unit(p_unit)
{
}

void MetricData::swap(MetricData & p_other) noexcept
{
  if(this != &p_other)
  {
    yy_values::MetricData::swap(p_other);
    std::swap(m_help, p_other.m_help);
    std::swap(m_type, p_other.m_type);
    std::swap(m_unit, p_other.m_unit);
    std::swap(m_format, p_other.m_format);
  }
}

} // namespace yafiyogi::yy_prometheus
