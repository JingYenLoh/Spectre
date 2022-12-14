/*
    This file is part of Spectre, an open-source physically based
    spectral raytracing library.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.

    Spectre is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "spectrum.h"

Spectrum::Spectrum(double v)
{
    std::fill(std::begin(m_Coefficients), std::end(m_Coefficients), v);
}

Spectrum Spectrum::operator+(const Spectrum& c) const
{
    Spectrum result;

    for (int i = 0; i < NumSpectralSamples; ++i)
        result.m_Coefficients[i] = m_Coefficients[i] + c.m_Coefficients[i];

    return result;
}

Spectrum& Spectrum::operator+=(const Spectrum& c)
{
    for (int i = 0; i < NumSpectralSamples; ++i)
        m_Coefficients[i] += c.m_Coefficients[i];

    return *this;
}

Spectrum Spectrum::operator-(const Spectrum& c) const
{
    Spectrum result;

    for (int i = 0; i < NumSpectralSamples; ++i)
        result.m_Coefficients[i] = m_Coefficients[i] - c.m_Coefficients[i];

    return result;
}

Spectrum& Spectrum::operator-=(const Spectrum& c)
{
    for (int i = 0; i < NumSpectralSamples; ++i)
        m_Coefficients[i] -= c.m_Coefficients[i];

    return *this;
}

Spectrum Spectrum::operator*(const Spectrum& c) const
{
    Spectrum result;

    for (int i = 0; i < NumSpectralSamples; ++i)
        result.m_Coefficients[i] = m_Coefficients[i] * c.m_Coefficients[i];

    return result;
}

Spectrum& Spectrum::operator*=(const Spectrum& c)
{
    for (int i = 0; i < NumSpectralSamples; ++i)
        m_Coefficients[i] *= c.m_Coefficients[i];

    return *this;
}

Spectrum Spectrum::operator/(const Spectrum& c) const
{
    Spectrum result;

    for (int i = 0; i < NumSpectralSamples; ++i)
        result.m_Coefficients[i] = m_Coefficients[i] / c.m_Coefficients[i];

    return result;
}

Spectrum& Spectrum::operator/=(const Spectrum& c)
{
    for (int i = 0; i < NumSpectralSamples; ++i)
        m_Coefficients[i] /= c.m_Coefficients[i];

    return *this;
}

bool Spectrum::IsBlack() const
{
    for (int i = 0; i < NumSpectralSamples; ++i)
        if (m_Coefficients[i] != 0.0)
            return false;

    return true;
}

bool Spectrum::HasNans() const
{
    for (int i = 0; i < NumSpectralSamples; ++i)
        if (std::isnan(m_Coefficients[i]))
            return true;

    return false;
}

bool Spectrum::IsEqual(const Spectrum& other) const
{
    for (int i = 0; i < NumSpectralSamples; ++i)
        if (m_Coefficients[i] != other.m_Coefficients[i])
            return false;

    return true;
}

void Spectrum::ClampZero()
{
    for (int i = 0; i < NumSpectralSamples; ++i)
        m_Coefficients[i] = m_Coefficients[i] < 0 ? 0 : m_Coefficients[i];
}

Spectrum Spectrum::Sqrt(const Spectrum& s)
{
    Spectrum result;
    for (int i = 0; i < NumSpectralSamples; ++i)
        result.m_Coefficients[i] = sqrt(s.m_Coefficients[i]);

    return result;
}

Spectrum Spectrum::Pow(const Spectrum& s, double p)
{
    Spectrum result;
    for (int i = 0; i < NumSpectralSamples; ++i)
        result.m_Coefficients[i] = pow(s.m_Coefficients[i], p);

    return result;
}

Spectrum Spectrum::Lerp(const Spectrum& s1, const Spectrum& s2, double t)
{
    return s1 * (1 - t) + s2 * t;
}

Spectrum Spectrum::Clamp(const Spectrum& s1, const Spectrum& l, const Spectrum& h)
{
    Spectrum result;
    for (int i = 0; i < NumSpectralSamples; ++i)
    {
        double val = s1.m_Coefficients[i];
        double lv = l.m_Coefficients[i];
        double hv = h.m_Coefficients[i];
        result.m_Coefficients[i] = val < lv ? lv : (val > hv ? hv : val);
    }

    return result;
}

Spectrum Spectrum::Min(const Spectrum& s1, const Spectrum& s2)
{
    Spectrum result;
    for (int i = 0; i < NumSpectralSamples; ++i)
    {
        double v1 = s1.m_Coefficients[i];
        double v2 = s2.m_Coefficients[i];
        result.m_Coefficients[i] = v1 < v2 ? v1 : v2;
    }

    return result;
}

Spectrum Spectrum::Max(const Spectrum& s1, const Spectrum& s2)
{
    Spectrum result;
    for (int i = 0; i < NumSpectralSamples; ++i)
    {
        double v1 = s1.m_Coefficients[i];
        double v2 = s2.m_Coefficients[i];
        result.m_Coefficients[i] = v1 > v2 ? v1 : v2;
    }

    return result;
}

