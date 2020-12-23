/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2020-2021 Samuel Van Allen - All rights reserved.

    RTCore is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "resolution.h"
#include "filmtile.h"
#include "core/spectrum/spectralcoefficients.h"

class Film
{
public:
    Film();
    ~Film() = default;

    inline const Resolution& GetResolution() const { return m_Resolution; }
    inline int GetNumPixels() const { return m_Resolution.GetWidth() * m_Resolution.GetHeight(); }

    FilmTile& GetTile(int index);
    FilmTile& GetTile(const Vector2i& position);

    void SetResolution(const Resolution& resolution);

private:
    void SetupTiles();
    int GetTileIndex(const Vector2i& position) const;

private:
    Resolution m_Resolution;
    std::vector<FilmTile> m_Tiles;
};

