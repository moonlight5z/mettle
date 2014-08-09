#ifndef INC_METTLE_TERM_HPP
#define INC_METTLE_TERM_HPP

#include <sstream>
#include <string>

namespace term {

namespace detail {
  // This is just a dumb template trick so that this file can have a static
  // variable and be header-only. That'll make life easier for users of the lib.
  template<typename Tag>
  struct status {
    static std::atomic<bool> enabled_;
  };

  template<typename Tag>
  std::atomic<bool> status<Tag>::enabled_(false);

  struct status_tag {};
}

inline void enabled(bool enabled) {
  detail::status<detail::status_tag>::enabled_ = enabled;
}

inline bool enabled() {
  return detail::status<detail::status_tag>::enabled_;
}

enum class color {
  black   = 0,
  red     = 1,
  green   = 2,
  yellow  = 3,
  blue    = 4,
  magenta = 5,
  cyan    = 6,
  white   = 7,
  normal  = 9
};

inline size_t fg(const color &c) {
  return 30 + static_cast<size_t>(c);
}

inline size_t bg(const color &c) {
  return 40 + static_cast<size_t>(c);
}

enum class sgr {
  reset     = 0,
  bold      = 1,
  underline = 4
};

class format {
  friend std::ostream & operator <<(std::ostream &, const format &);
public:
  template<typename First>
  explicit format(First &&first) {
    std::stringstream s;
    s << "\033[" << static_cast<size_t>(std::forward<First>(first)) << "m";
    string_ = s.str();
  }

  template<typename First, typename ...Rest>
  explicit format(First &&first, Rest &&...rest) {
    std::stringstream s;
    s << "\033[" << static_cast<size_t>(std::forward<First>(first));

    size_t args[] = {static_cast<size_t>(std::forward<Rest>(rest))...};
    for(const auto &i : args)
      s << ";" << i;
    s << "m";
    string_ = s.str();
  }
private:
  std::string string_;
};

inline format reset() {
  return format(sgr::reset);
}

inline std::ostream & operator <<(std::ostream &o, const format &fmt) {
  if(enabled())
    return o << fmt.string_;
  return o;
}

} // namespace term

#endif
