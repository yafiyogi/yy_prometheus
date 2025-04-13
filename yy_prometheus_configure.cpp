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

#include <string_view>

#include "yy_cpp/yy_make_lookup.h"
#include "yy_cpp/yy_string_case.h"
#include "yy_cpp/yy_string_util.h"

#include "yy_values/yy_values_metric_data.hpp"

#include "yy_prometheus_configure.h"

namespace yafiyogi::yy_prometheus {

using namespace std::string_view_literals;

namespace {

static constexpr const auto metric_type_names =
  yy_data::make_lookup<std::string_view, MetricType>(MetricType::None,
                                                     {{g_metric_type_gauge, MetricType::Gauge}});

static constexpr const auto metric_types =
  yy_data::make_lookup<MetricType, std::string_view>(""sv,
                                                     {{MetricType::Gauge, g_metric_type_gauge}});

constexpr const auto g_timestamp_types =
  yy_data::make_lookup<std::string_view,
                       yy_prometheus::MetricTimestamp>(yy_prometheus::MetricTimestamp::On,
                                                       {{"on"sv, yy_prometheus::MetricTimestamp::On},
                                                        {"off"sv, yy_prometheus::MetricTimestamp::Off}});

static constexpr const auto metric_unit_names =
  yy_data::make_lookup<std::string_view, MetricUnit>(MetricUnit::None,
                                                     {{g_metric_unit_time, MetricUnit::Time},
                                                      {"temp"sv, MetricUnit::Temperature},
                                                      {g_metric_unit_temperature, MetricUnit::Temperature},
                                                      {g_metric_unit_length, MetricUnit::Length},
                                                      {g_metric_unit_bytes, MetricUnit::Bytes},
                                                      {g_metric_unit_percent, MetricUnit::Percent},
                                                      {g_metric_unit_voltage, MetricUnit::Voltage},
                                                      {g_metric_unit_current, MetricUnit::Current},
                                                      {g_metric_unit_energy, MetricUnit::Energy},
                                                      {g_metric_unit_power, MetricUnit::Power},
                                                      {g_metric_unit_mass, MetricUnit::Mass}});

static constexpr const auto metric_units =
  yy_data::make_lookup<MetricUnit, std::string_view>(""sv,
                                                     {{MetricUnit::Time, g_metric_unit_time},
                                                      {MetricUnit::Temperature, g_metric_unit_temperature},
                                                      {MetricUnit::Length, g_metric_unit_length},
                                                      {MetricUnit::Bytes, g_metric_unit_bytes},
                                                      {MetricUnit::Percent, g_metric_unit_percent},
                                                      {MetricUnit::Voltage, g_metric_unit_voltage},
                                                      {MetricUnit::Current, g_metric_unit_current},
                                                      {MetricUnit::Energy, g_metric_unit_energy},
                                                      {MetricUnit::Power, g_metric_unit_power},
                                                      {MetricUnit::Mass, g_metric_unit_mass}});

} // anonymous namespace

std::string_view decode_metric_type(MetricType p_type)
{
  return metric_types.lookup(p_type);
}

MetricType decode_metric_type_name(std::optional<std::string_view> p_type_name)
{
  if(p_type_name.has_value())
  {
    const std::string type_name{yy_util::to_lower(yy_util::trim(p_type_name.value()))};

    return metric_type_names.lookup(type_name);
  }

  return MetricType::None;
}

MetricTimestamp decode_metric_timestamp(std::string_view p_timestamp,
                                        MetricTimestamp p_default_timestamp)
{
  return g_timestamp_types.lookup(yy_util::to_lower(yy_util::trim(p_timestamp)),
                                  p_default_timestamp);

}

std::string_view decode_metric_unit(MetricUnit p_unit)
{
  return metric_units.lookup(p_unit);
}

MetricUnit decode_metric_unit_name(const std::optional<std::string_view> p_unit_name)
{
  if(p_unit_name.has_value())
  {
    const std::string unit_name{yy_util::to_lower(yy_util::trim(p_unit_name.value()))};

    return metric_unit_names.lookup(unit_name);
  }

  return MetricUnit::None;
}

} // namespace yafiyogi::yy_prometheus
