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

#include "core/entity/components/transform.h"
#include "core/film/film.h"

class Camera
{
public:
    Camera() = default;
    ~Camera() = default;

    inline Transform& GetTransform() { return m_Transform; }
    inline Film& GetFilm() { return m_Film; }

public:
    virtual void Render() = 0;

protected:
    Transform m_Transform;
    Film m_Film;
};

