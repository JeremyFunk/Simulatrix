#pragma once

#include <xhash>

namespace Simulatrix {
    class UUID {
    public:
        UUID();
        UUID(uint64_t uuid);

        operator uint64_t() const { return m_UUID; }
    private:
        uint64_t m_UUID;

    };
}


namespace std {
    template<>
    struct hash<Simulatrix::UUID>
    {
        std::size_t operator()(const Simulatrix::UUID& uuid) const {
            return hash<uint64_t>()((uint64_t)uuid);
        }
    };
}