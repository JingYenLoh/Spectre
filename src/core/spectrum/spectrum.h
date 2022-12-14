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

#pragma once

const int NumSpectralSamples = 60;
static_assert(NumSpectralSamples % 4 == 0, "NumSpectralSamples should be 32byte (AVX2) aligned");

class Spectrum
{
public:
    Spectrum(double v = 0.0);
    ~Spectrum() = default;

public:
    inline bool operator==(const Spectrum& other) const { return IsEqual(other); }
    inline bool operator!=(const Spectrum& other) const { return !IsEqual(other); }

    Spectrum operator+(const Spectrum& c) const;
    Spectrum& operator+=(const Spectrum& c);
    Spectrum operator-(const Spectrum& c) const;
    Spectrum& operator-=(const Spectrum& c);
    Spectrum operator*(const Spectrum& c) const;
    Spectrum& operator*=(const Spectrum& c);
    Spectrum operator/(const Spectrum& c) const;
    Spectrum& operator/=(const Spectrum& c);

public:
    bool IsBlack() const;
    bool HasNans() const;
    bool IsEqual(const Spectrum& other) const;

    void ClampZero();

public:
    static Spectrum Sqrt(const Spectrum& s);
    static Spectrum Pow(const Spectrum& s, double n);
    static Spectrum Lerp(const Spectrum& s1, const Spectrum& s2, double t);
    static Spectrum Clamp(const Spectrum& s1, const Spectrum& l, const Spectrum& h);
    static Spectrum Min(const Spectrum& s1, const Spectrum& s2);
    static Spectrum Max(const Spectrum& s1, const Spectrum& s2);

public:
    double m_Coefficients[NumSpectralSamples];
};

