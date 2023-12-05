/*
BStone: Unofficial source port of Blake Stone: Aliens of Gold and Blake Stone: Planet Strike
Copyright (c) 2023 Boris I. Bendovsky (bibendovsky@hotmail.com) and Contributors
SPDX-License-Identifier: MIT
*/

// OpenGL symbol resolver (SDL).

#include <SDL_video.h>

#include "bstone_sys_sdl_gl_symbol_resolver.h"

namespace bstone {
namespace sys {

void* SdlGlSymbolResolver::do_find_symbol(const char* symbol_name) const noexcept
{
	return SDL_GL_GetProcAddress(symbol_name);
}

} // namespace sys
} // namespace bstone
