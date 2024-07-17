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

#include "yy_cpp/yy_make_lookup.h"
#include "yy_cpp/yy_string_case.h"
#include "yy_cpp/yy_string_util.h"

#include "yy_prometheus_metric_data.h"

#include "yy_prometheus_configure.h"

namespace yafiyogi::yy_prometheus {

static constexpr const std::string_view g_type_guage{"gauge"};

static constexpr const auto metric_types =
  yy_data::make_lookup<std::string_view, MetricType>({{g_type_guage, MetricType::Guage}});


MetricType decode_metric_type(std::optional<std::string_view> p_type_name)
{
  if(p_type_name.has_value())
  {
    const std::string type_name{yy_util::to_lower(yy_util::trim(p_type_name.value()))};

    return metric_types.lookup(type_name, MetricType::None);
  }

  return MetricType::None;
}

static constexpr std::string_view g_unit_time{"time"};
static constexpr std::string_view g_unit_temp{"temp"};
static constexpr std::string_view g_unit_temperature{"temperature"};
static constexpr std::string_view g_unit_length{"length"};
static constexpr std::string_view g_unit_bytes{"bytes"};
static constexpr std::string_view g_unit_percent{"percent"};
static constexpr std::string_view g_unit_voltage{"voltage"};
static constexpr std::string_view g_unit_current{"current"};
static constexpr std::string_view g_unit_energy{"energy"};
static constexpr std::string_view g_unit_power{"power"};
static constexpr std::string_view g_unit_mass{"mass"};

static constexpr const auto metric_units =
  yy_data::make_lookup<std::string_view, MetricUnit>({{g_unit_time, MetricUnit::Time},
                                                      {g_unit_temp, MetricUnit::Temperature},
                                                      {g_unit_temperature, MetricUnit::Temperature},
                                                      {g_unit_length, MetricUnit::Length},
                                                      {g_unit_bytes, MetricUnit::Bytes},
                                                      {g_unit_percent, MetricUnit::Percent},
                                                      {g_unit_voltage, MetricUnit::Voltage},
                                                      {g_unit_current, MetricUnit::Current},
                                                      {g_unit_energy, MetricUnit::Energy},
                                                      {g_unit_power, MetricUnit::Power},
                                                      {g_unit_mass, MetricUnit::Mass}});

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
