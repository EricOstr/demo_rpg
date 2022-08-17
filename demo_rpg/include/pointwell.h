#pragma once
#include "types.h"


class PointWell {

private:
    welltype _current;
    welltype _max;

public:

    PointWell();
    PointWell(welltype c, welltype m);

    [[nodiscard]] const welltype GetMax() const noexcept;
    [[nodiscard]] const welltype GetCurrent() const noexcept;
    [[nodiscard]] const bool IsFull() const noexcept;

    void SetMax(welltype new_max) noexcept;
    void ReduceCurrent(welltype damage) noexcept;
    void IncreaseCurrent(welltype amount) noexcept;

};