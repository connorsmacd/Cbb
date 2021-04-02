#ifndef CBB_FRACTION_HPP
#define CBB_FRACTION_HPP

#include <ieme/ieme.hpp>


namespace cbb {


using fraction_rep_t = int;
using fraction_ops_t = ieme::ops::defaults;

using fraction = ieme::fraction<fraction_rep_t, fraction_ops_t>;


} // namespace cbb


#endif
