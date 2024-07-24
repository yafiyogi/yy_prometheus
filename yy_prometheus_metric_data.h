/*

  MIT License

  Copyright (c) 2024 Yafiyogi

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

#include <cstdint>

#include <string>

#include "yy_cpp/yy_vector.h"

#include "yy_prometheus_metric_types.h"
#include "yy_prometheus_labels.h"

namespace yafiyogi::yy_prometheus {

struct MetricData
{
    std::string id{};
    Labels labels{};
    std::string help{};
    int64_t timestamp{};
    std::string value{};
    MetricType type{MetricType::None};
    MetricUnit unit{MetricUnit::None};

    constexpr bool operator<(const MetricData & other) const noexcept
    {
      return std::tie(id, type, unit, labels) < std::tie(other.id, other.type, other.unit, other.labels);
    }

    constexpr bool operator==(const MetricData & other) const noexcept
    {
      return std::tie(id, type, unit, labels) == std::tie(other.id, other.type, other.unit, other.labels);
    }
};

using MetricDataVector = yy_quad::simple_vector<MetricData>;

} // namespace yafiyogi::yy_prometheus
