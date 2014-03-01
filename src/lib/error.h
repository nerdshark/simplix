/*
 * Copyright © 2014 Thorben Hasenpusch <thorben.hasenpusch@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

class Errno {
public:
    enum ErrorCode {
        SUCCESS,
        EINVAL,
        ERANGE
    };

    Errno(ErrorCode code) : code(code) { }

    bool operator==(ErrorCode x) { return x == code; }
    bool operator!=(ErrorCode x) { return x != code; }
    ErrorCode operator=(ErrorCode x) { return code = x; }
    const char *to_string() const;
private:
    ErrorCode code;
};
