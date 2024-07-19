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

#include <string_view>

#include "yy_cpp/yy_make_lookup.h"
#include "yy_cpp/yy_string_case.h"
#include "yy_cpp/yy_string_util.h"

#include "yy_prometheus_metric_data.h"

#include "yy_prometheus_configure.h"

namespace yafiyogi::yy_prometheus {

using namespace std::string_view_literals;

static constexpr const auto metric_types =
  yy_data::make_lookup<std::string_view, MetricType>({{"guage"sv, MetricType::Guage}});


MetricType decode_metric_type(std::optional<std::string_view> p_type_name)
{
  if(p_type_name.has_value())
  {
    const std::string type_name{yy_util::to_lower(yy_util::trim(p_type_name.value()))};

    return metric_types.lookup(type_name, MetricType::None);
  }

  return MetricType::None;
}

static constexpr const auto metric_units =
  yy_data::make_lookup<std::string_view, MetricUnit>({{"time"sv, MetricUnit::Time},
                                                      {"temp"sv, MetricUnit::Temperature},
                                                      {"temperature"sv, MetricUnit::Temperature},
                                                      {"length"sv, MetricUnit::Length},
                                                      {"bytes"sv, MetricUnit::Bytes},
                                                      {"percent"sv, MetricUnit::Percent},
                                                      {"voltage"sv, MetricUnit::Voltage},
                                                      {"current"sv, MetricUnit::Current},
                                                      {"energy"sv, MetricUnit::Energy},
                                                      {"power"sv, MetricUnit::Power},
                                                      {"mass"sv, MetricUnit::Mass}});

MetricUnit decode_metric_unit(const std::optional<std::string_view> p_unit_name)
{
  if(p_unit_name.has_value())
  {
    const std::string unit_name{yy_util::to_lower(yy_util::trim(p_unit_name.value()))};

    return metric_units.lookup(unit_name, MetricUnit::None);
  }

  return MetricUnit::None;
}

} // namespace yafiyogi::yy_prometheus
