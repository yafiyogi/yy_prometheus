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

#include "yy_cpp/yy_vector.h"

namespace yafiyogi::yy_prometheus {

class MetricData;
enum class MetricType:uint8_t;

using MetricBuffer = yy_quad::simple_vector<char>;
using MetricFormatFn = void (*)(MetricBuffer & output,
                                const MetricData &);

void NoFormat(MetricBuffer & /* p_output */,
              const MetricData & /* p_metric */);

MetricFormatFn decode_metric_format_fn(MetricType type);
MetricFormatFn decode_metric_timestamp_format_fn(MetricType type);

void FormatHeaders(MetricBuffer & p_buffer,
                   const MetricData & p_metric,
                   bool p_show_unit);

} // namespace yafiyogi::yy_prometheus
