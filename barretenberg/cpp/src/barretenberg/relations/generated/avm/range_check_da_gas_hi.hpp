#pragma once

#include "barretenberg/relations/generic_lookup/generic_lookup_relation.hpp"

#include <cstddef>
#include <tuple>

namespace bb {

class range_check_da_gas_hi_lookup_settings {
  public:
    static constexpr size_t READ_TERMS = 1;
    static constexpr size_t WRITE_TERMS = 1;
    static constexpr size_t READ_TERM_TYPES[READ_TERMS] = { 0 };
    static constexpr size_t WRITE_TERM_TYPES[WRITE_TERMS] = { 0 };
    static constexpr size_t LOOKUP_TUPLE_SIZE = 1;
    static constexpr size_t INVERSE_EXISTS_POLYNOMIAL_DEGREE = 4;
    static constexpr size_t READ_TERM_DEGREE = 0;
    static constexpr size_t WRITE_TERM_DEGREE = 0;

    template <typename AllEntities> static inline auto inverse_polynomial_is_computed_at_row(const AllEntities& in)
    {
        return (in.main_sel_gas_accounting_active == 1 || in.main_sel_rng_16 == 1);
    }

    template <typename Accumulator, typename AllEntities>
    static inline auto compute_inverse_exists(const AllEntities& in)
    {
        using View = typename Accumulator::View;
        const auto is_operation = View(in.main_sel_gas_accounting_active);
        const auto is_table_entry = View(in.main_sel_rng_16);
        return (is_operation + is_table_entry - is_operation * is_table_entry);
    }

    template <typename AllEntities> static inline auto get_const_entities(const AllEntities& in)
    {
        return std::forward_as_tuple(in.range_check_da_gas_hi,
                                     in.range_check_da_gas_hi_counts,
                                     in.main_sel_gas_accounting_active,
                                     in.main_sel_rng_16,
                                     in.main_abs_da_rem_gas_hi,
                                     in.main_clk);
    }

    template <typename AllEntities> static inline auto get_nonconst_entities(AllEntities& in)
    {
        return std::forward_as_tuple(in.range_check_da_gas_hi,
                                     in.range_check_da_gas_hi_counts,
                                     in.main_sel_gas_accounting_active,
                                     in.main_sel_rng_16,
                                     in.main_abs_da_rem_gas_hi,
                                     in.main_clk);
    }
};

template <typename FF_>
class range_check_da_gas_hi_relation : public GenericLookupRelation<range_check_da_gas_hi_lookup_settings, FF_> {
  public:
    static constexpr const char* NAME = "RANGE_CHECK_DA_GAS_HI";
};
template <typename FF_> using range_check_da_gas_hi = GenericLookup<range_check_da_gas_hi_lookup_settings, FF_>;

} // namespace bb