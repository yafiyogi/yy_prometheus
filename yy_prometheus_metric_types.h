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

namespace yafiyogi::yy_prometheus {

enum class MetricType:uint8_t {None, Gauge};

inline constexpr std::string_view g_metric_type_gauge{"gauge"};

enum class MetricUnit:uint8_t {None, Time, Temperature, Length, Bytes, Percent, Voltage, Current, Energy, Power, Mass};

enum class MetricTimestamp:uint8_t { On, Off };

inline constexpr std::string_view g_metric_unit_time{"time"};
inline constexpr std::string_view g_metric_unit_temperature{"temperature"};
inline constexpr std::string_view g_metric_unit_length{"length"};
inline constexpr std::string_view g_metric_unit_bytes{"bytes"};
inline constexpr std::string_view g_metric_unit_percent{"percent"};
inline constexpr std::string_view g_metric_unit_voltage{"voltage"};
inline constexpr std::string_view g_metric_unit_current{"current"};
inline constexpr std::string_view g_metric_unit_energy{"energy"};
inline constexpr std::string_view g_metric_unit_power{"power"};
inline constexpr std::string_view g_metric_unit_mass{"mass"};

} // namespace yafiyogi::yy_prometheus
