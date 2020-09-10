/*
  Copyright (C) 2002-2020 CERN for the benefit of the ATLAS collaboration
*/

#include <cmath>
#include <cstring>
#include <iostream>

namespace CxxUtils
{
    /// Define a nice alias for a built-in vectorized type.
    template <typename T, size_t N>
    using vec __attribute__((vector_size(N * sizeof(T)))) = T;

    template <class VEC>
    struct vec_type
    {
        static auto elt(const VEC &v) -> decltype(v[0]);
        typedef typename std::invoke_result<decltype(elt), const VEC &>::type type1;
        typedef std::remove_cv_t<std::remove_reference_t<type1>> type;
    };
    /// Deduce the element type from a vectorized type.
    template <class VEC>
    using vec_type_t = typename vec_type<VEC>::type;

    template <class VEC>
    inline constexpr size_t vec_size()
    {
        typedef vec_type_t<VEC> ELT;
        return sizeof(VEC) / sizeof(ELT);
    }

    template <typename VEC>
    inline void
    vload(VEC &dst, vec_type_t<VEC> const *src)
    {
        std::memcpy(&dst, src, sizeof(VEC));
    }

    template <typename VEC>
    inline void
    vstore(vec_type_t<VEC> *dst, const VEC &src)
    {
        std::memcpy(dst, &src, sizeof(VEC));
    }

    namespace bool_pack_helper
    {
        template <bool...>
        struct bool_pack;
        template <bool... bs>
        using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;
    } // namespace bool_pack_helper

    template <size_t... Indices, typename VEC>
    inline void vpermute(VEC &dst, const VEC &src)
    {
        constexpr size_t N = vec_size<VEC>();
        static_assert((sizeof...(Indices) == N),
                      "Number of indices different than vector size");
        static_assert(
            bool_pack_helper::all_true<(Indices >= 0 && Indices < N)...>::value,
            "permute indices outside allowed range");

#if !HAVE_VECTOR_SIZE_ATTRIBUTE || WANT_VECTOR_FALLBACK
        dst = VEC{src[Indices]...};
#elif defined(__clang__)
        dst = __builtin_shufflevector(src, src, Indices...);
#else // gcc
        dst = __builtin_shuffle(src, mask_type_t<VEC>{Indices...});
#endif
    }
} // namespace CxxUtils
