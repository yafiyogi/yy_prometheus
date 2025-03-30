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
#include "fmt/compile.h"

#include "yy_cpp/yy_int_util.h"
#include "yy_cpp/yy_make_lookup.h"

#include "yy_prometheus_configure.h"
#include "yy_prometheus_metric_data.h"
#include "yy_prometheus_metric_format.h"

namespace yafiyogi::yy_prometheus {

using namespace std::string_view_literals;
using namespace fmt::literals;

static constexpr auto help_format{"# HELP {} {}\x0a"_cf};
static constexpr auto type_format{"# TYPE {} {}\x0a"_cf};
static constexpr auto unit_format{"# UNIT {} {}\x0a"_cf};

void FormatHeaders(MetricBuffer & p_buffer,
                   const MetricData & p_metric,
                   bool p_show_unit)
{
  auto metric_type = yy_prometheus::decode_metric_type(p_metric.Type());
  p_buffer.reserve(p_buffer.size() + ((size_type{9} + p_metric.Id().size()) * (size_type{2} + size_type{p_show_unit})) + p_metric.Help().size() + metric_type.size());

  fmt::format_to(std::back_inserter(p_buffer),
                 help_format,
                 p_metric.Id(),
                 p_metric.Help());
  fmt::format_to(std::back_inserter(p_buffer),
                 type_format,
                 p_metric.Id(),
                 metric_type);
  if(p_show_unit)
  {
    auto metric_unit = yy_prometheus::decode_metric_unit(p_metric.Unit());
    p_buffer.reserve(p_buffer.size() + metric_unit.size());

    fmt::format_to(std::back_inserter(p_buffer),
                   unit_format,
                   p_metric.Id(),
                   metric_unit);
  }
}


static constexpr auto labels_start_format{"{}{{"_cf};
static constexpr auto labels_end_format{"}}"_cf};
static constexpr auto labels_separator_format{","_cf};
static constexpr auto label_format{"{}=\"{}\""_cf};

static void FormatMetricLabels(MetricBuffer & p_buffer,
                               const MetricData & p_metric)
{
  p_buffer.reserve(p_buffer.size() + p_metric.Id().size() + size_type{2});
  fmt::format_to(std::back_inserter(p_buffer),
                 labels_start_format,
                 p_metric.Id());

  bool first = true;
  p_metric.Labels().visit([&first, &p_buffer](const auto & label, const auto & value) {
    p_buffer.reserve(p_buffer.size() + size_type{!first} + label.size() + value.size() + size_type{3});
    if(!first)
    {
      fmt::format_to(std::back_inserter(p_buffer),
                     labels_separator_format);
    }
    first = false;
    fmt::format_to(std::back_inserter(p_buffer),
                   label_format,
                   label, value);
  });

  fmt::format_to(std::back_inserter(p_buffer),
                 labels_end_format);
}

static constexpr auto gauge_format{" {}\x0a"_cf};
static void FormatGauge(MetricBuffer & p_buffer,
                        const MetricData & p_metric)
{
  FormatMetricLabels(p_buffer, p_metric);

  auto value = p_metric.Value();
  p_buffer.reserve(p_buffer.size() + size_type{3} + value.size());

  fmt::format_to(std::back_inserter(p_buffer),
                 gauge_format,
                 value);
}

//static constexpr auto gauge_timestamp_format{" {} {}\x0a"_cf};
static constexpr auto gauge_timestamp_format{" {} {}\x0a"sv};
static void FormatGaugeTimestamp(MetricBuffer & p_buffer,
                                 const MetricData & p_metric)
{
  FormatMetricLabels(p_buffer, p_metric);

  auto value = p_metric.Value();
  auto timestamp = p_metric.Timestamp();

  p_buffer.reserve(p_buffer.size() + size_type{3} + value.size() + yy_util::Digits<decltype(timestamp)>::digits);

  fmt::format_to(std::back_inserter(p_buffer),
                 gauge_timestamp_format,
                 value,
                 timestamp);
}

void NoFormat(MetricBuffer & /* p_output */,
              const MetricData & /* p_metric */)
{
}

static constexpr const auto metric_type_fn =
  yy_data::make_lookup<MetricType, MetricFormatFn>(&NoFormat,
                                                   {{MetricType::Gauge, &FormatGauge}});

MetricFormatFn decode_metric_format_fn(MetricType p_type)
{
  return metric_type_fn.lookup(p_type);
}

static constexpr const auto metric_timestamp_type_fn =
  yy_data::make_lookup<MetricType, MetricFormatFn>(&NoFormat,
                                                   {{MetricType::Gauge, &FormatGaugeTimestamp}});

MetricFormatFn decode_metric_timestamp_format_fn(MetricType p_type)
{
  return metric_timestamp_type_fn.lookup(p_type);
}

} // namespace yafiyogi::yy_prometheus
