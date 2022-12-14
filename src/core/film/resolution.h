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

class Resolution
{
public:
    Resolution();
    ~Resolution() = default;

public:
    bool operator==(const Resolution& resolution) const;
    bool operator!=(const Resolution& resolution) const;

public:
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline int GetArea() const { return m_Width * m_Height; }

public:
    void SetWidth(int width);
    void SetHeight(int height);
    bool IsWithinBounds(const Point2i& point) const;

protected:
    int m_Width;
    int m_Height;
};

