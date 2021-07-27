//
// Created by Darwin Yuan on 2021/7/27.
//

#ifndef TYPE_LIST_2_0B40D1F68A124491969A33E713632229
#define TYPE_LIST_2_0B40D1F68A124491969A33E713632229

#include <type-list/types/detail/ebo.h>
#include <type-list/types/bool_c.h>
#include <utility>

namespace holo::detail {
    template<typename Xn, typename ... Ts>
    struct tuple_base;

    template<std::size_t ... Xn, typename ... Ts>
    struct tuple_base<std::index_sequence<Xn...>, Ts...> {
        struct base : ebo<Xn, Ts> ... {};
    };

    template<typename ... Ts>
    using tuple_base_t = typename tuple_base<std::index_sequence_for<Ts...>, Ts...>::base;
}

namespace holo {
    template<typename ... Ts>
    struct type_list_t;

    template<typename ... Ts>
    struct tuple_t : detail::tuple_base_t<Ts...> {
        constexpr tuple_t() {}
        using to_list_t = type_list_t<Ts...>;
    };

    template<std::size_t N, typename ... Xs>
    constexpr auto get(tuple_t<Xs...> xs) -> auto {
        return detail::ebo_get<N>(xs);
    }

    template<typename ... Xs>
    constexpr auto tuple_c = tuple_t<Xs...>{};

    template<typename ... Xs, typename ... Ys>
    constexpr auto operator==(tuple_t<Xs...>, tuple_t<Ys...>) -> auto {
        if constexpr(sizeof...(Xs) == sizeof...(Ys)) {
            return ((type_c<Xs> == type_c<Ys>) && ...);
        } else {
            return false_c;
        }
    }

    template<typename ... Xs, typename ... Ys>
    constexpr auto operator!=(tuple_t<Xs...> lhs, tuple_t<Ys...> rhs) -> auto {
        return !operator==(lhs, rhs);
    }
}

#endif //TYPE_LIST_2_0B40D1F68A124491969A33E713632229