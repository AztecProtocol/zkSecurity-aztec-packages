#pragma once

#include "barretenberg/relations/generated/avm/declare_views.hpp"
#include "barretenberg/relations/relation_parameters.hpp"
#include "barretenberg/relations/relation_types.hpp"

namespace bb::Avm_vm {

template <typename FF> struct PowersRow {
    FF powers_power_of_2{};
};

template <typename FF_> class powersImpl {
  public:
    using FF = FF_;

    static constexpr std::array<size_t, 1> SUBRELATION_PARTIAL_LENGTHS = { 2 };

    template <typename ContainerOverSubrelations, typename AllEntities>
    void static accumulate(ContainerOverSubrelations& evals,
                           const AllEntities& new_term,
                           [[maybe_unused]] const RelationParameters<FF>&,
                           [[maybe_unused]] const FF& scaling_factor)
    {
        {
            using Accumulator = typename std::tuple_element_t<0, ContainerOverSubrelations>;
            auto tmp = (new_term.powers_power_of_2 - new_term.powers_power_of_2);
            tmp *= scaling_factor;
            std::get<0>(evals) += typename Accumulator::View(tmp);
        }
    }
};

template <typename FF> class powers : public Relation<powersImpl<FF>> {
  public:
    static constexpr const char* NAME = "powers";

    static std::string get_subrelation_label(size_t index)
    {
        switch (index) {}
        return std::to_string(index);
    }
};

} // namespace bb::Avm_vm