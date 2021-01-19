#pragma once

#include <array>
#include <vector>
#include <iostream>
#include <map>
#include <functional>

namespace lib {
    using ip_type = int;

    using ip_address = std::tuple<ip_type, ip_type, ip_type, ip_type>;

    // **********************************************************************************************************

    template <typename... Types, size_t... Position>
    constexpr auto CreateTupleFromVectorHelper(const std::vector<std::string>& v, std::index_sequence<Position...>) {
        return std::make_tuple(atoi(v[Position].c_str()) ...);
    }

    template <typename>
    struct CreateTupleFromVector;

    template <typename... Types>
    struct CreateTupleFromVector<std::tuple<Types...>> {
        static auto create(const std::vector<std::string>& v) {
            return CreateTupleFromVectorHelper(v, std::make_index_sequence<sizeof... (Types)>());
        }
    };

    // **********************************************************************************************************

    extern bool Compare(ip_type lhs, ip_type rhs);

    template <typename Type, typename ... Types>
    bool FindInTuple(const std::tuple<Types ...>& data, const Type& pattern) {
        auto finder = [&pattern](auto&& ... args) {
            return (Compare(pattern, decltype(args)(args)) || ...);
        };

        return std::apply(finder, data);
    }

    template <size_t I>
    struct CompareTuples {
        template <typename... TypeData, typename... TypePattern>
        static constexpr bool CompareAll(const std::tuple<TypeData...>& data, const std::tuple<TypePattern...>& pattern) {
            if (std::get<I - 1>(data) != std::get<I - 1>(pattern)) {
                return false;
            }
                
            return CompareTuples<I - 1>::CompareAll(data, pattern);
        }

        template <typename ... TypeData, typename ... TypePattern>
        static constexpr bool CompareAny(const std::tuple<TypeData ...>& data, const std::tuple<TypePattern ...>& pattern) {
            if (FindInTuple(data, std::get<I-1>(pattern))) {
                return true;
            }

            return CompareTuples<I-1>::CompareAny(data, pattern);
        }
    };

    template <>
    struct CompareTuples<0> {
        template <typename ... TypeData, typename ... TypePattern>
        static constexpr bool CompareAll(const std::tuple<TypeData ...>&, const std::tuple<TypePattern ...>&) {
            return true;
        }

        template <typename ... TypeData, typename ... TypePattern>
        static constexpr bool CompareAny(const std::tuple<TypeData ...>&, const std::tuple<TypePattern ...>&) {
            return false;
        }
    };

    // **********************************************************************************************************

    template <typename Type, size_t... I>
    void PrintTuple(std::ostream& ostream, const Type& tuple, std::index_sequence<I...>) {
        (..., (ostream << std::string(I == 0 ? "" : ".") << std::get<I>(tuple)));
    }

    template <typename... Types>
    void PrintTuple(std::ostream& ostream, const std::tuple<Types...>& tuple) {
        PrintTuple(ostream, tuple, std::make_index_sequence<sizeof...(Types)>());
    }

    // **********************************************************************************************************

    class IPAddressPool {
    public:
        void insert(const ip_address& address);

        void insert(const std::string&);

        template <typename... Args>
        void print_all(std::ostream& ostream, Args&&... args) {
            auto filterAll = [&](const auto& address) {
                return CompareTuples<sizeof...(args)>::CompareAll(address, std::make_tuple(args...));
            };
            print(ostream, filterAll);
        }

        template <typename... Args>
        void print_any(std::ostream& ostream, Args&&... args) {
            auto filterAny = [&](const auto& address) {
                return CompareTuples<sizeof...(args)>::CompareAny(address, std::make_tuple(args...));
            };
            print(ostream, filterAny);
        }

    private:
        std::map<ip_address, int, std::greater<ip_address>> ip_pool;

        std::vector<std::string> split(const std::string &str, char d);

        void print(std::ostream& ostream, std::function<bool(ip_address)>);

    };

// ************************************************************************

    int version();
}
