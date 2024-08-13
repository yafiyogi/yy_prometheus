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

#include "fmt/core.h"

#include "yy_cpp/yy_make_lookup.h"

#include "yy_prometheus_configure.h"
#include "yy_prometheus_metric_data.h"
#include "yy_prometheus_metric_format.h"

namespace yafiyogi::yy_prometheus {

using namespace std::string_view_literals;

void FormatHeaders(MetricBuffer & p_buffer,
                          const MetricData & p_metric,
                          bool p_show_unit)
{
  fmt::format_to(std::back_inserter(p_buffer),
                 "# HELP {} {}\x0a"sv,
                 p_metric.Id(),
                 p_metric.Help());
  fmt::format_to(std::back_inserter(p_buffer),
                 "# TYPE {} {}\x0a"sv,
                 p_metric.Id(),
                 yy_prometheus::decode_metric_type(p_metric.Type()));
  if(p_show_unit)
  {
    fmt::format_to(std::back_inserter(p_buffer),
                   "# UNIT {} {}\x0a"sv,
                   p_metric.Id(),
                   yy_prometheus::decode_metric_unit(p_metric.Unit()));
  }
}

static void FormatMetricHeaders(MetricBuffer & p_buffer,
                                const MetricData & p_metric)
{
  fmt::format_to(std::back_inserter(p_buffer), "{}{{"sv,
                 p_metric.Id());

  bool first = true;
  p_metric.Labels().visit([&first, &p_buffer](const auto & label, const auto & value) {
    if(!first)
    {
      fmt::format_to(std::back_inserter(p_buffer), ","sv);
    }
    first = false;
    fmt::format_to(std::back_inserter(p_buffer),
                   "{}=\"{}\""sv,
                   label, value);
  });

  fmt::format_to(std::back_inserter(p_buffer), "}}");
}

static void FormatMetricTrailers(MetricBuffer & p_buffer,
                                 const MetricData & p_metric)
{
  fmt::format_to(std::back_inserter(p_buffer),
                 "{}\x0a"sv,
                 p_metric.Timestamp());
}

static void FormatGauge(MetricBuffer & p_buffer,
                         const MetricData & p_metric)
{
  FormatMetricHeaders(p_buffer, p_metric);

  fmt::format_to(std::back_inserter(p_buffer),
                 "{}"sv, p_metric.Value());

  FormatMetricTrailers(p_buffer, p_metric);
}


static void NoFormat(MetricBuffer & /* p_output */,
                     const MetricData & /* p_metric */)
{
};

static constexpr const auto metric_type_fn =
  yy_data::make_lookup<MetricType, MetricFormatFn>({{MetricType::Guage, &FormatGauge}});

MetricFormatFn decode_metric_format_fn(MetricType p_type)
{
  return metric_type_fn.lookup(p_type, &NoFormat);
}

} // namespace yafiyogi::yy_prometheus
