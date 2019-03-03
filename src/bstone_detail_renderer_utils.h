/*
BStone: A Source port of
Blake Stone: Aliens of Gold and Blake Stone: Planet Strike

Copyright (c) 1992-2013 Apogee Entertainment, LLC
Copyright (c) 2013-2019 Boris I. Bendovsky (bibendovsky@hotmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the
Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/


//
// Renderer utils.
//
// !!! Internal usage only. !!!
//


#ifndef BSTONE_DETAIL_RENDERER_UTILS_INCLUDED
#define BSTONE_DETAIL_RENDERER_UTILS_INCLUDED


#include <string>
#include "bstone_renderer.h"


struct SDL_Window;
using SdlWindowPtr = SDL_Window*;


namespace bstone
{
namespace detail
{


class RendererUtilsCreateWindowParam
{
public:
	bool is_opengl_;

	RendererInitializeWindowParam window_;
}; // RendererUtilsCreateWindowParam


class RendererUtils
{
public:
	using TextureBuffer = std::vector<RendererColor32>;


	const std::string& get_error_message() const;


	static bool is_pot_value(
		const int value);

	static int find_nearest_pot_value(
		const int value);

	static int calculate_mipmap_count(
		const int width,
		const int height);

	bool create_window(
		const RendererUtilsCreateWindowParam& param,
		SdlWindowPtr& sdl_window);

	bool show_window(
		SdlWindowPtr sdl_window,
		const bool is_visible);

	bool validate_initialize_param(
		const RendererInitializeParam& param);


	bool validate_index_buffer_create_param(
		const RendererIndexBufferCreateParam& param);

	bool validate_index_buffer_update_param(
		const RendererIndexBufferUpdateParam& param);


	bool validate_vertex_buffer_create_param(
		const RendererVertexBufferCreateParam& param);

	bool validate_vertex_buffer_update_param(
		const RendererVertexBufferUpdateParam& param);


	bool validate_texture_2d_create_param(
		const RendererTexture2dCreateParam& param);

	bool validate_texture_2d_update_param(
		const RendererTexture2dUpdateParam& param);

	static bool is_ogl_renderer_path(
		const RendererPath renderer_path);


	// Converts indexed, opaque, power-of-two pixels to RGBA ones.
	static void indexed_opaque_pot_to_rgba_pot(
		const int width,
		const int height,
		const int actual_width,
		const int actual_height,
		const std::uint8_t* const indexed_pixels,
		const RendererPalette& indexed_palette,
		const bool* const indexed_alphas,
		TextureBuffer& texture_buffer);

	// Converts indexed, opaque, non-power-of-two pixels to RGBA ones.
	static void indexed_opaque_npot_to_rgba_pot(
		const int width,
		const int height,
		const int actual_width,
		const int actual_height,
		const std::uint8_t* const indexed_pixels,
		const RendererPalette& indexed_palette,
		const bool* const indexed_alphas,
		TextureBuffer& texture_buffer);

	// Converts indexed, transparent, power-of-two pixels to RGBA ones.
	static void indexed_transparent_pot_to_rgba_pot(
		const int width,
		const int height,
		const int actual_width,
		const int actual_height,
		const std::uint8_t* const indexed_pixels,
		const RendererPalette& indexed_palette,
		const bool* const indexed_alphas,
		TextureBuffer& texture_buffer);

	// Converts indexed, transparent, non-power-of-two pixels to RGBA ones.
	static void indexed_transparent_npot_to_rgba_pot(
		const int width,
		const int height,
		const int actual_width,
		const int actual_height,
		const std::uint8_t* const indexed_pixels,
		const RendererPalette& indexed_palette,
		const bool* const indexed_alphas,
		TextureBuffer& texture_buffer);

	// Converts indexed pixels to RGBA ones.
	static void indexed_to_rgba_pot(
		const int width,
		const int height,
		const int actual_width,
		const int actual_height,
		const std::uint8_t* const indexed_pixels,
		const RendererPalette& indexed_palette,
		const bool* const indexed_alphas,
		TextureBuffer& texture_buffer);


	// Converts indexed sprite pixels to RGBA ones.
	static void indexed_sprite_to_rgba_pot(
		const std::int16_t* const indexed_sprite,
		const RendererPalette& indexed_palette,
		TextureBuffer& texture_buffer);


	// Converts RGBA non-power-of-two pixels to RGBA power-of-two ones.
	static void rgba_npot_to_rgba_pot(
		const int width,
		const int height,
		const int actual_width,
		const int actual_height,
		const RendererColor32* const rgba_pixels,
		TextureBuffer& texture_buffer);


	static void build_mipmap(
		const int previous_width,
		const int previous_height,
		const RendererColor32CPtr src_colors,
		const RendererColor32Ptr dst_colors);


private:
	std::string error_message_;


	bool create_window_validate_param(
		const RendererUtilsCreateWindowParam& param);

	bool create_window_set_ogl_attributes();

	std::uint32_t create_window_sdl_flags(
		const RendererUtilsCreateWindowParam& param);
}; // RendererUtils


} // detail
} // bstone


#endif // !BSTONE_DETAIL_RENDERER_UTILS_INCLUDED
