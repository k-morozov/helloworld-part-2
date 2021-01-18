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

    template <size_t I>
    struct CompareTuples {
        template <typename... Types1, typename... Types2>
        static constexpr bool CompareAll(const std::tuple<Types1...>& data, const std::tuple<Types2...>& pattern) {
            if (std::get<I - 1>(data) != std::get<I - 1>(pattern))
                return false;

            return CompareTuples<I - 1>::CompareAll(data, pattern);
        }
    };

    template <>
    struct CompareTuples<0> {
        template <typename... Types1, typename... Types2>
        static constexpr bool CompareAll(const std::tuple<Types1...>&, const std::tuple<Types2...>&) {
            return true;
        }
    };

    // **********************************************************************************************************

    template <typename TupType, size_t... I>
    void PrintTuple(std::ostream& ostream, const TupType& tuple, std::index_sequence<I...>) {
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

    private:
        std::map<ip_address, int, std::greater<ip_address>> ip_pool;

        std::vector<std::string> split(const std::string &str, char d);

        void print(std::ostream& ostream, std::function<bool(ip_address)>);

    };

// ************************************************************************

    int version();
}
