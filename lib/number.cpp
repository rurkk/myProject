#include "number.h"

#include <iomanip>

#include <cmath>
#include <cstring>

uint2022_t from_uint(uint32_t i) {
  uint2022_t number{};
  number.digits[0] = i % uint2022_t::BASE;
  number.digits[1] = i / uint2022_t::BASE;

  return number;
}

uint2022_t from_string(const char* buff) {
  uint2022_t number;
  uint32_t element = 0;
  uint32_t j = 0;
  for (int i = strlen(buff) - 1; i >= 0; i--, j++) {
    if (j % uint2022_t::NUMBERS == 0 and j != 0) {
      number.digits[(j / uint2022_t::NUMBERS) - 1] = element;
      element = (buff[i] - '0');
    } else {
      element += (buff[i] - '0') * pow(10, j % uint2022_t::NUMBERS);
    }
  }
  if (j % uint2022_t::NUMBERS != 0) number.digits[j / uint2022_t::NUMBERS] = element;
  else number.digits[(j / uint2022_t::NUMBERS) - 1] = element;

  return number;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
  uint2022_t answer;
  uint2022_t a = lhs;
  uint2022_t b = rhs;
  for (int i = 0; i < uint2022_t::SIZE; i++) {
    answer.digits[i] = (a.digits[i] + b.digits[i]) % uint2022_t::BASE;
    a.digits[i + 1] += (a.digits[i] + b.digits[i]) / uint2022_t::BASE;
  }

  return answer;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
  uint2022_t answer;
  uint2022_t answer0;
  uint2022_t a = lhs;
  uint2022_t b = rhs;
  for (int i = 0; i < uint2022_t::SIZE; i++) {
    if (a.digits[i] >= b.digits[i]) answer.digits[i] = a.digits[i] - b.digits[i];
    else {
      int j = i + 1;
      while (a.digits[j] == 0) {
        a.digits[j] = uint2022_t::BASE - 1;
        j++;
        if (j >= uint2022_t::SIZE) {
          return answer0;
        }
      }
      a.digits[j]--;
      a.digits[i] += uint2022_t::BASE;
      answer.digits[i] = a.digits[i] - b.digits[i];
    }
  }

  return answer;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
  uint2022_t answer;
  uint64_t element;
  for (int i = 0; i < uint2022_t::SIZE; i++) {
    uint64_t a = lhs.digits[i];
    for (int j = 0; j < uint2022_t::SIZE; j++) {
      if (i + j >= uint2022_t::SIZE) {
        break;
      }
      uint64_t b = rhs.digits[j];
      element = (uint64_t) answer.digits[i + j] + a * b;
      answer.digits[i + j] = element % uint2022_t::BASE;
      if (i + j + 1 < uint2022_t::SIZE) {
        answer.digits[i + j + 1] += element / uint2022_t::BASE;
      }
    }
  }

  return answer;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
  uint2022_t res;
  uint2022_t cur_value;
  for (int i = uint2022_t::SIZE - 1; i >= 0; i--) {
    for (int j = uint2022_t::SIZE - 1; j >= 1; j--) cur_value.digits[j] = cur_value.digits[j - 1];
    cur_value.digits[0] = lhs.digits[i];
    int x = 0;
    int l = 1, r = uint2022_t::BASE;
    while (l <= r) {
      int m = (l + r) >> 1;
      uint2022_t cur = rhs * from_uint(m);
      if (cur <= cur_value) {
        x = m;
        l = m + 1;
      } else
        r = m - 1;
    }
    res.digits[i] = x;
    cur_value = cur_value - rhs * from_uint(x);
  }

  return res;
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
  bool flag = true;
  for (int i = 0; i < uint2022_t::SIZE; i++) {
    if (lhs.digits[i] != rhs.digits[i]) {
      flag = false;
      break;
    }
  }

  return flag;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
  return !(lhs == rhs);
}

bool operator>(const uint2022_t& lhs, const uint2022_t& rhs) {
  uint2022_t first_n = lhs;
  uint2022_t second_n = rhs;
  for (int i = uint2022_t::SIZE - 1; i >= 0; i--) {
    if (first_n.digits[i] != second_n.digits[i]) {
      return first_n.digits[i] > second_n.digits[i];
    }
  }

  return false;
}

bool operator>=(const uint2022_t& lhs, const uint2022_t& rhs) {
  return !(lhs < rhs);
}

bool operator<(const uint2022_t& lhs, const uint2022_t& rhs) {
  return (rhs > lhs);
}

bool operator<=(const uint2022_t& lhs, const uint2022_t& rhs) {
  return !(lhs > rhs);
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
  int start_index = uint2022_t::SIZE - 1;
  bool flag = false;
  for (uint32_t digit : value.digits) {
    if (digit != 0) {
      flag = true;
      break;
    }
  }
  if (!flag) {
    stream << 0;

    return stream;
  }
  while (value.digits[start_index] == 0) start_index--;
  stream << value.digits[start_index];
  start_index--;
  for (int i = start_index; i >= 0; i--) {
    stream << std::setw(uint2022_t::NUMBERS) << std::setfill('0') << value.digits[i];
  }

  return stream;
}